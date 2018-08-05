/*
 * CS 2110 Spring 2017
 * Author: Jake Vollkommer
 */

/* we need this for uintptr_t */
#include <stdint.h>
/* we need this for memcpy/memset */
#include <string.h>
/* we need this for my_sbrk */
#include "my_sbrk.h"
/* we need this for the metadata_t struct and my_malloc_err enum definitions */
#include "my_malloc.h"

/* You *MUST* use this macro when calling my_sbrk to allocate the
 * appropriate size. Failure to do so may result in an incorrect
 * grading!
 */
#define SBRK_SIZE 2048

/* All sizes will be in multiples of the word size defined below */
#define WORD_SIZE 8

/* This is the size of the metadata struct and canary footer in words */
#define TOTAL_METADATA_SIZE ((sizeof(metadata_t) + sizeof(long)) / WORD_SIZE)

/* This is the minimum size of a block in words, where it can
 * store the metadata, canary footer, and at least 1 word of data
 */
#define MIN_BLOCK_SIZE (TOTAL_METADATA_SIZE + 1)

/* If you want to use debugging printouts, it is HIGHLY recommended
 * to use this macro or something similar. If you produce output from
 * your code then you may receive a 20 point deduction. You have been
 * warned.
 */
#ifdef DEBUG
#define DEBUG_PRINT(x) printf(x)
#else
#define DEBUG_PRINT(x)
#endif

/* Our freelist structure - this is where the current freelist of
 * blocks will be maintained. failure to maintain the list inside
 * of this structure will result in no credit, as the grader will
 * expect it to be maintained here.
 * DO NOT CHANGE the way this structure is declared
 * or it will break the autograder.
 */
metadata_t* freelist;

/* MALLOC
 * See my_malloc.h for documentation
 */
void* my_malloc(size_t size) {
    // No need to allocate a block
    if (size == 0) {
        ERRNO = NO_ERROR;
        return NULL;
    }

    // blocksize includes alignment and the metadata size
    size_t blockSize = (size + (WORD_SIZE - size % WORD_SIZE)) / WORD_SIZE + TOTAL_METADATA_SIZE;

    // max request size is SBRK_SIZE
    if (blockSize * WORD_SIZE > SBRK_SIZE) {
        ERRNO = SINGLE_REQUEST_TOO_LARGE;
        return NULL;
    }

    metadata_t* bestfit = findBest(blockSize);
    metadata_t* userBlock = breakBlock(bestfit, blockSize);

    return (void*)((char*)(userBlock + 1));
}

metadata_t* findBest(size_t blockSize) {
    // freelist has no memory, sbrk some
    if (freelist == NULL) {
        freelist = (metadata_t*) my_sbrk(SBRK_SIZE);
        if (freelist == NULL) {
            ERRNO = OUT_OF_MEMORY;
            return NULL;
        }
        freelist -> next = NULL;
        freelist -> size = SBRK_SIZE / WORD_SIZE;
        freelist -> canary = (uintptr_t)freelist ^ freelist -> size;
        *(unsigned long*)((char*) freelist + (freelist -> size * WORD_SIZE) - sizeof(long)) = freelist -> canary;
    }

    metadata_t* curr = freelist;
    metadata_t* bestfit = NULL;
    metadata_t* prev = NULL;

    // check if first block is perfect size
    if (curr -> size == blockSize) {
        bestfit = freelist;
        bestfit -> next = NULL;
        return bestfit;
    // if first block is big enough, set bestfit to first block
    } else if (curr -> size > blockSize) {
        bestfit = curr;
    }
    // find best fit block by looking at the next block
    while (curr -> next != NULL) {
        // next block is perfect size
        if (curr -> next -> size == blockSize) {
            bestfit = curr -> next;
            curr -> next = curr -> next -> next;
            bestfit -> size = blockSize;
            bestfit -> next = NULL;
            return bestfit;
        }
        // next block is big enough and smaller than the current bestfit
        if (curr -> next -> size > blockSize &&
                (bestfit == NULL || bestfit -> size > curr -> next -> size)) {
            bestfit = curr -> next;
            prev = curr;
        }
        curr = curr -> next;
    }

    // no blocks were big enough
    if (bestfit == NULL) {
        metadata_t* new = my_sbrk(SBRK_SIZE);
        if (new == NULL) {
            ERRNO = OUT_OF_MEMORY;
            return NULL;
        }
        //bestfit will be a new sbrk
        bestfit = new;
        bestfit -> size = SBRK_SIZE / WORD_SIZE;
        bestfit -> canary = (uintptr_t) bestfit ^ bestfit -> size;
        *(unsigned long*)((char*) bestfit + (bestfit -> size * WORD_SIZE) - sizeof(long)) = bestfit -> canary;
    // bestfit was found in the freelist
    } else {
        if (bestfit == freelist) {
            freelist = freelist -> next;
        } else {
            prev -> next = bestfit -> next;
        }
    }
    bestfit -> next = NULL;

    return bestfit;
}

