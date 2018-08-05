#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char a;
    char b;
} p;
typedef struct {
    short p;
    char a;
    int b;
} d;

int main() {
    printf("char: %lu\n", sizeof(char));
    printf("short: %lu\n", sizeof(short));
    printf("int: %lu\n", sizeof(int));
    printf("long: %lu\n", sizeof(long));
    printf("char*: %lu\n", sizeof(char*));
    printf("int*: %lu\n", sizeof(int*));
    printf("void*: %lu\n", sizeof(void*));
    printf("int**: %lu\n", sizeof(int**));
    p struct1 = {1, 2};
    d struct2 = {1, 2, 3};
    printf("struct1: %lu\n", sizeof(p));
    printf("struct2: %lu\n", sizeof(d));
}


