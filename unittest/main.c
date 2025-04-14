#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool isIdentifier(const char *str) {
    if (!isalpha(str[0]) && str[0] != '_') return false;
    for (int i = 1; str[i] != '\0'; i++) {
        if (!isalnum(str[i]) && str[i] != '_') return false;
    }
    return true;
}

bool isInteger(const char *str) {
    int i = 0;
    if (str[0] == '-' || str[0] == '+') i++;
    for (; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

bool isFloat(const char *str) {
    int i = 0, dotCount = 0;
    if (str[0] == '-' || str[0] == '+') i++;
    for (; str[i] != '\0'; i++) {
        if (str[i] == '.') dotCount++;
        else if (!isdigit(str[i])) return false;
    }
    return dotCount == 1;
}

void classifyToken(const char *token) {
    if (isIdentifier(token)) {
        printf("Identifier\n");
    } else if (isInteger(token)) {
        if (token[0] == '-')
            printf("Negative Integer\n");
        else
            printf("Positive Integer\n");
    } else if (isFloat(token)) {
        if (token[0] == '-')
            printf("Negative Floating\n");
        else
            printf("Positive Floating\n");
    } else {
        printf("Error\n");
    }
}

int main() {
    char input[] = "rate R2D2 -22 555666 0.23 -1.2 5a #";
    char *token = strtok(input, " ");

    while (token != NULL) {
        if (strcmp(token, "#") == 0) break;
        classifyToken(token);
        token = strtok(NULL, " ");
    }
    return 0;
}
