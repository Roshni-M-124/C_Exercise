#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

void reverse(char s[]);

int main() {
    char line[MAXLINE];

    while (fgets(line, MAXLINE, stdin) != NULL) {
        reverse(line);
        printf("%s", line);
    }

    return 0;
}

void reverse(char s[]) {
    int i, j;
    char temp;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        if (s[j] == '\n') { j--; } 
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}
