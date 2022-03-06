#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//PROBLEMA 2
int count_occurrences(const char* text, const char* word) {
    int i, j, cnt = 0;
    char first = word[0];
    for(i = 0; text[i] != '\0'; i++) {
        if (text[i] == first) {
            for (j = 1; word[j] != '\0'; j++)
                if (text[i + j] != word[j])
                    break;
            if (word[j] == '\0')
                cnt++;
        }
    }
    return cnt;
}

//PROBLEMA 3
char* replace (char* text, const char* word1, const char* word2) {
    char *p;
    int occurrences = count_occurrences(text, word1);
    p = strstr(text, word1);
    while (p != NULL && occurrences > 0) {
        strncpy (p, word2, strlen(word2));
        p = strstr(text, word1);
        occurrences--;
    }
    return text;
}

int main()
{
    /*char x[5] = "aa", text[5] = "aaaa", x1[5] = "a", x2[5] = "de", text1[10] = "abcabcabc";
    printf("%d\n", count_occurrences(text,x)); //3
    printf("%s\n", replace(text1, x1, x2));*/

    char *p, text[10] = "abcabcabc";
    char word1[6] = "a", word2[5] = "de";
    int occurrences = count_occurrences(text, word1);
    p = strstr(text, word1);
    while (p != NULL && occurrences > 0) {
        printf("  p== %s  ", p);
        strncpy (p, word2, strlen(word2));
        printf("  p== %s  ", p);
        p = strstr(text, word1);
        printf("%s\n", text);
        occurrences--;
    }
    printf("%s\n", text);
    return 0;
}
