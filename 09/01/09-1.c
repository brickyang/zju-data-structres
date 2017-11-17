#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int MaxNum = 100000;

void Swap(int[], int, int);
void Bubble_Sort(int[], int);
void Insertion_Sort(int[], int);
void Shell_Sort(int[], int);
void Selection_Sort(int[], int);
void Heap_Sort(int[], int);
void PercDown(int[], int, int);
void Merge_Sort(int[], int);
void MSort(int[], int[], int, int);
void Merge(int[], int[], int, int, int);

int main()
{
  int N, i;
  int A[MaxNum];
  scanf("%d", &N);
  for (i = 0; i < N; i++)
    scanf("%d", &A[i]);

  // Bubble_Sort(A, N);
  // Insertion_Sort(A, N);
  // Shell_Sort(A, N);
  // Merge_Sort(A, N);
  Heap_Sort(A, N);

  for (i = 0; i < N; i++)
    printf((i < N - 1) ? "%d " : "%d", A[i]);
  printf("\n");

  return 0;
}

void Heap_Sort(int A[], int N)
{
  int i;
  for (i = N / 2 - 1; i >= 0; i--)
    PercDown(A, i, N);
  for (i = N - 1; i > 0; i--)
  {
    Swap(A, 0, i);
    PercDown(A, 0, i);
  }
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

void Merge_Sort(int A[], int N)
{
  int *tmpA;
  tmpA = malloc(N * sizeof(int));
  MSort(A, tmpA, 0, N - 1);
  free(tmpA);
}

void MSort(int A[], int tmpA[], int L, int RightEnd)
{
  int Center;
  if (L < RightEnd)
  {
    Center = (L + RightEnd) / 2;
    MSort(A, tmpA, L, Center);
    MSort(A, tmpA, Center + 1, RightEnd);
    Merge(A, tmpA, L, Center + 1, RightEnd);
  }
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

void Shell_Sort(int A[], int N)
{
  int Si, D, P, i;
  int Tmp;

  int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};

  for (Si = 0; Sedgewick[Si] >= N; Si++)
    ;

  for (D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si])
    for (P = D; P < N; P++)
    {
      Tmp = A[P];
      for (i = P; i >= D && A[i - D] > Tmp; i -= D)
        A[i] = A[i - D];
      A[i] = Tmp;
    }
}

void Insertion_Sort(int A[], int N)
{
  int P, i, tmp;
  for (P = 1; P < N; P++)
  {
    tmp = A[P];
    for (i = P; i > 0 && A[i - 1] > tmp; i--)
      A[i] = A[i - 1];
    A[i] = tmp;
  }
}

void Bubble_Sort(int A[], int N)
{
  int P, flag, i;
  for (P = N - 1; P >= 0; P--)
  {
    flag = 0;
    for (i = 0; i < P; i++)
    {
      if (A[i] > A[i + 1])
      {
        Swap(A, i, i + 1);
        flag = 1;
      }
    }
    if (flag == 0)
      break;
  }
}

void Swap(int A[], int i, int j)
{
  int tmp;
  tmp = A[i];
  A[i] = A[j];
  A[j] = tmp;
}
