#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum scoreType_s { G, GPA, S } scoreType_t;
typedef enum G_s { Aplus, A, Aduce, Bplus, B, Bduce, Cplus, C, Cduce, F, X } G_t;
typedef enum GPA_s { b4dot3, b4dot0, b3dot7, b3dot3, b3dot0, b2dot7, b2dot3, b2dot0, b1dot7, b1, b0 } GPA_t;
typedef enum S_s { b90to100, b85to89, b80to84, b77to79, b73to76, b70to72, b67to69, b63to66, b60to62, b1to59, b0to0 } S_t;

typedef union student_s {
    int score;
    G_t G;
    GPA_t GPA;
    S_t S;
} student_t;

typedef struct {
    int id;
    int avgScore;
} result_t;

int g_table[]   = {95, 87, 82, 78, 75, 70, 68, 65, 60, 50, 0};
int gpa_table[] = {95, 87, 82, 78, 75, 70, 68, 65, 60, 50, 0};
int s_table[]   = {95, 87, 82, 78, 75, 70, 68, 65, 60, 50, 0};

scoreType_t courseType[10];

int getGIndex(char *str) {
    if (strcmp(str, "A+") == 0) return Aplus;
    if (strcmp(str, "A") == 0) return A;
    if (strcmp(str, "A-") == 0) return Aduce;
    if (strcmp(str, "B+") == 0) return Bplus;
    if (strcmp(str, "B") == 0) return B;
    if (strcmp(str, "B-") == 0) return Bduce;
    if (strcmp(str, "C+") == 0) return Cplus;
    if (strcmp(str, "C") == 0) return C;
    if (strcmp(str, "C-") == 0) return Cduce;
    if (strcmp(str, "F") == 0) return F;
    if (strcmp(str, "X") == 0) return X;
    return X;
}

int getGPAIndex(char *str) {
    if (strcmp(str, "4.3") == 0) return b4dot3;
    if (strcmp(str, "4.0") == 0) return b4dot0;
    if (strcmp(str, "3.7") == 0) return b3dot7;
    if (strcmp(str, "3.3") == 0) return b3dot3;
    if (strcmp(str, "3.0") == 0) return b3dot0;
    if (strcmp(str, "2.7") == 0) return b2dot7;
    if (strcmp(str, "2.3") == 0) return b2dot3;
    if (strcmp(str, "2.0") == 0) return b2dot0;
    if (strcmp(str, "1.7") == 0) return b1dot7;
    if (strcmp(str, "1") == 0)   return b1;
    if (strcmp(str, "0") == 0)   return b0;
    return b0;
}

int getSIndex(char *str) {
    if (strcmp(str, "90-100") == 0) return b90to100;
    if (strcmp(str, "85-89") == 0) return b85to89;
    if (strcmp(str, "80-84") == 0) return b80to84;
    if (strcmp(str, "77-79") == 0) return b77to79;
    if (strcmp(str, "73-76") == 0) return b73to76;
    if (strcmp(str, "70-72") == 0) return b70to72;
    if (strcmp(str, "67-69") == 0) return b67to69;
    if (strcmp(str, "63-66") == 0) return b63to66;
    if (strcmp(str, "60-62") == 0) return b60to62;
    if (strcmp(str, "1-59") == 0) return b1to59;
    if (strcmp(str, "0") == 0) return b0to0;
    return b0to0;
}

int cmp(const void *a, const void *b) {
    return ((result_t *)a)->avgScore - ((result_t *)b)->avgScore;
}

int main() {
    int M, N;
    scanf("%d", &M);
    for (int i = 0; i < M; ++i) {
        char type[10];
        scanf("%s", type);
        if (strcmp(type, "G") == 0) courseType[i] = G;
        else if (strcmp(type, "GPA") == 0) courseType[i] = GPA;
        else courseType[i] = S;
    }

    scanf("%d", &N);
    result_t results[10];

    for (int i = 0; i < N; ++i) {
        int id;
        char scoreStr[20];
        student_t scores[10];
        int sum = 0;

        scanf("%d", &id);
        results[i].id = id;

        for (int j = 0; j < M; ++j) {
            scanf("%s", scoreStr);
            int percent = 0;
            switch (courseType[j]) {
                case G:
                    scores[j].G = getGIndex(scoreStr);
                    percent = g_table[scores[j].G];
                    break;
                case GPA:
                    scores[j].GPA = getGPAIndex(scoreStr);
                    percent = gpa_table[scores[j].GPA];
                    break;
                case S:
                    scores[j].S = getSIndex(scoreStr);
                    percent = s_table[scores[j].S];
                    break;
            }
            sum += percent;
        }
        results[i].avgScore = sum / M;
    }

    qsort(results, N, sizeof(result_t), cmp);

    for (int i = 0; i < N; ++i) {
        printf("%d %d\n", results[i].id, results[i].avgScore);
    }

    return 0;
}
