#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a = 10;                   // stack allocation
    int *b = malloc(sizeof(int)); // heap allocation
    *b = 20;

    printf("%d %d\n", a, *b);

    free(b);
    return 0;
}