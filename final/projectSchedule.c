#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 105

typedef struct {
    int duration;         // ���������ةһݤѼ�
    int indegree;         // �e�m�`�I�ƶq
    int fromCount;        // ���V�Ӹ`�I���`�I�ƶq
    int from[100];        // ���V�Ӹ`�I���`�I�s��
} Node;

int max(int a, int b) {
    return a > b ? a : b;
}

int calculateProjectDays(int M, Node nodes[]) {
    int queue[MAX_NODES], front = 0, rear = 0;
    int dp[MAX_NODES] = {0}; // ��F�C�Ӹ`�I���̪��ɶ�

    // ��X�J�׬� 0 ���`�I�A�[�J queue
    for (int i = 1; i <= M; i++) {
        if (nodes[i].indegree == 0) {
            dp[i] = nodes[i].duration;
            queue[rear++] = i;
        }
    }

    while (front < rear) {
        int curr = queue[front++];
        for (int i = 1; i <= M; i++) {
            for (int j = 0; j < nodes[i].fromCount; j++) {
                if (nodes[i].from[j] == curr) {
                    nodes[i].indegree--;
                    dp[i] = max(dp[i], dp[curr] + nodes[i].duration);
                    if (nodes[i].indegree == 0) {
                        queue[rear++] = i;
                    }
                }
            }
        }
    }

    // ��X�̤j�ɶ�
    int maxTime = 0;
    for (int i = 1; i <= M; i++) {
        maxTime = max(maxTime, dp[i]);
    }

    return maxTime;
}

int main() {
    int N;
    scanf("%d", &N);

    while (N--) {
        int M;
        scanf("%d", &M);

        Node nodes[MAX_NODES] = {0};

        for (int i = 1; i <= M; i++) {
            int duration, K;
            scanf("%d %d", &duration, &K);
            nodes[i].duration = duration;

            for (int j = 0; j < K; j++) {
                int target;
                scanf("%d", &target);
                nodes[target].from[nodes[target].fromCount++] = i;
                nodes[target].indegree++;
            }
        }

        int result = calculateProjectDays(M, nodes);
        printf("%d\n", result);
    }

    return 0;
}

