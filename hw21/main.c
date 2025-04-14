#include <stdio.h>

void selectionSort(int d[], int n, int *compareCount, int *moveCount) {
    *compareCount = 0;
    *moveCount = 0;

    for (int i = 0; i < n - 1; i++) {
        int index = i;
        for (int j = i + 1; j < n; j++) {
            (*compareCount)++; // 計算 d[i] 的比較次數
            if (d[j] < d[index]) {
                index = j;
            }
        }

        if (index != i) {
            // 執行交換，算作搬移 3 次
            int temp = d[i];
            d[i] = d[index];
            d[index] = temp;
            (*moveCount) += 3;
        }
    }
}

void insertionSort(int a[], int n, int *compareCount, int *moveCount) {
    *compareCount = 0;
    *moveCount = 0;

    for (int i = 1; i < n; i++) {
        int target = a[i];
        (*moveCount)++; // target 放入暫存（搬移 1 次）
        int j = i;

        while (1) {
            (*compareCount)++; // 計算 j > 0 的比較次數
            if (j > 0) {
                (*compareCount)++; // 計算 a[j-1] > target 的比較次數
                if (a[j - 1] > target) {
                    a[j] = a[j - 1];
                    (*moveCount)++; // 搬移 1 次
                    j--;
                    continue;
                }
            }
            break;
        }

        a[j] = target;
        (*moveCount)++; // target 寫入 a[j]（搬移 1 次）
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int data1[15], data2[15];
    for (int i = 0; i < n; i++) {
        scanf("%d", &data1[i]);
        data2[i] = data1[i]; // 複製原始陣列
    }

    int selCmp, selMov, insCmp, insMov;
    selectionSort(data1, n, &selCmp, &selMov);
    insertionSort(data2, n, &insCmp, &insMov);

    printf("%d %d\n", selCmp, selMov);
    printf("%d %d\n", insCmp, insMov);

    return 0;
}
