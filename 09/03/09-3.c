#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int MaxNum = 100;

void Single_Insertion_Sort(int[], int, int);
void Single_Heap_Sort(int[], int, int);
void PercDown(int[], int, int);
int arycmp(int[], int[], int);
void Swap(int[], int, int);

int main()
{
  int N, P, i;
  char flag = 0;
  int A1[MaxNum];
  int A2[MaxNum];
  int sortedA[MaxNum];
  int *A;
  char *str;
  void (*(func))();
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
    Single_Heap_Sort(A2, N, P);
    if (arycmp(A1, sortedA, N))
    {
      flag = 'I';
      A = A1;
      func = Single_Insertion_Sort;
      break;
    }
    if (arycmp(A2, sortedA, N))
    {
      flag = 'H';
      A = A2;
      func = Single_Heap_Sort;
      break;
    }
  }

  (*func)(A, N, P + 1);

  if (flag == 'I')
    str = "Insertion Sort";
  else if (flag == 'H')
    str = "Heap Sort";
  printf("%s\n", str);

  for (i = 0; i < N; i++)
    printf((i < N - 1) ? "%d " : "%d", A[i]);
  printf("\n");

  return 0;
}

void Single_Heap_Sort(int A[], int N, int P)
{
  if (P == 1)
    for (int i = N / 2 - 1; i >= 0; i--)
      PercDown(A, i, N);

  Swap(A, 0, N - P);
  PercDown(A, 0, N - P);
}

void PercDown(int A[], int p, int N)
{
  int Parent, Child;
  int X;

  X = A[p];
  for (Parent = p; Parent * 2 + 1 < N; Parent = Child)
  {
    Child = Parent * 2 + 1;
    if ((Child != N - 1) && (A[Child] < A[Child + 1]))
      Child++;
    if (X >= A[Child])
      break;
    else
      A[Parent] = A[Child];
  }
  A[Parent] = X;
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

void Swap(int A[], int i, int j)
{
  int tmp;
  tmp = A[i];
  A[i] = A[j];
  A[j] = tmp;
}
