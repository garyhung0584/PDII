#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dnode_s {
    int data;
    struct dnode_s *front;  // points to previous node
    struct dnode_s *back;   // points to next node
} node_t;

typedef node_t* nodep_t;

// Global pointers for head and tail of the list, and length counter
nodep_t head = NULL;
nodep_t tail = NULL;
int len = 0;

// Create a new node with given data
nodep_t create_node(int data) {
    nodep_t newNode = (nodep_t)malloc(sizeof(node_t));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->front = NULL;
    newNode->back = NULL;
    return newNode;
}

// Insert at the front (head) of the list
void add_front(int data) {
    nodep_t newNode = create_node(data);
    if (head == NULL) {
        head = tail = newNode;
    } else {
        newNode->back = head;
        head->front = newNode;
        head = newNode;
    }
    len++;
}

// Insert at the back (tail) of the list
void add_back(int data) {
    nodep_t newNode = create_node(data);
    if (tail == NULL) {
        head = tail = newNode;
    } else {
        tail->back = newNode;
        newNode->front = tail;
        tail = newNode;
    }
    len++;
}

// Remove the front (head) node
void remove_front() {
    if (len == 0) {
        printf("Double link list is empty\n");
        return;
    }
    nodep_t tmp = head;
    if (head == tail) {
        // Only one node
        head = tail = NULL;
    } else {
        head = head->back;
        head->front = NULL;
    }
    free(tmp);
    len--;
}

// Remove the back (tail) node
void remove_back() {
    if (len == 0) {
        printf("Double link list is empty\n");
        return;
    }
    nodep_t tmp = tail;
    if (head == tail) {
        // Only one node
        head = tail = NULL;
    } else {
        tail = tail->front;
        tail->back = NULL;
    }
    free(tmp);
    len--;
}

// Delete all nodes in the list
void empty_list() {
    if (len == 0) {
        printf("Double link list is empty\n");
        return;
    }
    nodep_t cur = head;
    while (cur) {
        nodep_t nxt = cur->back;
        free(cur);
        cur = nxt;
    }
    head = tail = NULL;
    len = 0;
}

// Insert a new node with 'data' after the n-th node (1-based index)
void insert_after(int n, int data) {
    if (n > len) {
        printf("Invalid command\n");
        return;
    }
    // Traverse to the n-th node
    nodep_t cur = head;
    for (int i = 1; i < n; i++) {
        cur = cur->back;
    }
    // Now cur points to the n-th node
    nodep_t newNode = create_node(data);
    newNode->front = cur;
    newNode->back = cur->back;
    if (cur->back) {
        cur->back->front = newNode;
    } else {
        // cur was tail
        tail = newNode;
    }
    cur->back = newNode;
    len++;
}

// Remove the n-th node (1-based index)
void remove_nth(int n) {
    if (n > len) {
        printf("Invalid command\n");
        return;
    }
    // Traverse to the n-th node
    nodep_t cur = head;
    for (int i = 1; i < n; i++) {
        cur = cur->back;
    }
    // Remove cur
    if (cur->front) {
        cur->front->back = cur->back;
    } else {
        // cur was head
        head = cur->back;
    }
    if (cur->back) {
        cur->back->front = cur->front;
    } else {
        // cur was tail
        tail = cur->front;
    }
    free(cur);
    len--;
}

// Print all nodes from head to tail, one per line
void print_list() {
    if (len == 0) {
        printf("Double link list is empty\n");
        return;
    }
    nodep_t cur = head;
    while (cur) {
        printf("%d\n", cur->data);
        cur = cur->back;
    }
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) {
        return 0;
    }

    for (int i = 0; i < N; i++) {
        char cmd[20];
        scanf("%s", cmd);

        if (strcmp(cmd, "addFront") == 0) {
            int data;
            scanf("%d", &data);
            add_front(data);

        } else if (strcmp(cmd, "addBack") == 0) {
            int data;
            scanf("%d", &data);
            add_back(data);

        } else if (strcmp(cmd, "removeFront") == 0) {
            remove_front();

        } else if (strcmp(cmd, "removeBack") == 0) {
            remove_back();

        } else if (strcmp(cmd, "empty") == 0) {
            empty_list();

        } else if (strcmp(cmd, "insert") == 0) {
            int n, data;
            scanf("%d %d", &n, &data);
            insert_after(n, data);

        } else if (strcmp(cmd, "remove") == 0) {
            int n;
            scanf("%d", &n);
            remove_nth(n);

        } else if (strcmp(cmd, "print") == 0) {
            print_list();
        }
        // Any other commands can be ignored; problem guarantees valid inputs
    }

    return 0;
}
