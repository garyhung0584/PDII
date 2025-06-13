#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
    char data;
    struct node_s *left, *right;
} tree_t;
typedef tree_t * btree;

// 建立新節點
btree createNode(char data) {
    btree node = (btree)malloc(sizeof(tree_t));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// 在中序中找 root 的 index
int findIndex(char *inorder, char root, int in_start, int in_end) {
    for (int i = in_start; i <= in_end; i++) {
        if (inorder[i] == root) return i;
    }
    return -1;
}

// 由前序與中序建樹
btree buildPreIn(char *preorder, char *inorder, int in_start, int in_end, int *pre_index) {
    if (in_start > in_end) return NULL;

    char root_val = preorder[(*pre_index)++];
    btree root = createNode(root_val);

    if (in_start == in_end) return root;

    int root_index = findIndex(inorder, root_val, in_start, in_end);

    root->left = buildPreIn(preorder, inorder, in_start, root_index - 1, pre_index);
    root->right = buildPreIn(preorder, inorder, root_index + 1, in_end, pre_index);

    return root;
}

// 由後序與中序建樹
btree buildPostIn(char *postorder, char *inorder, int in_start, int in_end, int *post_index) {
    if (in_start > in_end) return NULL;

    char root_val = postorder[(*post_index)--];
    btree root = createNode(root_val);

    if (in_start == in_end) return root;

    int root_index = findIndex(inorder, root_val, in_start, in_end);

    root->right = buildPostIn(postorder, inorder, root_index + 1, in_end, post_index);
    root->left = buildPostIn(postorder, inorder, in_start, root_index - 1, post_index);

    return root;
}

// Queue node for BFS
typedef struct queue_node_s {
    btree node;
    struct queue_node_s *next;
} queue_node_t;

typedef struct {
    queue_node_t *front, *rear;
} queue_t;

void enqueue(queue_t *q, btree node) {
    queue_node_t *new_node = (queue_node_t *)malloc(sizeof(queue_node_t));
    new_node->node = node;
    new_node->next = NULL;
    if (q->rear) q->rear->next = new_node;
    else q->front = new_node;
    q->rear = new_node;
}

btree dequeue(queue_t *q) {
    if (!q->front) return NULL;
    queue_node_t *temp = q->front;
    btree result = temp->node;
    q->front = temp->next;
    if (!q->front) q->rear = NULL;
    free(temp);
    return result;
}

int isEmpty(queue_t *q) {
    return q->front == NULL;
}

// 層序輸出
void levelOrder(btree root) {
    if (!root) return;
    queue_t q = {NULL, NULL};
    enqueue(&q, root);
    while (!isEmpty(&q)) {
        btree node = dequeue(&q);
        printf("%c", node->data);
        if (node->left) enqueue(&q, node->left);
        if (node->right) enqueue(&q, node->right);
    }
}

int main() {
    char type1, type2;
    char A[25], B[25];

    scanf(" %c", &type1);
    scanf("%s", A);
    scanf(" %c", &type2);
    scanf("%s", B);

    btree root = NULL;
    int len = strlen(A);

    if ((type1 == 'P' && type2 == 'I') || (type1 == 'I' && type2 == 'P')) {
        char *preorder = (type1 == 'P') ? A : B;
        char *inorder = (type1 == 'I') ? A : B;
        int pre_index = 0;
        root = buildPreIn(preorder, inorder, 0, len - 1, &pre_index);
    } else if ((type1 == 'O' && type2 == 'I') || (type1 == 'I' && type2 == 'O')) {
        char *postorder = (type1 == 'O') ? A : B;
        char *inorder = (type1 == 'I') ? A : B;
        int post_index = len - 1;
        root = buildPostIn(postorder, inorder, 0, len - 1, &post_index);
    }

    levelOrder(root);
    printf("\n");

    return 0;
}
