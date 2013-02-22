#include <stdio.h>
#include <stdlib.h>

int add(const int *, const int *);
int multiply(const int *, const int *);
void operate(const int *, const int *, int *, int(*functionPtr)(const int *, const int *));

int globalvar = 0;

int main(int argc, char **argv) {
    static double staticvar = 0.0;
    printf("The memory address of global variable globalvar is %p\n", &globalvar);
    printf("The memory address of static variable staticvar is %p\n", &staticvar);
    printf("\n");

    int a = 4;
    int b = 3;
    printf("The memory address of local variable a is %p\n", &a);
    printf("The memory address of local variable b is %p\n", &b);
    printf("\n");

    int *c = malloc(sizeof(int));
    int *d = malloc(sizeof(int));
    printf("The memory address of heap variable c is %p\n", c);
    printf("The memory address of heap variable d is %p\n", d);
    printf("\n");

    printf("The memory address of the function add is %p\n", &add);
    printf("The memory address of the function multiply is %p\n", &multiply);
    printf("\n");

    printf("Ok, now let's try to add, by asking the operate function to use the add function...\n");
    operate(&a, &b, c, &add);
    printf("The contents of malloc'd space %p, \"c\", is %d\n", c, *c);
    printf("\n");

    printf("Ok, now let's try to multiply, by asking the operate function to use the multiply function...\n");
    operate(&a, &b, &globalvar, &multiply);
    printf("The contents of global variable %p, \"globalvar\", is %d\n", &globalvar, globalvar);

    free(c);
    free(d);
    return 0;
}

void operate(const int *a, const int *b, int *dest, int (*operationPtr)(const int *, const int*)) {
    printf("  (inside operate) Storing into %p results of operation at memory address %p\n", dest, operationPtr);
    *dest = (*operationPtr)(a, b);
}

int add(const int *a, const int *b) {
    printf("    (inside add) Adding the contents of %p and %p. (%d+%d)\n", a, b, *a, *b);
    return *a + *b;
}

int multiply(const int *a, const int *b) {
    printf("    (inside multiply) Multiplying the contents of %p and %p. (%d*%d)\n", a, b, *a, *b);
    return *a * *b;
}
