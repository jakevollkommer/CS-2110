/*
 * CS 2110 Spring 2017
 * Author: PUT NAME HERE
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
    return NULL;
}

/* REALLOC
 * See my_malloc.h for documentation
 */
void* my_realloc(void* ptr, size_t size) {
    return NULL;
}

/* CALLOC
 * See my_malloc.h for documentation
 */
void* my_calloc(size_t nmemb, size_t size) {
    return NULL;
}

/* FREE
 * See my_malloc.h for documentation
 */
void my_free(void* ptr) {
}
