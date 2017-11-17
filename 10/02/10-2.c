#include <stdio.h>
#include <stdlib.h>

#define MaxUsersNum 10000
#define MaxProblemsNum 6

typedef struct UserStruct *User;
struct UserStruct
{
  int id;
  int total;
  int scores[MaxProblemsNum];
};

int N, K, M;
int FullMarks[MaxProblemsNum];

void Print(User[]);
void Shell_Sort(User[], int);
int Larger(User, User);
void Assign(User, User);
void InputSubmissions(User[]);
void InputInitialValues(User[]);

int main()
{
  User Users[MaxUsersNum];
  InputInitialValues(Users);
  InputSubmissions(Users);
  Shell_Sort(Users, N);
  Print(Users);
  return 0;
}

void Print(User Users[])
{
  int rank = 1, n = 1, prev = 999999999;
  while (--N >= 0)
  {
    if (Users[N]->total == -1)
      break;

    rank = Users[N]->total == prev ? rank : n;
    prev = Users[N]->total;
    n++;

    printf("%d %05d %d ", rank, Users[N]->id, Users[N]->total);
    for (int i = 1; i <= K; i++)
    {
      if (Users[N]->scores[i] > -1)
        printf("%d", Users[N]->scores[i]);
      else
        printf("-");
      printf(i == K ? "\n" : " ");
    }
  }
}

void Shell_Sort(User A[], int N)
{
  int Si, D, P, i;
  User Tmp = (User)malloc(sizeof(struct UserStruct));

  int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};

  for (Si = 0; Sedgewick[Si] >= N; Si++)
    ;

  for (D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si])
    for (P = D; P < N; P++)
    {
      Assign(Tmp, A[P]);
      for (i = P; i >= D && Larger(A[i - D], Tmp); i -= D)
        Assign(A[i], A[i - D]);
      Assign(A[i], Tmp);
    }
}

int Larger(User U1, User U2)
{
  if (U1->total > U2->total)
    return 1;
  else if (U1->total < U2->total)
    return 0;

  int n1 = 0, n2 = 0;
  for (int i = 1; i <= K; i++)
  {
    if (U1->scores[i] == FullMarks[i])
      n1++;
    if (U2->scores[i] == FullMarks[i])
      n2++;
  }
  if (n1 > n2)
    return 1;
  if (n1 < n2)
    return 0;

  return U1->id < U2->id;
}

void Assign(User U1, User U2)
{
  U1->id = U2->id;
  U1->total = U2->total;
  for (int i = 0; i < MaxProblemsNum; i++)
    U1->scores[i] = U2->scores[i];
}

void InputSubmissions(User Users[])
{
  int i, m = M;
  int id, p, score;
  while ((--m) >= 0)
  {
    scanf("%d %d %d", &id, &p, &score);
    i = id - 1;

    if (score == -1 && Users[i]->scores[p] == -1)
      Users[i]->scores[p] = 0;

    if (score > Users[i]->scores[p])
    {
      if (Users[i]->total == -1)
        Users[i]->total = 0;
      if (Users[i]->scores[p] > -1)
        Users[i]->total -= Users[i]->scores[p];
      Users[i]->scores[p] = score;
      Users[i]->total += score;
    }
  }
}

void InputInitialValues(User Users[])
{
  int i;
  scanf("%d %d %d", &N, &K, &M);
  for (i = 1; i <= K; i++)
    scanf("%d", &FullMarks[i]);
  for (i = 0; i < N; i++)
  {
    Users[i] = (User)malloc(sizeof(struct UserStruct));
    Users[i]->id = i + 1;
    Users[i]->total = -1;
    for (int j = 0; j <= MaxProblemsNum; j++)
      Users[i]->scores[j] = -1;
  }
}
