#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * CS 2110 Timed Lab 6 Student Implementation
 * April 19, 2017
 * Jake Vollkommer
 */

/**
 * This function will create a new linked list, initialize its fields and return a pointer to the list.
 */
LIST *create_list()
{
    LIST* l = malloc(sizeof(LIST));
    l -> head = NULL;
    l -> size = 0;
    return l;
}

/**
 * This function will create a node from the given data and return a pointer to that node.
 * If the data pointer is NULL, return NULL
 */
NODE *create_node(void* data)
{
    if (data == NULL) return NULL;
    NODE* n = malloc(sizeof(NODE));
    n -> next = NULL;
    n -> data = data;
    return n;
}

/**
 * This function will add a node with the given data pointer to the head of the linked list.
 * If the data pointer or list is NULL, return from the function gracefully.
 */
void push_front(LIST *llist, void* data)
{
    if (llist == NULL || data == NULL) return;
    NODE* n = create_node(data);
    if (llist != NULL && llist->head == NULL) {
        llist->head = n;
        llist->size = llist->size + 1;
    } else if (llist != NULL && llist->head != NULL) {
        n->next = llist->head; llist->head = n;
        llist->size = llist->size + 1;
    }
}

/**
 * Removes the head of the linked list and returns the data pointer from the removed node to the user.
 * If the list is empty or NULL, return NULL.
 */
void* pop_front(LIST *llist)
{
    if (llist == NULL || llist -> size == 0) return NULL;
    NODE* n = llist->head;
    llist->head = n->next;
    llist->size = llist->size - 1;

    void* dat = n->data;
    free(n);
    return dat;
}

/**
 * All memory used in the linked list that was allocated from the heap should be freed.
 * This includes all of the node structs in the linked list and the linked list struct.
 * The data pointed at by the data pointers in each node should be freed with free_func.
 * If the list is NULL, return from the function gracefully.
 */
void destroy(LIST *llist, list_op free_func)
{
    if (llist != NULL) {
        NODE* n = NULL;
        while (NULL != llist->head) {
            n = llist->head;
            llist->head = (llist->head)->next;
            free_func(n->data);
            free(n);
        }
        llist->size = 0;
    } else {
        return;
    }
}

/**
 * This function will return an array of the data stored in the linked list.
 * Read the PDF for more information on this function.
 * If the list is empty or NULL, return NULL.
 */
void* to_array(LIST *llist, size_t struct_size)
{
    if (llist == NULL || llist -> size == 0) return NULL;
    NODE* n = llist -> head;
    char* result = malloc(struct_size * (llist -> size));
    char* p = result;
    while (n != NULL) {
        memcpy(p, n, struct_size);
        p += struct_size;
        n = n -> next;
    }
    return result;
}
