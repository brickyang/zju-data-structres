#include <stdio.h>

int main()
{
  int N, i, a;
  int Count[51] = {0};

  scanf("%d", &N);

  for (i = 0; i < N; i++)
  {
    scanf("%d", &a);
    Count[a]++;
  }

  for (i = 0; i < 51; i++)
    if (Count[i] > 0)
      printf("%d:%d\n", i, Count[i]);

  return 0;
}
