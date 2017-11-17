#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int MaxN = 100;
const float Diameter = 15.0;
int JumpDistance;
int Path[MaxN], Dist[MaxN];

typedef struct QNode *IQueue;
struct QNode
{
  int Q[MaxN];
  int Top;
  int Last;
};

typedef struct VNode *PtrToVNode;
struct VNode
{
  int X;
  int Y;
  IQueue AdjNodes;
};
typedef PtrToVNode Vertex;
Vertex VertexList[MaxN];

void PushAdjVIntoQueue(IQueue, int);
void InitAdjNodes(int, Vertex);
void InputVertexes(int);
int IsAdjacent(Vertex, Vertex);
Vertex CreateVertex();
void InitZeroVertex();

int IsSafe(int);
void InitPathAndDist(int, int *, int *);

IQueue CreateQueue();
void PushQueue(IQueue, int);
int PopQueue(IQueue);
int IsQueueEmpty(IQueue);

int main()
{
  int N;
  int Safe = 0;

  scanf("%d %d", &N, &JumpDistance);

  InitPathAndDist(N, Path, Dist);
  InitZeroVertex();
  InputVertexes(N);

  IQueue JumpQueue = CreateQueue();
  PushQueue(JumpQueue, 0);

  while (!IsQueueEmpty(JumpQueue))
  {
    int V = PopQueue(JumpQueue);
    if (IsSafe(V))
    {
      Safe = 1;
      break;
    }
    PushAdjVIntoQueue(JumpQueue, V);
  }

  if (Safe)
    printf("Yes\n");
  else
    printf("No\n");

  return 0;
}

void PushAdjVIntoQueue(IQueue JumpQueue, int V)
{
  int adjV;
  IQueue AdjNodes = VertexList[V]->AdjNodes;
  while (!IsQueueEmpty(AdjNodes))
  {
    adjV = PopQueue(AdjNodes);
    if (Dist[adjV] == -1)
    {
      Dist[adjV] = Dist[V] + 1;
      Path[adjV] = V;
      PushQueue(JumpQueue, adjV);
    }
  }
}

void InitAdjNodes(int N, Vertex V)
{
  for (int i = 0; i < N; i++)
    if (IsAdjacent(VertexList[i], V))
    {
      PushQueue(VertexList[i]->AdjNodes, N);
      if (i != 0)
        PushQueue(VertexList[N]->AdjNodes, i);
    }
}

void InputVertexes(int N)
{
  for (int i = 1; i <= N; i++)
  {
    VertexList[i] = CreateVertex();
    scanf("%d %d", &VertexList[i]->X, &VertexList[i]->Y);
    InitAdjNodes(i, VertexList[i]);
  }
}

int IsAdjacent(Vertex V1, Vertex V2)
{
  float dist = JumpDistance;
  if (V1->X == 0 && V1->Y == 0)
    dist += Diameter / 2;

  float dX = V2->X - V1->X;
  float dY = V2->Y - V1->Y;
  return dist >= sqrt(dX * dX + dY * dY);
}

Vertex CreateVertex()
{
  Vertex V = (Vertex)malloc(sizeof(struct VNode));
  V->AdjNodes = CreateQueue();
  return V;
}

void InitZeroVertex()
{
  VertexList[0] = CreateVertex();
  VertexList[0]->X = 0;
  VertexList[0]->Y = 0;
  VertexList[0]->AdjNodes = CreateQueue();
}

int IsSafe(int V)
{
  int X = abs(VertexList[V]->X);
  int Y = abs(VertexList[V]->Y);
  int cor = X > Y ? X : Y;
  return cor + JumpDistance >= 50;
}

void InitPathAndDist(int N, int *Path, int *Dist)
{
  for (int i = 0; i <= N; i++)
    Path[i] = Dist[i] = -1;

  Dist[0] = 0;
}

IQueue CreateQueue()
{
  IQueue Queue = (IQueue)malloc(sizeof(struct QNode));
  Queue->Top = 0;
  Queue->Last = -1;
  return Queue;
}

void PushQueue(IQueue Queue, int Data)
{
  Queue->Q[++Queue->Last] = Data;
}

int PopQueue(IQueue Queue)
{
  if (IsQueueEmpty(Queue))
    return -1;
  return Queue->Q[Queue->Top++];
}

int IsQueueEmpty(IQueue Queue)
{
  return Queue->Top > Queue->Last;
}