metadata_t* breakBlock(metadata_t* block, size_t userSize) {
    if (block -> size == userSize) {
        block -> canary = (uintptr_t) block ^ block -> size;
        *(unsigned long*)((char*) block + (block -> size * WORD_SIZE) - sizeof(long)) = block -> canary;
        return block;
    }

    // set a pointer to the end of the block - size
    char* p = (char*) block + (block -> size) * WORD_SIZE;
    p -= userSize;

    block -> size = block -> size - userSize;
    block -> canary = (uintptr_t) block ^ block -> size;
    *(unsigned long*)((char*) block + (block -> size * WORD_SIZE) - sizeof(long)) = block -> canary;

    if (block -> size >= MIN_BLOCK_SIZE) {
        addToList(block);
    } else {
        return block;
    }

    metadata_t* new = (metadata_t*) p;
    new -> size = userSize;
    new -> canary = (uintptr_t) new ^ new -> size;
    *(unsigned long*)((char*) new + (new -> size * WORD_SIZE) - sizeof(long)) = new -> canary;
    new -> next = NULL;

    return new;
}

int shouldMerge(metadata_t* left, metadata_t* right) {
    uintptr_t endOfLeft = (uintptr_t)((char*)left + (left -> size * WORD_SIZE));
    if (endOfLeft == (uintptr_t) right) {
        return 1;
    }
    return 0;
}

void addToList(metadata_t* block) {
    metadata_t* p = freelist;
    // freelist is empty
    if (freelist == NULL) {
        block -> next = NULL;
        freelist = block;
        return;
    } else {
        // block comes before start of freelist
        if ((uintptr_t)block < (uintptr_t)freelist) {
            block -> next = freelist;
            freelist = block;
            if (shouldMerge(block, block -> next)) {
                block -> size += block -> next -> size;
                block -> next = block -> next -> next;
            }
            return;
        // only one item in the freelist
        } else if (p -> next == NULL) {
            p -> next = block;
            if (shouldMerge(p, p -> next)) {
                p -> size += p -> next -> size;
                p -> next = p -> next -> next;
            }
            return;
        // block is less than second item in freelist
        } else if ((uintptr_t) block < (uintptr_t)p -> next) {
            block -> next = p -> next;
            p -> next = block;
            if (shouldMerge(block, block -> next)) {
                block -> size += block -> next -> size;
                block -> next = block -> next -> next;
            }
            return;
        } else {
            while (p -> next != NULL) {
                if ((uintptr_t)block < (uintptr_t)p -> next) {
                    block -> next = p -> next;
                    p -> next = block;
                    if (shouldMerge(block, block -> next)) {
                        block -> size += block -> next -> size;
                        block -> next = block -> next -> next;
                    }
                    if (shouldMerge(p, block)) {
                        p -> size += block -> size;
                        p -> next = block -> next;
                    }
                    return;
                }
                p = p -> next;
            }
            //block goes to the end of the freelist
            block -> next = p -> next;
            p -> next = block;
            if (shouldMerge(p, p -> next)) {
                p -> size += p -> next -> size;
                p -> next = p -> next -> next;
            }
        }
    }
}

/* REALLOC
 * See my_malloc.h for documentation
 */
void* my_realloc(void* ptr, size_t size) {
    if (ptr == NULL) {
        return my_malloc(size);
    }

    if (size == 0) {
        my_free(ptr);
        return NULL;
    }

    void* malloc = my_malloc(size);
    if (malloc == NULL) {
        return NULL;
    }

    void* copy = memcpy(malloc, ptr, size);
    my_free(ptr);
    ERRNO = NO_ERROR;
    return copy;
}

/* CALLOC
 * See my_malloc.h for documentation
 */
void* my_calloc(size_t nmemb, size_t size) {
    void* calloc = my_malloc(nmemb * size);
    if (calloc == NULL) {
        return NULL;
    }

    ERRNO = NO_ERROR;
    return memset(calloc, 0, (nmemb * size));
}

/* FREE
 * See my_malloc.h for documentation
 */
void my_free(void* ptr) {
    metadata_t* block = (metadata_t*) ptr - 1;
    long canary = (uintptr_t) block ^ block -> size;
    long c = block -> canary;

    if (c == canary) {
        addToList(block);
        ERRNO = NO_ERROR;
    } else {
        ERRNO = CANARY_CORRUPTED;
    }
}
