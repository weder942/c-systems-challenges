#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *append(Node *head, int value) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return head;
    }

    new_node->value = value;
    new_node->next = NULL;

    if (head == NULL) {
        return new_node;
    }

    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return head;
}

Node *remove_head(Node *head) {
    if (head == NULL) {
        return NULL;
    }

    free(head);
    return head->next;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d\n", current->value);
        current = current->next;
    }
}

int main(void) {
    Node *head = NULL;

    head = append(head, 1);
    head = append(head, 2);
    head = append(head, 3);

    head = remove_head(head);
    print_list(head);

    return 0;
}
