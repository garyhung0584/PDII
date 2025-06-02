#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
    int data;
    struct node_s *next;
} node_t;
typedef node_t *nodep_t;

/* Stack globals */
nodep_t stack_top = NULL;

/* Queue globals */
nodep_t queue_head = NULL;
nodep_t queue_tail = NULL;

/* --- Stack functions --- */
void stack_push(int x) {
    nodep_t new_node = (nodep_t)malloc(sizeof(node_t));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = x;
    new_node->next = stack_top;
    stack_top = new_node;
}

void stack_pop() {
    if (stack_top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    printf("%d\n", stack_top->data);
    nodep_t tmp = stack_top;
    stack_top = stack_top->next;
    free(tmp);
}

void stack_top_fun() {
    if (stack_top == NULL) {
        printf("Stack is empty\n");
    } else {
        printf("%d\n", stack_top->data);
    }
}

void stack_empty_fun() {
    if (stack_top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    while (stack_top != NULL) {
        nodep_t tmp = stack_top;
        stack_top = stack_top->next;
        free(tmp);
    }
}

void stack_print() {
    if (stack_top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    for (nodep_t cur = stack_top; cur != NULL; cur = cur->next) {
        printf("%d\n", cur->data);
    }
}

/* --- Queue functions --- */
void queue_push(int x) {
    nodep_t new_node = (nodep_t)malloc(sizeof(node_t));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = x;
    new_node->next = NULL;
    if (queue_tail == NULL) {
        /* Empty queue */
        queue_head = queue_tail = new_node;
    } else {
        queue_tail->next = new_node;
        queue_tail = new_node;
    }
}

void queue_pop() {
    if (queue_head == NULL) {
        printf("Queue is empty\n");
        return;
    }
    printf("%d\n", queue_head->data);
    nodep_t tmp = queue_head;
    queue_head = queue_head->next;
    if (queue_head == NULL) {
        /* Now empty */
        queue_tail = NULL;
    }
    free(tmp);
}

void queue_front_fun() {
    if (queue_head == NULL) {
        printf("Queue is empty\n");
    } else {
        printf("%d\n", queue_head->data);
    }
}

void queue_empty_fun() {
    if (queue_head == NULL) {
        printf("Queue is empty\n");
        return;
    }
    while (queue_head != NULL) {
        nodep_t tmp = queue_head;
        queue_head = queue_head->next;
        free(tmp);
    }
    queue_tail = NULL;
}

void queue_print() {
    if (queue_head == NULL) {
        printf("Queue is empty\n");
        return;
    }
    for (nodep_t cur = queue_head; cur != NULL; cur = cur->next) {
        printf("%d\n", cur->data);
    }
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) {
        return 0;
    }

    for (int i = 0; i < N; i++) {
        char ds[16], op[16];
        scanf("%s %s", ds, op);

        if (strcmp(ds, "stack") == 0) {
            if (strcmp(op, "push") == 0) {
                int x;
                scanf("%d", &x);
                stack_push(x);
            } else if (strcmp(op, "pop") == 0) {
                stack_pop();
            } else if (strcmp(op, "top") == 0) {
                stack_top_fun();
            } else if (strcmp(op, "empty") == 0) {
                stack_empty_fun();
            } else if (strcmp(op, "print") == 0) {
                stack_print();
            }
        } else if (strcmp(ds, "queue") == 0) {
            if (strcmp(op, "push") == 0) {
                int x;
                scanf("%d", &x);
                queue_push(x);
            } else if (strcmp(op, "pop") == 0) {
                queue_pop();
            } else if (strcmp(op, "front") == 0) {
                queue_front_fun();
            } else if (strcmp(op, "empty") == 0) {
                queue_empty_fun();
            } else if (strcmp(op, "print") == 0) {
                queue_print();
            }
        }
    }

    /* Clean up any remaining nodes before exit (not strictly required) */
    while (stack_top != NULL) {
        nodep_t tmp = stack_top;
        stack_top = stack_top->next;
        free(tmp);
    }
    while (queue_head != NULL) {
        nodep_t tmp = queue_head;
        queue_head = queue_head->next;
        free(tmp);
    }

    return 0;
}
