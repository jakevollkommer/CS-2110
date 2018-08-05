/**
 * CS 2110 - Spring 2017 - Homework #10
 *
 * @author Jake Vollkommer
 *
 * dllist.c: Complete the functions!
 */

#include <stdlib.h>
#include <stdio.h>
#include "dllist.h"

/* The node struct. Has a prev pointer, next pointer, and data. */
/* DO NOT DEFINE ANYTHING OTHER THAN WHAT'S GIVEN OR YOU WILL GET A ZERO */
/* Design consideration: Only this file should know about nodes */
/* Only this file should be manipulating nodes */
/* DO NOT TOUCH THIS DECLARATION, DO NOT PUT IT IN OTHER FILES */
typedef struct dnode
{
    struct dnode* prev; /* Pointer to previous node */
    struct dnode* next; /* Pointer to next node */
    void* data; /* User data */
} node;

/* Do not create any global variables here. Your dllist library should obviously
 * work for multiple concurrent dllists */

// This function is declared as static since you should only be calling this
// function from inside this file.
static node* create_node(void* data);

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its pointers to NULL.
  *
  * @param data a void pointer to data the user wants to store in the dllist
  * @return a node
  */
static node* create_node(void* data)
{
    node* node = malloc (sizeof(node));
    node -> data = data;
    node -> next = NULL;
    node -> prev = NULL;
    return node;
}

/** create_dllist
  *
  * Creates a dllist by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head/tail to NULL.
  *
  * @return an empty dllist
  */
dllist* create_dllist(void)
{
    dllist* list = malloc(sizeof(dllist));
    list -> head = NULL;
    list -> tail = NULL;
    list -> size = 0;
    return list;
}

/** push_front
  *
  * Adds the data to the front of the dllist.
  *
  * @param d a pointer to the dllist structure.
  * @param data pointer to data the user wants to store in the dllist.
  */
void push_front(dllist *d, void *data)
{
    node* newnode = create_node(data);
    if (d != NULL) {
        if (d -> size == 0) {
            d -> tail = newnode;
            d -> head = newnode;
            d -> size = (d -> size) + 1;
            return;
        }
        node* headnode = d -> head;
        newnode -> next = headnode;
        d -> head = newnode;
        headnode -> prev = newnode;
        d -> size = (d -> size) + 1;
    }
}

/** push_back
  *
  * Adds the data to the back of the dllist.
  *
  * @param d a pointer to the dllist structure.
  * @param data pointer to data the user wants to store in the dllist.
  */
void push_back(dllist *d, void *data)
{
    node* newnode = create_node(data);
    if (d != NULL) {
        if (d -> size == 0) {
            d -> head = newnode;
            d -> tail = newnode;
            d -> size = (d -> size) + 1;
            return;
        }
        node* tailnode = d -> tail;
        tailnode -> next = newnode;
        d -> tail = newnode;
        newnode -> prev = tailnode;
        d -> size = (d -> size) + 1;
    }
}

/** front
  *
  * Gets the data at the front of the dllist
  * If the dllist is empty return NULL.
  *
  * @param d a pointer to the dllist
  * @return The data at the first node in the dllist or NULL.
  */
void *front(dllist *d)
{
    if (d == NULL) return NULL;
    node* head = d -> head;
    return head -> data;
}

/** back
  *
  * Gets the data at the "end" of the dllist
  * If the dllist is empty return NULL.
  *
  * @param d a pointer to the dllist structure
  * @return The data at the last node in the dllist or NULL.
  */
void *back(dllist *d)
{
    if (d == NULL) return NULL;
    node* tail = d -> tail;
    return tail -> data;
}

/** get
  *
  * Gets the data at the specified index in the dllist
  *
  * @param d a pointer to the dllist structure
  * @param index 0-based, starting from the head.
  * @return The data from the specified index in the dllist or NULL if index is
  *         out of range of the dllist.
  */
void *get(dllist *d, int index)
{
    node* curr = d -> head;
    if (d == NULL || curr == NULL) return NULL;
    if (index >= d -> size || index < 0) return NULL;
    for (int i = 0; i < index; i++) {
        curr = curr -> next;
    }
    return curr -> data;
}

/** add
  *
  * Adds the data at the specified index in the dllist.
  * Adding at index size should have the same behavior as push_back
  *
  * @param d a pointer to the dllist structure
  * @param index 0-based, starting from the head, to size.
  * @return true if insertion was successful or false if index is
  *         out of range of the dllist.
  */
bool add(dllist *d, void* data, int index)
{
    node* curr = d -> head;
    if (d == NULL || curr == NULL) return false;
    if (index > d -> size || index < 0) return false;
    if (index == 0) {
        push_front(d, data);
        return true;
    }
    if (index == d -> size) {
        push_back(d, data);
        return true;
    }
    for (int i = 0; i < index; i++) {
        curr = curr -> next;
    }
    node* newnode = create_node(data);
    node* nextnode = curr -> next;
    (curr -> next) -> prev = newnode;
    newnode -> next = nextnode;
    curr -> next = newnode;
    newnode -> prev = curr;
    d -> size = (d -> size) + 1;
    return true;
}

