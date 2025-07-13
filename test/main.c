#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct dnode_s
{
    int data;
    struct dnode_s * front;
    struct dnode_s * back;
} node_t;
typedef node_t * nodep_t;




int main()
{
    // Global pointers for head and tail of the list, and length counter
    nodep_t head = NULL;
    nodep_t tail = NULL;
    int len = 0;

    nodep_t creatNode(int data)
    {
        nodep_t node = malloc(sizeof(node_t));

        node->data = data;
        node->front = NULL;
        node->back = NULL;
        return node;
    }
    void addFront(int val)
    {
        nodep_t node = creatNode(val);
        if (head == NULL)
        {
            head = node;
            tail = node;
        }
        else
        {
            node->back = head;
            head->front = node;
            head = node;
        }
        len++;
    }

    void addBack(int val)
    {
        nodep_t node = creatNode(val);
        if (tail == NULL)
        {
            head = node;
            tail = node;
        }
        else
        {
            node->front = tail;
            tail->back = node;
            tail = node;
        }
        len++;
    }
    void removeFront()
    {
        if(len == 0)
        {
            printf("Double link list is empty");
            return;
        }
        nodep_t tmp = head;
        if (head == tail)
        {
            head = tail = NULL;
        }
        else
        {
            head = head->back;
            head->front = NULL;
        }
        free(tmp);
        len--;
    }
    void removeBack()
    {
        if(len == 0)
        {
            printf("Double link list is empty");
            return;
        }
        nodep_t tmp = tail;
        if (head == tail)
        {
            head = tail = NULL;
        }
        else
        {
            tail = tail->front;
            tail->back = NULL;
        }
        free(tmp);
        len--;
    }
    void empty()
    {
        if (len == 0)
        {
            printf("Double link list is empty\n");
            return;
        }
        nodep_t curr = head;
        while (curr)
        {
            removeFront();
            curr = head;
        }
    }
// Insert a new node with 'data' after the n-th node (1-based index)
    void insert(int n, int data)
    {
        if (n > len)
        {
            printf("Invalid command\n");
            return;
        }
        // Traverse to the n-th node
        nodep_t cur = head;
        for (int i = 1; i < n; i++)
        {
            cur = cur->back;
        }
        // Now cur points to the n-th node
        nodep_t newNode = creatNode(data);
        newNode->front = cur;
        newNode->back = cur->back;
        if (cur->back)
        {
            cur->back->front = newNode;
        }
        else
        {
            // cur was tail
            tail = newNode;
        }
        cur->back = newNode;
        len++;
    }

// Remove the n-th node (1-based index)
    void remove(int n)
    {
        if (n > len)
        {
            printf("Invalid command\n");
            return;
        }
        // Traverse to the n-th node
        nodep_t cur = head;
        for (int i = 1; i < n; i++)
        {
            cur = cur->back;
        }
        // Remove cur
        if (cur->front)
        {
            cur->front->back = cur->back;
        }
        else
        {
            // cur was head
            head = cur->back;
        }
        if (cur->back)
        {
            cur->back->front = cur->front;
        }
        else
        {
            // cur was tail
            tail = cur->front;
        }
        free(cur);
        len--;
    }

// Print all nodes from head to tail, one per line
    void print()
    {
        if (len == 0)
        {
            printf("Double link list is empty\n");
            return;
        }
        nodep_t cur = head;
        while (cur)
        {
            printf("%d\n", cur->data);
            cur = cur->back;
        }
    }



    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        char cmd[20];
        scanf("%s", cmd);

        if (strcmp(cmd, "addFront") == 0)
        {
            int val;
            scanf("%d", &val);
            addFront(val);
        }
        else if (strcmp(cmd, "addBack") == 0)
        {
            int val;
            scanf("%d", &val);
            addBack(val);
        }
        else if (strcmp(cmd, "removeFront") == 0)
        {
            removeFront();
        }
        else if (strcmp(cmd, "removeBack") == 0)
        {
            removeBack();
        }
        else if (strcmp(cmd, "empty") == 0)
        {
            empty();
        }
        else if (strcmp(cmd, "insert") == 0)
        {
            int n, val;
            scanf("%d %d", &n, &val);
            insert(n, val);
        }
        else if(strcmp(cmd, "remove") == 0)
        {
            int n;
            scanf("%d", &n);
            remove(n);
        }
        else if (strcmp(cmd, "print") == 0)
        {
            print();
        }
    }
    return 0;
}
