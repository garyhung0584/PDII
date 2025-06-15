#include <stdlib.h>
#include <stdio.h>

#define MAX 100

typedef struct Node
{
    int duration;
    int indegree;
    int fromCount;
    int from[MAX];
} Node;

int max(int a, int b)
{
    return a > b ? a : b;
}

int getResult(int M, Node nodes[])
{
    int queue[MAX], front = 0, rear = 0;
    int dp[MAX] = {0};


    for (int i = 1; i < M; i++)
    {
        if (nodes[i].indegree == 0)
        {
            dp[i] = nodes[i].duration;
            queue[rear++] = i;
        }
    }

    while (front < rear)
    {
        int curr = queue[front++];
        for (int i = 1; i <= M; i++)
        {
            for (int j = 0; j < nodes[i].fromCount; j++)
            {
                if (nodes[i].from[j] == curr)
                {
                    nodes[i].indegree--;
                    dp[i] = max(dp[i], dp[curr] + nodes[i].duration);
                    if (nodes[i].indegree == 0){
                        queue[rear++] = i;
                    }
                }

            }
        }
    }
    // 找出最大時間
    int maxTime = 0;
    for (int i = 1; i <= M; i++) {
        maxTime = max(maxTime, dp[i]);
    }

    return maxTime;
}



int main()
{
    int N;
    scanf("%d", &N);
    while (N--)
    {
        int M;
        scanf("%d", &M);
        Node nodes[MAX];

        for (int i = 1; i <= M; i++)
        {
            int duration, K;
            scanf("%d %d", &duration, &K);
            nodes[i].duration = duration;


            for (int j = 0; j < K; j++)
            {
                int target;
                scanf("%d", &target);
                nodes[target].from[nodes[target].fromCount++] = i;
                nodes[target].indegree++;
            }
        }

        int result = getResult(M, nodes);
        printf("%d\n", result);
    }

    return 0;
}
