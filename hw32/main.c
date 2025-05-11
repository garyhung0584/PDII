#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For qsort if needed, or for INT_MIN/INT_MAX if used

// Define INT_MAX and INT_MIN if not available (usually in limits.h)
#ifndef INT_MAX
#define INT_MAX 2147483647
#endif
#ifndef INT_MIN
#define INT_MIN (-2147483647 - 1)
#endif

typedef struct student_s {
    char name[50];
    int score;
} student_t;

// Function to input n student records
void input(student_t s[], int n) {
    for (int i = 0; i < n; i++) {
        scanf("%s", s[i].name);
        scanf("%d", &s[i].score);
    }
}

// Function to get the student with the highest score
void getHigh(student_t s[], int n, char name[], int *highScore) {
    if (n <= 0) {
        strcpy(name, "N/A");
        *highScore = 0; // Or some indicator of no data
        return;
    }

    *highScore = s[0].score;
    strcpy(name, s[0].name);

    for (int i = 1; i < n; i++) {
        if (s[i].score > *highScore) {
            *highScore = s[i].score;
            strcpy(name, s[i].name);
        }
    }
}

// Function to get the student with the lowest score
void getLow(student_t s[], int n, char name[], int *lowScore) {
    if (n <= 0) {
        strcpy(name, "N/A");
        *lowScore = 0; // Or some indicator of no data
        return;
    }

    *lowScore = s[0].score;
    strcpy(name, s[0].name);

    for (int i = 1; i < n; i++) {
        if (s[i].score < *lowScore) {
            *lowScore = s[i].score;
            strcpy(name, s[i].name);
        }
    }
}

// Function to get the average score (truncated)
int getAverage(student_t s[], int n) {
    if (n <= 0) {
        return 0;
    }
    long long sum = 0; // Use long long to prevent overflow if n and scores are large, though not an issue here
    for (int i = 0; i < n; i++) {
        sum += s[i].score;
    }
    return (int)(sum / n); // Integer division truncates
}

// Comparison function for qsort (sorting integers)
int compare_scores(const void *a, const void *b) {
    int score_a = *(const int *)a;
    int score_b = *(const int *)b;
    return score_a - score_b; // For ascending order
}

// Function to get the median score (truncated)
int getMedian(student_t s[], int n) {
    if (n <= 0) {
        return 0;
    }

    int temp_scores[15]; // Max N is 15
    for (int i = 0; i < n; i++) {
        temp_scores[i] = s[i].score;
    }

    // Sort the temporary array of scores
    qsort(temp_scores, n, sizeof(int), compare_scores);

    if (n % 2 == 1) { // Odd number of students
        return temp_scores[n / 2];
    } else { // Even number of students
        // Average of the two middle elements, truncated
        return (temp_scores[n / 2 - 1] + temp_scores[n / 2]) / 2;
    }
}

int main() {
    int N;
    scanf("%d", &N);

    student_t students[15]; // As per problem constraint N <= 15

    input(students, N);

    char high_name[50];
    int high_score;
    getHigh(students, N, high_name, &high_score);

    char low_name[50];
    int low_score;
    getLow(students, N, low_name, &low_score);

    int average_score = getAverage(students, N);
    int median_score = getMedian(students, N);

    printf("%s %d\n", high_name, high_score);
    printf("%s %d\n", low_name, low_score);
    printf("%d\n", average_score);
    printf("%d\n", median_score);

    return 0;
}
