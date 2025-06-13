#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

// Structure to store the results
typedef struct {
    int position; // Combined row*10 + col
    int count;    // Number of 5-in-a-row lines formed
} Result;

// Function to check if a position is within the board boundaries
int isValid(int row, int col) {
    return (row >= 0 && row < SIZE && col >= 0 && col < SIZE);
}

// Function to count consecutive pieces in a specific direction from a starting point
// EXCLUDING the starting point. Stops at 0, edge, or after 4 steps.
int countConsecutive(int board[SIZE][SIZE], int r, int c, int dr, int dc) {
    int count = 0;
    for (int i = 1; i <= 4; ++i) { // Check up to 4 steps away
        int nr = r + i * dr;
        int nc = c + i * dc;
        if (isValid(nr, nc) && board[nr][nc] == 1) {
            count++;
        } else {
            break; // Stop if off-board or empty cell
        }
    }
    return count;
}

// Function to check if the position *beyond* a sequence of 'count' pieces is blocked (0 or edge)
int isBlocked(int board[SIZE][SIZE], int r, int c, int dr, int dc, int count) {
    int nr = r + (count + 1) * dr;
    int nc = c + (count + 1) * dc;
    if (!isValid(nr, nc)) {
        return 1; // Blocked by edge
    }
    return (board[nr][nc] == 0); // Blocked if 0
}

// Checks if placing a piece at (r, c) creates exactly 5-in-a-row in the axis (dr, dc)
// and that this 5-in-a-row is blocked on both ends.
int checkDirectionStrictlyFive(int board[SIZE][SIZE], int r, int c, int dr, int dc) {
    // Count consecutive pieces in both directions *from the target cell*
    int count_fwd = countConsecutive(board, r, c, dr, dc);
    int count_bwd = countConsecutive(board, r, c, -dr, -dc);

    // If placing the piece creates exactly 5
    if (count_fwd + count_bwd + 1 == 5) {
        // Check if the line of 5 is blocked on both ends
        int blocked_fwd = isBlocked(board, r, c, dr, dc, count_fwd);
        int blocked_bwd = isBlocked(board, r, c, -dr, -dc, count_bwd);
        return (blocked_fwd && blocked_bwd);
    }
    return 0; // Did not form exactly 5
}


// Counts how many strictly bounded 5-in-a-row lines are formed by placing at (r,c)
int countTotalStrictFives(int board[SIZE][SIZE], int r, int c) {
    int total_fives = 0;
    // Directions: horizontal, vertical, diag down-right, diag down-left
    int dr[] = {0, 1, 1, 1};
    int dc[] = {1, 0, 1, -1};

    for(int i = 0; i < 4; ++i) {
        if (checkDirectionStrictlyFive(board, r, c, dr[i], dc[i])) {
            total_fives++;
        }
    }
    return total_fives;
}

// Comparison function for qsort
int compareResults(const void *a, const void *b) {
    Result *resA = (Result *)a;
    Result *resB = (Result *)b;

    // Sort by count descending
    if (resA->count != resB->count) {
        return resB->count - resA->count;
    }
    // If counts are equal, sort by position ascending
    return resA->position - resB->position;
}

int main() {
    int board[SIZE][SIZE];
    char line[SIZE * 2 + 5]; // Buffer for reading lines

    // Read the board from input
    for (int i = 0; i < SIZE; i++) {
        if (fgets(line, sizeof(line), stdin) == NULL) {
             fprintf(stderr, "Error reading input.\n");
             return 1;
        }
        char *token = strtok(line, " \t\n");
        for (int j = 0; j < SIZE; j++) {
            if (token == NULL) {
                fprintf(stderr, "Error parsing input line %d.\n", i);
                return 1;
            }
            board[i][j] = atoi(token);
            token = strtok(NULL, " \t\n");
        }
    }

    // Store the results
    Result results[SIZE * SIZE];
    int resultCount = 0;

    // Iterate through each empty cell
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                // Check how many strictly bounded 5-in-a-row are formed
                int count = countTotalStrictFives(board, i, j);

                if (count > 0) {
                    results[resultCount].position = i * 10 + j;
                    results[resultCount].count = count;
                    resultCount++;
                }
            }
        }
    }

    // Sort the results
    qsort(results, resultCount, sizeof(Result), compareResults);

    // Print the sorted results
    for (int i = 0; i < resultCount; i++) {
        printf("%02d %d\n", results[i].position, results[i].count);
    }

    return 0;
}