/** contains
  *
  * Traverses the dllist, trying to see if the dllist contains some data.
  * Since non-NULL values are considered true, this can be used like a boolean
  *
  * The "data" parameter may not necessarily point to the same address as the
  * equal data you are returning from this function, it's just data which the
  * eq_func says is equal. For instance, if you have a dllist of person structs:
  *   (Andrew, 26), (Nick, 24), (Collin, 23), (Marie, 23)
  * And you want to return any person whose age is 22, you could create a new
  * person struct (<NULL>, 24) with an eq_func that returns age == 24 and pass
  * that into this function as "data". contains() would then return (Nick, 24)
  *
  * If there are multiple pieces of data in the dllist which are equal to the
  * "data" parameter, return any one of them.
  *
  * @param d a pointer to the dllist structure
  * @param data The data, to see if it exists in the dllist
  * @param eq_func A function written by the user that will tell if two pieces
  *                of data are equal. Returns 0 if equal, something else
  *                otherwise. Imagine subtracting two numbers.
  * @return The data contained in the dllist, or NULL if it doesn't exist
  */
void *contains(dllist *d, void *data, dllist_eq eq_func) {
    node* curr = d -> head;
    if (d == NULL || curr == NULL) return NULL;
    for (int i = 0; i < d -> size; i++) {
        if (eq_func(data, curr -> data) == 0) return curr -> data;
        curr = curr -> next;
    }
    return NULL;
}

/** pop_front
  *
  * Removes the node at the front of the dllist, and returns its data to the user
  *
  * @param d a pointer to the dllist.
  * @return The data in the first node, or NULL if the dllist is NULL or empty
  */
void *pop_front(dllist *d)
{
    if (d == NULL || (d -> head) == NULL) return NULL;
    node* n = d -> head;
    if (d -> size < 2) {
        d -> head = NULL;
        d -> tail = NULL;
        d -> size = 0;
        return n -> data;
    }
    d -> head = n -> next;
    (d -> head) -> prev = NULL;
    d -> size = (d -> size) - 1;
    return n -> data;
}

/** pop_back
  *
  * Removes the node at the end of the dllist, and returns its data to the user
  *
  * @param d a pointer to the dllist.
  * @return The data in the first node, or NULL if the dllist is NULL or empty
  */
void *pop_back(dllist *d)
{
    if (d == NULL || (d -> tail == NULL)) return NULL;
    node* n = d -> tail;
    if (d -> size < 2) {
        d -> head = NULL;
        d -> tail = NULL;
        d -> size = 0;
        return n -> data;
    }
    d -> tail = n -> prev;
    (d -> tail) -> next = NULL;
    d -> size = (d -> size) - 1;
    return n -> data;
}

/** copy_dllist
  *
  * Create a new dllist structure, new nodes, and new copies of the data by using
  * the copy function. Its implementation for any test structure must copy
  * EVERYTHING!
  *
  * @param d A pointer to the dllist structure to make a copy of
  * @param copy_func A function pointer to a function that makes a copy of the
  *                  data that's being used in this dllist, allocating space for
  *                  every part of that data on the heap. This is some function
  *                  you must write yourself for testing, tailored specifically
  *                  to whatever context you're using the dllist for in your test
  * @return The dllist structure created by copying the old one, or NULL if the
  *         structure passed in is NULL.
  */
dllist* copy_dllist(dllist *d, dllist_copy copy_func)
{
    if (d == NULL) return NULL;
    dllist* newlist = create_dllist();
    if (d -> size ==1) {
        add(newlist, d -> head, 0);
    } else {
        node* curr = d -> head;
        for (int i = 0; i < d -> size; i++) {
            add(newlist, copy_func(curr -> data), i);
            curr = curr -> next;
        }
        newlist -> size = d -> size;
    }
    return newlist;
}

/** size
  *
  * Gets the size of the dllist
  *
  * @param d a pointer to the dllist structure
  * @return The size of the dllist
  */
int size(dllist *d)
{
    if (d == NULL) return 0;
    return d -> size;
}

/** is_empty
  *
  * Checks to see if the dllist is empty.
  *
  * @param d a pointer to the dllist structure
  * @return true if the dllist is indeed empty, or false otherwise.
  */
bool is_empty(dllist *d)
{
    if (d == NULL) return false;
    return (d -> size) == 0 && (d -> head) == NULL;
}

/** empty_dllist
  *
  * Empties the dllist. After this is called, the dllist should be empty.
  * This does not free the dllist struct itself, just all nodes and data within.
  *
  * @param d a pointer to the dllist structure
  * @param free_func function used to free the nodes' data.
  */
void empty_dllist(dllist *d, dllist_op free_func)
{
    /// @todo Implement
    /// @note Free all of the nodes, not the dllist structure itself.
    /// @note do not free the dllist structure itself.
    node* curr = d -> head;
    node* next;
    for (int i = 0; i < d -> size; i++) {
        next = curr -> next;
        free_func(curr -> data);
        free_func(curr);
        curr = next;
    }
    d -> size = 0;
}

/** traverse
  *
  * Traverses the dllist, calling a function on each node's data.
  *
  * @param d a pointer to the dllist structure
  * @param do_func a function that does something to each node's data.
  */
void traverse(dllist *d, dllist_op do_func)
{
    if (d == NULL) return;
    node* curr = d -> head;
    for (int i = 0; i < d -> size; i++) {
        do_func(curr -> data);
        curr = curr -> next;
    }
}

/** reverse
  * Reverses the dllist
  * Should do nothing if d is NULL
  * @param d a pointer to the dllist structure
  */
void reverse(dllist *d) {
    if (d == NULL) return;
    node* curr = d -> head;
    d -> head = d -> tail;
    d -> tail = curr;
    for (int i = 0; i < d -> size; i++) {
        node* next = curr -> next;
        curr -> next = curr -> prev;
        curr -> prev = next;
    }
}
