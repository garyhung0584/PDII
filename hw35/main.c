#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int coeff;          // �Ӷ��Y��
    int exp;            // �Ӷ�����
    struct Node *next;  // ���V�U�@�`�I
} Node;

// �إߤ@�ӷs���`�I
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

// �N (coeff, exp) �[�J���쵲����ݡ]�O�ҿ�J���ǬO�q�������C����^
void appendTerm(Node **head, Node **tail, int coeff, int exp) {
    if (coeff == 0) return; // �Y�Y�Ƭ� 0�A���b�쵲��إ߸`�I
    Node *p = createNode(coeff, exp);
    if (*head == NULL) {
        *head = *tail = p;
    } else {
        (*tail)->next = p;
        *tail = p;
    }
}

// Ū���@���r�A�ѪR�X�Ҧ���ơA�ëإ��쵲��]�u�s��D�s�Y�ơ^�A��^ head ����
Node* readPolynomial() {
    char buffer1[10000], buffer2[10000];
    // Ū���@���A�]�A�Ů�M����
    if (fgets(buffer1, sizeof(buffer1), stdin) == NULL) {
        return NULL;
    }
    // �ƻs�@���Ω�ĤG���ѪR
    strcpy(buffer2, buffer1);

    // �Ĥ@���ϥ� strtok �έp�X�{ token ���Ӽ�
    int count = 0;
    char *token = strtok(buffer1, " \t\r\n");
    while (token) {
        count++;
        token = strtok(NULL, " \t\r\n");
    }
    if (count == 0) return NULL;

    // �N�U�� token �ഫ����ơA�x�s�b coeffs[] �}�C
    int *coeffs = (int*)malloc(count * sizeof(int));
    int idx = 0;
    token = strtok(buffer2, " \t\r\n");
    while (token) {
        coeffs[idx++] = atoi(token);
        token = strtok(NULL, " \t\r\n");
    }

    // �إ��쵲��ɻݭn���D�̰�����O count-1�A�̧ǩ��U�� 0
    Node *head = NULL, *tail = NULL;
    for (int i = 0; i < count; i++) {
        int exp = (count - 1) - i;
        int c = coeffs[i];
        appendTerm(&head, &tail, c, exp);
    }

    free(coeffs);
    return head;
}

// �X�֨�Ӥw�Ƨǡ]�� exp �Ѥj��p�^���h�����쵲��A�ñN�M�s��s���쵲��]�� exp �Ѥj��p�^
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
                // p1 �����A�� p2 �S��������
                appendTerm(&rHead, &rTail, p1->coeff, p1->exp);
                p1 = p1->next;
            } else {
                // p2 �����A�� p1 �S��������
                appendTerm(&rHead, &rTail, p2->coeff, p2->exp);
                p2 = p2->next;
            }
        } else if (p1) {
            // �u�� p1 �٦��Ѿl��
            appendTerm(&rHead, &rTail, p1->coeff, p1->exp);
            p1 = p1->next;
        } else {
            // �u�� p2 �٦��Ѿl��
            appendTerm(&rHead, &rTail, p2->coeff, p2->exp);
            p2 = p2->next;
        }
    }

    return rHead;
}

// ���D�خ榡��X�h�����A�p�G�쵲���š]�Y�Ҧ����ۥ[��Ҭ� 0�^�A�h��X "0"
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
            // �L�X�Ĥ@���G���ݭn�ˬd�e�� '+'
            if (coef < 0) {
                // �Y�Ĥ@���Y�Ƭ��t�A���L '-'
                printf("-");
            }
            // �̦�����O�B�z

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
                // �`�ƶ�
                printf("%d", absCoef);
            }

            first = 0;
        } else {
            // ���򶵡G�ݮھڥ��t�L '+' �� '-'
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

// �������쵲���O����
void freeList(Node *head) {
    Node *p;
    while (head) {
        p = head->next;
        free(head);
        head = p;
    }
}

int main() {
    // Ū����Ӧh����
    Node *poly1 = readPolynomial();
    Node *poly2 = readPolynomial();

    // �ۥ[
    Node *sumPoly = addPolynomials(poly1, poly2);

    // ��X
    printPolynomial(sumPoly);

    // ����O����
    freeList(poly1);
    freeList(poly2);
    freeList(sumPoly);

    return 0;
}
