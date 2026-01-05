#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include <stdlib.h>

void push(double);
double pop();
double stack[100];
int top=-1;

int main()
{
  char s[20];
  double d;
  double op1;
  while((scanf("%s",s))==1)
  {
    if(isdigit(s[0])|| (s[0]=='-' && isdigit(s[1])))
      push(atof(s));
    else
    {
      switch(s[0])
      {
      case '+':
        push(pop()+pop());
        break;
      case '*':
        push(pop()*pop());
        break;
      case '-':
        op1 =  pop();
        push(pop()-op1);
        break;
      case '/':
        op1 = pop();
        if(op1 !=0)
        {
        push(pop()/op1);
        break;
        }
        else
        {
          printf("Error:Zero division");
          break;
        }
       default :
        printf("Invalid Input");
        break;
    }  
    }
  }
  if (top == 0)
        printf("Result = %.2f\n", pop());
    else
        printf("Error: invalid postfix expression\n");
  return 0;
}  

void push(double s)
{
  if(top>=99)
   printf("stack overflow");
  else
    stack[++top] = s;
 }   

double pop()
{
  if (top < 0)
    {
        printf("Stack empty\n");
        return 0.0;
    }
    return stack[top--];
 }   
