#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

#define MAXLIM 100
#define NUMBER '0'
#define MAXVAL 100

int get_line(char s[],int lim);
void push(double f);
double pop();

int sp=0;
double val[MAXVAL];
int main()
{
 int i=0,l;
 double op1;
 char s[MAXLIM],num[20];
 l=get_line(s,MAXLIM);
 while(s[i]!='\0')
 {
 if (isdigit(s[i])) 
 {
    int j = 0;
    while (isdigit(s[i]) || s[i] == '.') 
        num[j++] = s[i++];
    num[j] = '\0';
    push(atof(num));
    continue;
  }
  if (s[i] == '\n') 
  {
    printf("\t%.8g\n", pop());
    i++;
    continue;
  }
  if(isspace(s[i]))
  {
      i++;
      continue;
  }
 switch(s[i])
 {
    case '+':
      push(pop()+pop());
      break;
    case '*':
      push(pop()*pop());
      break;
    case '-':
      op1=pop();
      push(pop()-op1);
      break;
    case '/':
      op1=pop();
      if(op1!= 0.0)
        push(pop()/op1);
      else
        printf("error:zero divisor\n");
      break;
    default:
      printf("error: unknown command %c\n",s[i]);
      break;
 }
 i++;
}
printf("\t%.8g\n", pop());
return 0;
}

int get_line(char s[],int lim)
{
  int i,c;
  for(i=0;i<lim-1 && ((c=getchar())!=EOF) && c!='\n';i++)
      s[i]=c;
  s[i]='\0';
  return i;
}
 
void push(double f)
{
  if(sp<MAXVAL)
      val[sp++]=f;
  else
      printf("error:stack full, cant push %g\n",f);
}

double pop()
{
  if(sp>0)
      return val[--sp];
  else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

