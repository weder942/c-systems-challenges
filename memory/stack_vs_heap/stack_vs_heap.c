#include <stdio.h>
#include <stdlib.h>

int *create_stack()
{
    int x = 10;
    printf("Endereco de x: %p\n", (void *)&x);
    return &x;
}

int *create_heap()
{
    int *x = malloc(sizeof(int));
    *x = 20;
    return x;
}

int main()
{
    int *a = create_stack();
    printf("Endereco de a: %p\n", (void *)a);
    int *b = create_heap();

    printf("Stack: %d\n", *a);
    printf("Heap: %d\n", *b);

    free(b);

    return 0;
}