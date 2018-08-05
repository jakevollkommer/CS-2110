#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"

void test_create_node_null(void);
void test_create_node_person(void);
void test_create_list(void);
void test_push_front_null(void);
void test_push_front_0(void);
void test_push_front_1(void);
void test_push_front_3(void);
void test_pop_front_null(void);
void test_pop_front_0(void);
void test_pop_front_1(void);
void test_pop_front_3(void);
void test_to_array_null(void);
void test_to_array_0(void);
void test_to_array_1(void);
void test_to_array_3(void);
void test_destroy_null(void);
void test_destroy_3(void);

typedef struct person_t {
	int age;
	char *name;
} person;

static person *create_person(const char *name, int age);
static void free_person(void *data);

int main() {
	test_create_node_null();
	test_create_node_person();
	test_create_list();
	test_push_front_null();
	test_push_front_0();
	test_push_front_1();
	test_push_front_3();
	test_pop_front_null();
	test_pop_front_0();
	test_pop_front_1();
	test_pop_front_3();
	test_to_array_null();
	test_to_array_0();
	test_to_array_1();
	test_to_array_3();
	test_destroy_null();
	test_destroy_3();

	printf("passed all tests\nMake sure to run with valgrind!\n");
}

static person *create_person(const char *name, int age) {
	person *p = (person*) malloc(sizeof(person));
	p->name = malloc(strlen(name) + 1);
	strcpy(p->name, name);
	p->age = age;
	return p;
}

static void free_person(void *data) {
	person *p = (person*) data;
	free(p->name);
	free(p);
}

void test_create_node_null(void) {
	printf("Test 01: Test Create Node NULL - RUN\n");
	NODE *ret = create_node(NULL);
	assert(ret == NULL);
	printf("Test 01: Test Create Node NULL - SUCCESS\n");
}

void test_create_node_person(void) {
	printf("Test 02: Test Create Node Person - RUN\n");
	person *trenton = create_person("Trenton", 19);
	NODE *ret = create_node(trenton);
	assert(ret != NULL);
	assert(ret->next == NULL);
	assert(ret->data == trenton);
	free(ret);
	free_person(trenton);
	printf("Test 02: Test Create Node Person - SUCCESS\n");
}

void test_create_list(void) {
	printf("Test 03: Test Create List - RUN\n");
	LIST *d = create_list();
	assert(d != NULL);
	assert(d->head == NULL);
	assert(d->size == 0);
	destroy(d, free_person);
	printf("Test 03: Test Create List - SUCCESS\n");
}

void test_push_front_null(void) {
	printf("Test 04: Test Push Front NULL - RUN\n");
	push_front(NULL, NULL);
	printf("Test 04: Test Push Front NULL - SUCCESS\n");
}

void test_push_front_0(void) {
	printf("Test 05: Test Push Front 0 - RUN\n");
	LIST *d = create_list();
	person *andrew = create_person("Andrew", 26);
	push_front(d, andrew);
	assert(d->size == 1);
	assert(d->head != NULL);
	NODE *n = d->head;
	assert(n->data == andrew);
	assert(n->next == NULL);

	destroy(d, free_person);
	printf("Test 05: Test Push Front 0 - SUCCESS\n");
}

void test_push_front_1(void) {
	printf("Test 06: Test Push Front 1 - RUN\n");
	LIST *d = create_list();
	person *andrew = create_person("Andrew", 26);
	person *bob = create_person("Bob", 30);
	push_front(d, andrew);
	push_front(d,bob);
	assert(d->size == 2);
	NODE *n = d->head;
	assert(n != NULL);
	assert(n->data == bob);

	NODE *m = n->next;
	assert(m->data == andrew);

	destroy(d, free_person);
	printf("Test 06: Test Push Front 1 - SUCCESS\n");
}

void test_push_front_3(void) {
	printf("Test 07: Test Push Front 3 - RUN\n");
	LIST *d = create_list();
	person *andrew = create_person("Andrew", 26);
	person *austin = create_person("Austin", 19);
	person *sai = create_person("Sai", 20);
	person *trenton = create_person("Trenton", 10);
	push_front(d, andrew);
	push_front(d, austin);
	push_front(d, sai);
	push_front(d,trenton);
	assert(d->size == 4);
	NODE *n = d->head;
	assert(n->data == trenton);

	destroy(d, free_person);
	printf("Test 07: Test Push Front 3 - SUCCESS\n");
}

