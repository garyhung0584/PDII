#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 10000

const char* PUNCTUATION = ".,:;!?";

int is_punct(char c)
{
    return strchr(PUNCTUATION, c) != NULL;
}

int isMatch(const char* word, const char* target, char* punct)
{
    size_t wlen = strlen(word);
    size_t tlen = strlen(target);
    *punct = '\0';

    for (size_t i = 0; i < wlen; ++i)
    {
        if (word[i] == '\'' || word[i] == '`')
        {
            if(strcmp(word, target) == 0) return 1;
            return 0;
        }
    }

    if (strcmp(word, target) == 0) return 1;


    if (wlen == tlen+1 && is_punct(word[wlen-1]))
    {
        if (strncmp(word, target, tlen) == 0)
        {
            *punct = word[wlen-1];
            return 1;
        }
    }
    return 0;
}


int main()
{
    char article[MAX_LENGTH];
    char *words[MAX_LENGTH];
    char P[128];
    char Q[128];

    int count = 0;
    if (!fgets(article, sizeof(article), stdin)) return 0;
    article[strcspn(article, "\n")] = '\0';
    scanf("%127s", P);
    scanf("%127s", Q);

    char *copy = strdup(article);
    char *token = strtok(copy, " ");
    while (token && count< MAX_LENGTH)
    {
        words[count++] = strdup(token);
        token = strtok(NULL, " ");
    }
    free(copy);

    for (int i = 0; i < count; i++)
    {
        char punct;
        if (isMatch(words[i], P, &punct))
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

    for (int i = 0; i < count; ++i)
    {
        char punct;
        if (isMatch(words[i], P, &punct))
        {
            printf("%s", Q);
        }
        printf("%s", words[i]);
        if (i < count - 1) putchar(' ');
    }
    putchar('\n');

    for (int i = 0; i < count; ++i)
    {
        char punct;
        printf("%s", words[i]);
        if (isMatch(words[i], P, punct))
        {
            printf("%s", Q);
        }
        if (i < count - 1) putchar(' ');
    }
    putchar('\n');

    int first = 1;
    for (int i = 0; i < count; ++i)
    {
        char punct;
        if (!isMatch(words[i], P, punct))
        {
            if (!first) putchar(' ');
            printf("%s", words[i]);
            first = 0;
        }
    }
    putchar('\n');

    for (int i= count-1; i >= 0; --i)
    {
        printf("%s", words[i]);
        if(i > 0)putchar(' ');
    }
    putchar('\n');

    for (int i=0; i < count; ++i) free(words[i]);
    return 0;






}
