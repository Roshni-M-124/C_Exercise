void squeeze(char s1[], char s2[])
{
int i, j,k=0,found;
for (i =0; s1[i] != '\0'; i++)
{
found=0;
for(j=0;s2[j]!='\0';j++)
{
 if(s1[i]==s2[j])
 {
 out=1;
 break;
 }
}
if(!found)
s1[k++]=s1[i];
}
s1[k]='\0';
}
