#include <ctype.h>
#include <stdio.h>
#define MAXLINE 100
double atof(char s[]);
int mgetline(char s[], int lim);

int main()
{
double sum;
char line[MAXLINE];
mgetline(line, MAXLINE) ;
printf("\t%g\n", atof(line));
return 0;
}

int mgetline(char s[], int lim)
{
int c, i;
i = 0;
while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
  s[i++] = c;
if (c == '\n')
s[i++] = c;
s[i] = '\0';
return i;
}

double atof(char s[])
{
double val, power;
int i, sign;
for (i = 0; isspace(s[i]); i++) 
;
sign = (s[i] == '-') ? -1 : 1;
if (s[i] == '+' || s[i] == '-')
  i++;
for (val = 0.0; isdigit(s[i]); i++)
  val = 10.0 * val + (s[i] - '0');
if (s[i] == '.')
  i++;
for (power = 1.0; isdigit(s[i]); i++) 
{
  val = 10.0 * val + (s[i] - '0');
  power *= 10;
}
if (s[i] == 'e' || s[i] == 'E')
{
    int exp = 0, exp_sign = 1;
    i++;
    if (s[i] == '+' || s[i] == '-')
    {
        exp_sign = (s[i] == '-') ? -1 : 1;
        i++;
    }
    while (isdigit(s[i])) 
    {
        exp = 10 * exp + (s[i] - '0');
        i++;
    }
    while (exp-- > 0) {
        if (exp_sign == 1)
            val *= 10;
        else
            val /= 10;
    }
}
return sign*val/power;
}
