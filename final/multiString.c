#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ARTICLE_LENGTH 10000
#define MAX_WORDS 2000

const char* PUNCTUATION = ".,!?:;";

// Check if character is in allowed punctuation set
int is_allowed_punct(char c)
{
    return strchr(PUNCTUATION, c) != NULL;
}

// Determine if word matches target P; returns 1 if match, and sets trailing punctuation
int match_word(const char* word, const char* target, char* out_punct)
{
    size_t wlen = strlen(word);
    size_t tlen = strlen(target);
    *out_punct = '\0';

    // If contains apostrophe or backtick, only exact match
    for (size_t i = 0; i < wlen; ++i)
    {
        if (word[i] == '\'' || word[i] == '`')
        {
            if (strcmp(word, target) == 0) return 1;
            return 0;
        }
    }

    // Exact match
    if (strcmp(word, target) == 0)
    {
        return 1;
    }
    // Match with one trailing punctuation
    if (wlen == tlen + 1 && is_allowed_punct(word[wlen-1]))
    {
        if (strncmp(word, target, tlen) == 0)
        {
            *out_punct = word[wlen-1];
            return 1;
        }
    }
    return 0;
}

int main()
{
    char article[MAX_ARTICLE_LENGTH];
    char *words[MAX_WORDS];
    char P[128], Q[128];
    int count = 0;

    // Read inputs
    if (!fgets(article, sizeof(article), stdin)) return 0;
    article[strcspn(article, "\n")] = '\0';
    scanf("%127s", P);
    scanf("%127s", Q);

    // Tokenize
    char *copy = strdup(article);
    char *tok = strtok(copy, " ");
    while (tok && count < MAX_WORDS)
    {
        words[count++] = strdup(tok);
        tok = strtok(NULL, " ");
    }
    free(copy);

    // 1. Replacement
    for (int i = 0; i < count; ++i)
    {
        char punct;
        if (match_word(words[i], P, &punct))
        {
            printf("%s", Q);
            if (punct) putchar(punct);
        }
        else
        {
            printf("%s", words[i]);
        }
        if (i < count-1) putchar(' ');
    }
    putchar('\n');

    // 2. Insert before
    for (int i = 0; i < count; ++i)
    {
        char punct;
        if (match_word(words[i], P, &punct))
        {
            printf("%s ", Q);
        }
        printf("%s", words[i]);
        if (i < count-1) putchar(' ');
    }
    putchar('\n');

    // 3. Insert after
    for (int i = 0; i < count; ++i)
    {
        printf("%s", words[i]);
        char punct;
        if (match_word(words[i], P, &punct))
        {
            printf("%s", Q);
        }
        if (i < count-1) putchar(' ');
    }
    putchar('\n');

    // 4. Deletion
    int first = 1;
    for (int i = 0; i < count; ++i)
    {
        char punct;
        if (!match_word(words[i], P, &punct))
        {
            if (!first) putchar(' ');
            printf("%s", words[i]);
            first = 0;
        }
    }
    putchar('\n');

    // 5. Reverse order
    for (int i = count-1; i >= 0; --i)
    {
        printf("%s", words[i]);
        if (i > 0) putchar(' ');
    }
    putchar('\n');

    // Cleanup
    for (int i = 0; i < count; ++i) free(words[i]);
    return 0;
}

