#include <stdio.h>
#define MAXLINE 1000

int getline(char line[], int maxline);
void copy(char to[], char from[]);

int main() {
    int len, maxlen = 0;
    char line[MAXLINE];
    char longest[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > maxlen) {
            maxlen = len;
            copy(longest, line);
        }
    }

    if (maxlen > 0) {
        printf("Longest line :\n%s", longest);
        printf("Total length: %d characters\n", maxlen);
    }

    return 0;
}

int getline(char s[], int lim) {
    int c, i = 0, len = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        len++;
        if (i < lim - 1) {
            s[i++] = c; 
        }
    }

    if (c == '\n') {
        len++;
        if (i < lim - 1)
            s[i++] = c;
    }

    s[i] = '\0';
    return len; 
}

void copy(char to[], char from[]) {
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}

