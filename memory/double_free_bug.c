#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *numbers = malloc(5 * sizeof(int));
    if (numbers == NULL) {
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        numbers[i] = i * 10;
    }

    free(numbers);

    printf("Primeiro elemento: %d\n", numbers[0]);

    free(numbers);

    return 0;
}
