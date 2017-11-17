#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int A[1000] = {0};
int T[1000];

void solve(int, int, int);
int getLeftLenght(int);
int compare(const void *, const void *);
int min(int, int);

int main()
{
  int N;
  scanf("%d", &N);
  {
    for (int i = 0; i < N; i++)
      scanf("%d", &A[i]);
  }
  qsort(A, N, sizeof(int), compare);
  solve(0, N - 1, 0);

  for (int i = 0; i < N; i++)
  {
    printf("%d", T[i]);
    if (i == N - 1)
      printf("\n");
    else
      printf(" ");
  }
  return 0;
}

void solve(int ALeft, int ARight, int TRoot)
{
  int n = ARight - ALeft + 1;
  if (n == 0)
    return;
  int L = getLeftLenght(n);
  T[TRoot] = A[ALeft + L];
  int LeftTRoot = TRoot * 2 + 1;
  int RightTRoot = LeftTRoot + 1;
  solve(ALeft, ALeft + L - 1, LeftTRoot);
  solve(ALeft + L + 1, ARight, RightTRoot);
}

int getLeftLenght(int N)
{
  int H = log2(N + 1);
  int X = N + 1 - pow(2, H);
  X = min(X, pow(2, H - 1));
  int L = pow(2, H - 1) - 1 + X;
  return L;
}

int compare(const void *a1, const void *a2)
{
  return *(int *)a1 - *(int *)a2;
}

int min(int a1, int a2)
{
  return a1 < a2 ? a1 : a2;
}
