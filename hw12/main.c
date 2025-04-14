#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LEN 1000

// 檢查字串是否符合規則
int isValidString(const char *str) {
    int len = strlen(str);
    if (!((isalpha(str[0]) || str[0] == '_') && (isalpha(str[len - 1]) || str[len - 1] == '_')))
        return 0;
    return 1;
}

// 反轉字串
void reverseString(char *str) {
    int left = 0, right = strlen(str) - 1;
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

// 計算不含空白的字串長度
int getLengthWithoutSpaces(const char *str) {
    int count = 0;
    while (*str) {
        if (!isspace((unsigned char)*str))
            count++;
        str++;
    }
    return count;
}

int main() {
    char str1[MAX_LEN], str2[MAX_LEN];

    // 讀取輸入
    fgets(str1, MAX_LEN, stdin);
    fgets(str2, MAX_LEN, stdin);

    // 移除換行符
    str1[strcspn(str1, "\n")] = '\0';
    str2[strcspn(str2, "\n")] = '\0';

    // 檢查字串是否符合規則
    if (!isValidString(str1) || !isValidString(str2)) {
        printf("Error\n");
        return 0;
    }

    // 反轉字串
    char revStr1[MAX_LEN], revStr2[MAX_LEN];
    strcpy(revStr1, str1);
    strcpy(revStr2, str2);
    reverseString(revStr1);
    reverseString(revStr2);

    // 輸出反轉後的字串
    printf("%s\n", revStr1);
    printf("%s\n", revStr2);

    // 比較去空白後的長度
    int len1 = getLengthWithoutSpaces(str1);
    int len2 = getLengthWithoutSpaces(str2);

    // 輸出較長的原始字串（若相同長度則輸出第一個）
    printf("%s\n", (len1 >= len2) ? str1 : str2);

    return 0;
}
