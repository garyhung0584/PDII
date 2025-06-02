#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int coeff;          // 該項係數
    int exp;            // 該項次方
    struct Node *next;  // 指向下一節點
} Node;

// 建立一個新的節點
Node* createNode(int coeff, int exp) {
    Node *p = (Node*)malloc(sizeof(Node));
    if (!p) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    p->coeff = coeff;
    p->exp = exp;
    p->next = NULL;
    return p;
}

// 將 (coeff, exp) 加入到鏈結表尾端（保證輸入順序是從高次方到低次方）
void appendTerm(Node **head, Node **tail, int coeff, int exp) {
    if (coeff == 0) return; // 若係數為 0，不在鏈結表建立節點
    Node *p = createNode(coeff, exp);
    if (*head == NULL) {
        *head = *tail = p;
    } else {
        (*tail)->next = p;
        *tail = p;
    }
}

// 讀取一行文字，解析出所有整數，並建立鏈結表（只存放非零係數），返回 head 指標
Node* readPolynomial() {
    char buffer1[10000], buffer2[10000];
    // 讀取一整行，包括空格和換行
    if (fgets(buffer1, sizeof(buffer1), stdin) == NULL) {
        return NULL;
    }
    // 複製一份用於第二次解析
    strcpy(buffer2, buffer1);

    // 第一次使用 strtok 統計出現 token 的個數
    int count = 0;
    char *token = strtok(buffer1, " \t\r\n");
    while (token) {
        count++;
        token = strtok(NULL, " \t\r\n");
    }
    if (count == 0) return NULL;

    // 將各個 token 轉換為整數，儲存在 coeffs[] 陣列
    int *coeffs = (int*)malloc(count * sizeof(int));
    int idx = 0;
    token = strtok(buffer2, " \t\r\n");
    while (token) {
        coeffs[idx++] = atoi(token);
        token = strtok(NULL, " \t\r\n");
    }

    // 建立鏈結表時需要知道最高次方是 count-1，依序往下到 0
    Node *head = NULL, *tail = NULL;
    for (int i = 0; i < count; i++) {
        int exp = (count - 1) - i;
        int c = coeffs[i];
        appendTerm(&head, &tail, c, exp);
    }

    free(coeffs);
    return head;
}

// 合併兩個已排序（依 exp 由大到小）的多項式鏈結表，並將和存於新的鏈結表（依 exp 由大到小）
Node* addPolynomials(Node *p1, Node *p2) {
    Node *rHead = NULL, *rTail = NULL;

    while (p1 != NULL || p2 != NULL) {
        if (p1 && p2) {
            if (p1->exp == p2->exp) {
                int sum = p1->coeff + p2->coeff;
                if (sum != 0) {
                    appendTerm(&rHead, &rTail, sum, p1->exp);
                }
                p1 = p1->next;
                p2 = p2->next;
            } else if (p1->exp > p2->exp) {
                // p1 中有，但 p2 沒有此次方
                appendTerm(&rHead, &rTail, p1->coeff, p1->exp);
                p1 = p1->next;
            } else {
                // p2 中有，但 p1 沒有此次方
                appendTerm(&rHead, &rTail, p2->coeff, p2->exp);
                p2 = p2->next;
            }
        } else if (p1) {
            // 只有 p1 還有剩餘項
            appendTerm(&rHead, &rTail, p1->coeff, p1->exp);
            p1 = p1->next;
        } else {
            // 只有 p2 還有剩餘項
            appendTerm(&rHead, &rTail, p2->coeff, p2->exp);
            p2 = p2->next;
        }
    }

    return rHead;
}

// 依題目格式輸出多項式，如果鏈結表為空（即所有項相加後皆為 0），則輸出 "0"
void printPolynomial(Node *head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }

    Node *p = head;
    int first = 1;
    while (p) {
        int coef = p->coeff;
        int exp = p->exp;
        int absCoef = (coef < 0) ? -coef : coef;

        if (first) {
            // 印出第一項：不需要檢查前導 '+'
            if (coef < 0) {
                // 若第一項係數為負，先印 '-'
                printf("-");
            }
            // 依次方分別處理

            if (exp > 1) {
                if (absCoef == 1) {
                    printf("x^%d", exp);
                } else {
                    printf("%dx^%d", absCoef, exp);
                }
            } else if (exp == 1) {
                if (absCoef == 1) {
                    printf("x");
                } else {
                    printf("%dx", absCoef);
                }
            } else { // exp == 0
                // 常數項
                printf("%d", absCoef);
            }

            first = 0;
        } else {
            // 後續項：需根據正負印 '+' 或 '-'
            if (coef > 0) {
                printf("+");
            } else {
                printf("-");
            }

            if (exp > 1) {
                if (absCoef == 1) {
                    printf("x^%d", exp);
                } else {
                    printf("%dx^%d", absCoef, exp);
                }
            } else if (exp == 1) {
                if (absCoef == 1) {
                    printf("x");
                } else {
                    printf("%dx", absCoef);
                }
            } else { // exp == 0
                printf("%d", absCoef);
            }
        }

        p = p->next;
    }

    printf("\n");
}

// 釋放整個鏈結表的記憶體
void freeList(Node *head) {
    Node *p;
    while (head) {
        p = head->next;
        free(head);
        head = p;
    }
}

int main() {
    // 讀取兩個多項式
    Node *poly1 = readPolynomial();
    Node *poly2 = readPolynomial();

    // 相加
    Node *sumPoly = addPolynomials(poly1, poly2);

    // 輸出
    printPolynomial(sumPoly);

    // 釋放記憶體
    freeList(poly1);
    freeList(poly2);
    freeList(sumPoly);

    return 0;
}
