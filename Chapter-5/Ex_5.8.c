#include<stdio.h>

static char daytab[2][13]={
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

int day_of_year(int year,int month,int day);
void month_day(int year,int yearday);

int main()
{
    int day,mo,dat;
    day=day_of_year(1988,2,29);
    printf("%d\n",day);
    month_day(1988,60);
    return 0;
}

int day_of_year(int year,int month,int day)
{
    int i,leap;
    leap = year % 4 == 0 && year%100 != 0 || year%400 == 0;
    if(month<1||month>12)
        return -1;
    if(day<1|| day>daytab[leap][month])
        return -1;
    for(i=1;i<month;i++)
        day += daytab[leap][i];
    return day;
}

void month_day(int year,int yearday)
{
    int i,leap;
    if(year<1)
        return;    
    leap = year % 4 == 0 && year%100 != 0 || year%400 == 0;
    for(i=1;i<12 && yearday > daytab[leap][i];i++)
        yearday -= daytab[leap][i];
    if(i>12 && yearday > daytab[leap][12])
        return;
    printf("Month: %d, Day: %d\n", i, yearday);

}
