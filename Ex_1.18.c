#include <stdio.h>
#define MAXLINE 1000

int getline(char line[], int maxline);

int main() {
    int len, i;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        for (i = len - 1; i >= 0 && (line[i] == ' ' || line[i] =='\t' || line[i] == '\n'); --i)
        ;
        line[i + 1] = '\n';
        line[i + 2] = '\0';
        
        if (i >= 0) 
            printf("%s", line);
    }

    return 0;
}
