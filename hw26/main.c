#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ARTICLE_LENGTH 10000
#define MAX_WORD_LENGTH 100
#define MAX_WORDS 1000

// Function to check if a character is an English punctuation
int is_english_punctuation(char c) {
    return (c == '.' || c == ',' || c == '!' || c == '?' || c == ';' || c == ':');
}

// Function to check if a word matches the target word considering trailing punctuation
// word: the word from the article
// target: the target word P
// trailing_punctuation: pointer to store the trailing punctuation character (if any)
// Returns 1 if matches, 0 otherwise.
int word_matches(const char *word, const char *target, char *trailing_punctuation) {
    int word_len = strlen(word);
    int target_len = strlen(target);

    *trailing_punctuation = '\0'; // Initialize to no punctuation

    if (word_len < target_len) {
        return 0; // Word is shorter than the target
    }

    // Check for contraction (' or `) - if found, it's not a match
    for (int i = 0; i < word_len; i++) {
        if (word[i] == '\'' || word[i] == '`') {
            return 0;
        }
    }

    // Case 1: Exact match
    if (strcmp(word, target) == 0) {
        return 1;
    }

    // Case 2: Match with one trailing English punctuation
    if (word_len == target_len + 1) {
        if (is_english_punctuation(word[word_len - 1])) {
            // Check if the part before the punctuation matches the target
            if (strncmp(word, target, target_len) == 0) {
                *trailing_punctuation = word[word_len - 1];
                return 1;
            }
        }
    }

    return 0; // No match
}

int main() {
    char article_input[MAX_ARTICLE_LENGTH];
    char p_word[MAX_WORD_LENGTH];
    char q_word[MAX_WORD_LENGTH];

    // Read the entire line for the article
    if (fgets(article_input, sizeof(article_input), stdin) == NULL) {
        return 1; // Error reading input
    }
    article_input[strcspn(article_input, "\n")] = 0; // Remove trailing newline

    scanf("%s", p_word);
    scanf("%s", q_word);

    // --- Tokenize the article into words ---
    char *words[MAX_WORDS];
    int num_words = 0;
    // Create a copy of the input string because strtok modifies it
    char article_copy[MAX_ARTICLE_LENGTH];
    strcpy(article_copy, article_input);

    char *token = strtok(article_copy, " ");

    while (token != NULL && num_words < MAX_WORDS) {
        words[num_words++] = strdup(token); // Duplicate the token
        token = strtok(NULL, " ");
    }

    // --- 1. Word Replacement ---
    for (int i = 0; i < num_words; i++) {
        char trailing_punc = '\0';
        if (word_matches(words[i], p_word, &trailing_punc)) {
            // Print Q and then the captured punctuation (if any)
            printf("%s%c", q_word, trailing_punc);
        } else {
            // Print the original word as is
            printf("%s", words[i]);
        }
        if (i < num_words - 1) {
            printf(" "); // Print space between words
        }
    }
    printf("\n");

    // --- 2. Insert Word Before ---
    for (int i = 0; i < num_words; i++) {
        char trailing_punc = '\0'; // Not strictly needed for logic here, as we print the original word
        if (word_matches(words[i], p_word, &trailing_punc)) {
            printf("%s ", q_word); // Print Q followed by a space
        }
        printf("%s", words[i]); // Print the original word (with its punctuation)
        if (i < num_words - 1) {
            printf(" "); // Print space between words
        }
    }
    printf("\n");

    // --- 3. Insert Word After ---
    for (int i = 0; i < num_words; i++) {
        char trailing_punc = '\0'; // Not strictly needed for logic here, as we print the original word
        printf("%s", words[i]); // Print the original word (with its punctuation)
        if (word_matches(words[i], p_word, &trailing_punc)) {
            printf(" %s", q_word); // Print a space followed by Q
        }
        if (i < num_words - 1) {
            printf(" "); // Print space between words/insertions
        }
    }
    printf("\n");


    // --- 4. Word Deletion ---
    int first_word_printed = 0; // Flag to handle spaces correctly
    for (int i = 0; i < num_words; i++) {
        char trailing_punc = '\0'; // Not strictly needed for logic here
        if (!word_matches(words[i], p_word, &trailing_punc)) {
            // If it's not a match, print it
            if (first_word_printed) {
                printf(" "); // Add space before printing if it's not the first word
            }
            printf("%s", words[i]);
            first_word_printed = 1; // Mark that we've printed at least one word
        }
    }
    printf("\n");

    // --- 5. Word Order Reversal ---
    for (int i = num_words - 1; i >= 0; i--) {
        printf("%s%s", words[i], (i == 0) ? "" : " "); // Print word, then space (except for the last one)
    }
    printf("\n");

    // Free the duplicated strings allocated by strdup
    for (int i = 0; i < num_words; i++) {
        free(words[i]);
    }

    return 0;
}
