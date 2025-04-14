#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_A 20
#define MAX_M 10

typedef struct {
    int data[MAX_M];
} Subsequence;

// 比較函式，用於 qsort 排序子序列
int compare(const void *a, const void *b) {
    Subsequence *sub1 = (Subsequence *)a;
    Subsequence *sub2 = (Subsequence *)b;
    for (int i = 0; i < MAX_M; i++) {
        if (sub1->data[i] != sub2->data[i]) {
            return sub1->data[i] - sub2->data[i];
        }
    }
    return 0;
}

// 檢查子序列是否包含重複元素
int is_unique(int *arr, int m) {
    int seen[10] = {0};  // 數字範圍 0~9
    for (int i = 0; i < m; i++) {
        if (seen[arr[i]]) return 0;  // 發現重複數字
        seen[arr[i]] = 1;
    }
    return 1;
}

int main() {
    int m, a = 0;
    int sequence[MAX_A];
    Subsequence subs[MAX_A];  // 用來存符合條件的子序列
    int count = 0;
    char line[100];  // 存儲整數序列的輸入行

    // 讀取 m 值
    scanf("%d", &m);
    getchar();  // 清除換行符

    // 讀取數列
    if (fgets(line, sizeof(line), stdin)) {
        char *token = strtok(line, " ");
        while (token && a < MAX_A) {
            sequence[a++] = atoi(token);
            token = strtok(NULL, " ");
        }
    }

    // 取得所有符合條件的子序列
    for (int i = 0; i <= a - m; i++) {
        if (is_unique(&sequence[i], m)) {
            memcpy(subs[count].data, &sequence[i], m * sizeof(int));  // 複製前 m 個元素
            count++;
        }
    }

    // 排序子序列
    qsort(subs, count, sizeof(Subsequence), compare);

    // 去重並輸出
    int unique_count = 0;
    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        if (i == 0 || memcmp(subs[i].data, subs[i - 1].data, m * sizeof(int)) != 0) {  // ✅ 確保唯一
            unique_count++;
            for (int j = 0; j < m; j++) {
                printf("%d%s", subs[i].data[j], j == m - 1 ? "\n" : " ");
            }
        }
    }

    return 0;
}
