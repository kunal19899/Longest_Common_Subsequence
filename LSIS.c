// Prototype of dynamic programming for Strictest Longest Increasing Subsequence
// Based on D. Gries, The Science of Programming, p. 262
// which is based on M. Fredman, Discrete Mathematics 11 (1975),
//   29-35.
// See CSE 2320 Notes 07

#include <stdio.h>
#include <stdlib.h>

int binSearchLast(int *a,int n,int key)
{
// Input: int array a[] with n elements in ascending order.
//        int key to find.
// Output: Returns subscript of the last a element <= key.
//         Returns -1 if key<a[0].
// Processing: Binary search.
  int low,high,mid;
  low=0;
  high=n-1;
// subscripts between low and high are in search range.
// size of range halves in each iteration.
// When low>high, low==high+1 and a[high]<=key and a[low]>key.
  while (low<=high)
  {
    mid=(low+high)/2;
    if (a[mid]<=key)
      low=mid+1;
    else
      high=mid-1;
  }
  return high;
}

int main()
{
// Get input sequence
int n;
int *y,*bsTabC,*bsTabI,*C,*j;
int i,k,LISlength;

// Get input sequence
scanf("%d",&n);
y=(int*) malloc((n+1)*sizeof(int));
bsTabC=(int*) malloc((n+1)*sizeof(int));
bsTabI=(int*) malloc((n+1)*sizeof(int));
C=(int*) malloc((n+1)*sizeof(int));
j=(int*) malloc((n+1)*sizeof(int));
if (!y || !bsTabC || !bsTabI || !C || !j)
{
  printf("malloc fail %d\n",__LINE__);
  exit(0);
}
for (i=1;i<=n;i++){
  scanf("%d",y+i);
  // printf("%d\n", *(y+i));
}
// Initialize table for binary search for DP
bsTabC[0]=(-999999);  // Must be smaller than all input values.
bsTabI[0]=0;          // Index of predecessor (0=grounded)
for (i=1;i<=n;i++)
  bsTabC[i]=999999;   // Must be larger than all input values.

C[0]=0;  // DP base case
j[0]=0;

for (i=1;i<=n;i++)
{
  // Find SIS that y[i] could be appended to.
  // See CSE 2320 Notes 01 for binSearchLast()
  k=binSearchLast(bsTabC,n+1,y[i]);
  // y[i] only matters if it is not already in table.
  if (bsTabC[k]<y[i]) {
    C[i]=k+1;         // Save length of LIS for y[i]
    j[i]=bsTabI[k];   // Predecessor of y[i]
    bsTabC[k+1]=y[i]; // Decrease value for this length IS
    bsTabI[k+1]=i;
  }
  else
  {
    C[i]=(-1);        // Mark as ignored
    j[i]=(-1);
  }
}

int count = 0;
 for (i = 0; i < 10; i++){
   count++;
 }

printf("  i   y   C   j\n");
printf("---------------\n");
for (i=1;i<=n;i++)
  printf("%3d %3d %3d %3d\n",i,y[i],C[i],j[i]);
   
for (LISlength=n;
     bsTabC[LISlength]==999999;
     LISlength--)
  ;
printf("  i bsTabC bsTabI\n");
printf("-----------------\n");
for (i=1;i<=LISlength;i++)
  printf("%3d %6d %6d\n",i,bsTabC[i],bsTabI[i]);
printf("Length of LIS is %d\n",LISlength);
printf("LIS reversed\n");
for (i=bsTabI[LISlength];
     i>0;
     i=j[i])
  printf("%d\n",y[i]);

free(y);
free(bsTabC);
free(bsTabI);
free(C);
free(j);
}