void test_pop_front_null(void) {
	printf("Test 08: Test Pop Back NULL - RUN\n");
	void *ret = pop_front(NULL);
	assert(ret == NULL);
	printf("Test 08: Test Pop Back NULL - SUCCESS\n");
}

void test_pop_front_0(void) {
	printf("Test 09: Test Pop Back 0 - RUN\n");
	LIST *d = create_list();
	void *ret = pop_front(d);
	assert(ret == NULL);

	destroy(d, free_person);
	printf("Test 09: Test Pop Back 0 - SUCCESS\n");
}

void test_pop_front_1(void) {
	printf("Test 10: Test Pop Back 1 - RUN\n");
	LIST *d = create_list();
	person *sean = create_person("Sean", 19);
	push_front(d, sean);
	void *ret = pop_front(d);
	assert(ret != NULL);
	assert(ret == sean);
	free_person(ret);

	assert(d->size == 0);
	assert(d->head == NULL);
	destroy(d, free_person);
	printf("Test 10: Test Pop Back 1 - SUCCESS\n");
}

void test_pop_front_3(void) {
	printf("Test 11: Test Pop Back 3 - RUN\n");
	LIST *d = create_list();
	person *andrew = create_person("Andrew", 26);
	person *austin = create_person("Austin", 19);
	person *sai = create_person("Sai", 20);
	person *trenton = create_person("Trenton", 10);
	push_front(d, andrew);
	push_front(d, austin);
	push_front(d, sai);
	push_front(d, trenton);

	void *ret = pop_front(d);

	assert(ret == trenton);
	free_person(ret);

	assert(d->size == 3);
	assert(d->head->data == sai);

	destroy(d, free_person);
	printf("Test 11: Test Pop Back 3 - SUCCESS\n");
}

void test_destroy_null(void) {
	printf("Test 16: Test Destroy NULL - RUN\n");
	destroy(NULL, NULL);
	printf("Test 16: Test Destroy NULL - SUCCESS\n");
}

void test_destroy_3(void) {
	printf("Test 17: Test Destroy 3 - RUN\n");
	LIST *d = create_list();
	person *andrew = create_person("Andrew", 26);
	person *austin = create_person("Austin", 19);
	person *sai = create_person("Sai", 20);
	person *trenton = create_person("Trenton", 10);
	push_front(d, andrew);
	push_front(d, austin);
	push_front(d, sai);
	push_front(d, trenton);
	destroy(d, free_person);
	printf("Test 17: Test Destroy 3 - SUCCESS\n");
}

void test_to_array_null(void) {
	printf("Test 12: Test To Array NULL - RUN\n");
	to_array(NULL, sizeof(person));
	printf("Test 12: Test To Array NULL - SUCCESS\n");
}
void test_to_array_0(void) {
	printf("Test 13: Test To Array 0 - RUN\n");
	LIST *d = create_list();
	void **ret = to_array(d, sizeof(person));
	assert(ret == NULL);
	destroy(d, free_person);
	printf("Test 13: Test To Array 0 - SUCCESS\n");
}

void test_to_array_1(void) {
	printf("Test 14: Test To Array 1 - RUN\n");
	LIST *d = create_list();
	person *trenton = create_person("Trenton", 19);
	push_front(d, trenton);
 	person *ret = to_array(d, sizeof(person));
	person arr[] = {*trenton};
	assert(ret[0].age == arr[0].age);
	assert(ret[0].name == arr[0].name);
	free(ret);
	destroy(d, free_person);
	printf("Test 14: Test To Array 1 - SUCCESS\n");
}

void test_to_array_3(void) {
	printf("Test 15: Test To Array 2 - RUN\n");
	LIST *d = create_list();
	person *andrew = create_person("Andrew", 26);
	person *austin = create_person("Austin", 19);
	person *sai = create_person("Sai", 20);
	person *trenton = create_person("Trenton", 10);
	push_front(d, andrew);
	push_front(d, austin);
	push_front(d, sai);
	push_front(d, trenton);
	person *ret = to_array(d, sizeof(person));
	person arr[] = {*trenton, *sai, *austin, *andrew};
	for(int x = 0; x < 4; x++) {
	  assert(ret[x].age == arr[x].age);
	  assert(ret[x].name == arr[x].name);
	}
	free(ret);
	destroy(d, free_person);
	printf("Test 15: Test To Array 2 - SUCCESS\n");
}
