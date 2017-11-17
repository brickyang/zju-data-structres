#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int MaxNum = 100;

void Single_Insertion_Sort(int[], int, int);
void Single_Merge_Sort(int[], int, int);
void Merge_Pass(int[], int[], int, int);
void Merge(int[], int[], int, int, int);
int arycmp(int[], int[], int);

int main()
{
  int N, P, i;
  char flag = 0;
  int A1[MaxNum];
  int A2[MaxNum];
  int sortedA[MaxNum];
  scanf("%d", &N);
  for (i = 0; i < N; i++)
  {
    scanf("%d", &A1[i]);
    A2[i] = A1[i];
  }
  for (i = 0; i < N; i++)
    scanf("%d", &sortedA[i]);

  for (P = 1; P < N; P++)
  {
    Single_Insertion_Sort(A1, N, P);
    Single_Merge_Sort(A2, N, P);
    if (arycmp(A1, sortedA, N))
    {
      flag = 'I';
      Single_Insertion_Sort(A1, N, P + 1);
      break;
    }
    if (arycmp(A2, sortedA, N))
    {
      flag = 'M';
      Single_Merge_Sort(A2, N, P + 1);
      break;
    }
  }

  if (flag == 'I')
  {
    printf("Insertion Sort\n");
    for (i = 0; i < N; i++)
      printf((i < N - 1) ? "%d " : "%d", A1[i]);
  }
  else if (flag == 'M')
  {
    printf("Merge Sort\n");
    for (i = 0; i < N; i++)
      printf((i < N - 1) ? "%d " : "%d", A2[i]);
  }

  printf("\n");

  return 0;
}

void Single_Merge_Sort(int A[], int N, int i)
{
  int *tmpA;
  tmpA = malloc(N * sizeof(int));
  int length = pow(2, i - 1);
  Merge_Pass(A, tmpA, N, length);
}

void Merge_Pass(int A[], int tmpA[], int N, int length)
{
  int i;
  for (i = 0; i < N - 2 * length; i += 2 * length)
    Merge(A, tmpA, i, i + length, i + 2 * length - 1);

  if (i + length < N)
    Merge(A, tmpA, i, i + length, N - 1);
  else
    for (int j = i; j < N; j++)
      tmpA[j] = A[j];
}

void Merge(int A[], int tmpA[], int L, int R, int RightEnd)
{
  int LeftEnd = R - 1;
  int tmp = L;
  int NumElements = RightEnd - L + 1;
  while (L <= LeftEnd && R <= RightEnd)
  {
    if (A[L] <= A[R])
      tmpA[tmp++] = A[L++];
    else
      tmpA[tmp++] = A[R++];
  }
  while (L <= LeftEnd)
    tmpA[tmp++] = A[L++];
  while (R <= RightEnd)
    tmpA[tmp++] = A[R++];
  for (int i = 0; i < NumElements; i++, RightEnd--)
    A[RightEnd] = tmpA[RightEnd];
}

void Single_Insertion_Sort(int A[], int N, int P)
{
  int i, tmp;
  tmp = A[P];
  for (i = P; i > 0 && A[i - 1] > tmp; i--)
    A[i] = A[i - 1];
  A[i] = tmp;
}

int arycmp(int A[], int B[], int N)
{
  for (int i = 0; i < N; i++)
    if (A[i] != B[i])
      return 0;
  return 1;
}
