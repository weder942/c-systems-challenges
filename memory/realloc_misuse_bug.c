#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t count = 4;
    int *values = malloc(count * sizeof(int));
    if (values == NULL) {
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        values[i] = (int)(i + 1);
    }

    count = 1000000000000ULL;
    values = realloc(values, count * sizeof(int));
    if (values == NULL) {
        fprintf(stderr, "Falha ao redimensionar buffer\n");
        return 1;
    }

    printf("Primeiro valor: %d\n", values[0]);

    free(values);
    return 0;
}
