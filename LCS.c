/*Longest common subsequences*/
#include <stdio.h>
#include <string.h>

#define MAXSIZE 70

int length1,length2;
char string1[MAXSIZE],string2[MAXSIZE];

int LCSlength;
char LCSstring[MAXSIZE];

int cost[MAXSIZE+1][MAXSIZE+1];

void LCS()
{
  int i,j,k;
  /*string1[i] is associated with row i+1
    string2[i] is associated with column i+1 */
  /*Initialize*/
  for (i=0;i<=length1;i++)
    cost[i][0]=0;
  for (i=1;i<=length2;i++)
    cost[0][i]=0;

  for (i=1;i<=length1;i++)
    for (j=1;j<=length2;j++)
      cost[i][j]=
        (string1[i-1]==string2[j-1])
          ? cost[i-1][j-1]+1
          : (cost[i][j-1]<=cost[i-1][j]) ? cost[i-1][j]
                                        : cost[i][j-1];

  LCSlength=cost[length1][length2];
  LCSstring[LCSlength]='\0';
  i=length1;
  j=length2;
  int count = 0;
  while (cost[i][j]!=0)
    if (string1[i-1]==string2[j-1])
    {
      LCSstring[cost[i][j]-1]=string1[i-1];
      count++;
      i--;
      j--;
    }
    else if (cost[i][j-1]<=cost[i-1][j])
      i--;
    else
      j--;
  
  for (int k = 0; k < count; k++){
    printf("%c\n", LCSstring[k]);
  }
}

int main()
{
  int i,j;

  scanf("%s",string1);
  scanf("%s",string2);
  length1=strlen(string1);
  length2=strlen(string2);
  LCS();
  printf("LCS is %s, length==%d\n",LCSstring,LCSlength);

  // Print table
  printf("    ");
  for (i=0;i<length2;i++)
    printf("  %c",string2[i]);
  printf("\n ");
  for (i=0;i<=length2;i++)
    printf(" %2d",cost[0][i]);
  printf("\n");
  for (i=0;i<length1;i++)
  {
    printf("%c",string1[i]);
    for (j=0;j<=length2;j++)
      printf(" %2d",cost[i+1][j]);
    printf("\n");
  }
}