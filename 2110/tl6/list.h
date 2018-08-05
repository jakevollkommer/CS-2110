#include <stdlib.h>

#ifndef LIST_H
#define LIST_H

typedef struct node_t {
	struct node_t *next;
	void* data;
} NODE;

typedef struct llist_t {
	NODE *head;
	size_t size;
} LIST;

typedef void (*list_op)(void*);

LIST *create_list();
NODE *create_node(void* data);
void push_front(LIST *llist, void* data);
void* pop_front(LIST *llist);
void destroy(LIST *llist, list_op free_func);
void* to_array(LIST *llist, size_t struct_size);

#endif
