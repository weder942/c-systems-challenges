#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_message(const char *name) {
    char *buffer = malloc(100);
    if (buffer == NULL) {
        return NULL;
    }

    sprintf(buffer, "Olá, %s!", name);
    return buffer;
}

int main(void) {
    char *msg1 = create_message("Weder");
    char *msg2 = create_message("Silva");

    if (msg1 != NULL) {
        printf("%s\n", msg1);
    }

    if (msg2 != NULL) {
        printf("%s\n", msg2);
    }

    return 0;
}
