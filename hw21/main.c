#include <stdio.h>

void selectionSort(int d[], int n, int *compareCount, int *moveCount) {
    *compareCount = 0;
    *moveCount = 0;

    for (int i = 0; i < n - 1; i++) {
        int index = i;
        for (int j = i + 1; j < n; j++) {
            (*compareCount)++; // �p�� d[i] ���������
            if (d[j] < d[index]) {
                index = j;
            }
        }

        if (index != i) {
            // ����洫�A��@�h�� 3 ��
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
        (*moveCount)++; // target ��J�Ȧs�]�h�� 1 ���^
        int j = i;

        while (1) {
            (*compareCount)++; // �p�� j > 0 ���������
            if (j > 0) {
                (*compareCount)++; // �p�� a[j-1] > target ���������
                if (a[j - 1] > target) {
                    a[j] = a[j - 1];
                    (*moveCount)++; // �h�� 1 ��
                    j--;
                    continue;
                }
            }
            break;
        }

        a[j] = target;
        (*moveCount)++; // target �g�J a[j]�]�h�� 1 ���^
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int data1[15], data2[15];
    for (int i = 0; i < n; i++) {
        scanf("%d", &data1[i]);
        data2[i] = data1[i]; // �ƻs��l�}�C
    }

    int selCmp, selMov, insCmp, insMov;
    selectionSort(data1, n, &selCmp, &selMov);
    insertionSort(data2, n, &insCmp, &insMov);

    printf("%d %d\n", selCmp, selMov);
    printf("%d %d\n", insCmp, insMov);

    return 0;
}
