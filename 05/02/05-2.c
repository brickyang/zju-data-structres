#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct
{
  ElementType Data;
  int Parent;
} SetType;

int *Computers;

void Connect(int, int);
void Check(int, int);
int Find(int);

int main()
{
  int N, c1, c2;
  scanf("%d", &N);
  getchar();
  Computers = malloc((N + 1) * sizeof(int));
  {
    for (int i = 0; i <= N; i++)
      Computers[i] = -1;
  }
  char op;
  while ((op = getchar()) != 'S')
  {
    scanf("%d %d", &c1, &c2);
    if (op == 'I')
      Connect(c1, c2);
    else if (op == 'C')
      Check(c1, c2);
    getchar();
  }

  int components = 0;
  for (int i = 1; i <= N; i++)
    if (Computers[i] < 0)
      components++;

  if (components > 1)
    printf("There are %d components.\n", components);
  else
    printf("The network is connected.\n");

  return 0;
}

void Connect(int c1, int c2)
{
  int Root1 = Find(c1);
  int Root2 = Find(c2);
  if (Root1 == Root2)
    return;

  if (Computers[Root1] <= Computers[Root2])
  {
    Computers[Root1] += Computers[Root2];
    Computers[Root2] = Root1;
  }
  else
  {
    Computers[Root2] += Computers[Root1];
    Computers[Root1] = Root2;
  }
}

void Check(int c1, int c2)
{
  int Root1 = Find(c1);
  int Root2 = Find(c2);
  if (Root1 == Root2)
    printf("yes\n");
  else
    printf("no\n");
}

int Find(int c)
{
  while (Computers[c] > 0)
    c = Computers[c];

  return c;
}
