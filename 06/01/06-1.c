#include <stdio.h>
#include <stdlib.h>

typedef int Vertex;
typedef int WeightType;
const int MaxVertaxNum = 10;

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
  Vertex AdjV;
  WeightType Weight;
  PtrToAdjVNode Next;
};

typedef struct VNode
{
  PtrToAdjVNode FirstEdge;
  int Visited;
} AdjList[MaxVertaxNum];

typedef struct GNode *PtrToGNode;
struct GNode
{
  int Nv;
  int Ne;
  AdjList G;
};
typedef PtrToGNode LGraph;

typedef struct ENode *PtrToENode;
struct ENode
{
  Vertex V1, V2;
  WeightType Weight;
};
typedef PtrToENode Edge;

typedef struct QNode *PtrToQNode;
struct QNode
{
  int Q[MaxVertaxNum];
  int Top;
  int Last;
};
typedef PtrToQNode GQueue;

void PushAdjVNode(LGraph, GQueue, PtrToAdjVNode);
int IsQueueEmpty(GQueue);
void ResetQueue(GQueue);
int PopQueue(GQueue);
void PushQueue(GQueue, int);
void DFS(LGraph, PtrToAdjVNode);
void ResetVisited(LGraph);
LGraph CreateGraph(int);
void InsertEdge(LGraph, Edge);

int main()
{
  int Nv, i;
  scanf("%d", &Nv);
  LGraph Graph = CreateGraph(Nv);
  scanf("%d", &Graph->Ne);
  for (i = 0; i < Graph->Ne; i++)
  {
    Edge E = (Edge)malloc(sizeof(struct ENode));
    scanf("%d %d", &E->V1, &E->V2);
    E->Weight = 1;
    InsertEdge(Graph, E);
  }

  for (i = 0; i < Graph->Nv; i++)
  {
    if (Graph->G[i].Visited)
      continue;
    Graph->G[i].Visited = 1;
    printf("{ %d ", i);
    DFS(Graph, Graph->G[i].FirstEdge);
    printf("}\n");
  }

  ResetVisited(Graph);

  GQueue Queue = (GQueue)malloc(sizeof(struct QNode));
  Queue->Top = 0;
  Queue->Last = -1;

  for (i = 0; i < Graph->Nv; i++)
  {
    if (Graph->G[i].Visited)
      continue;

    Graph->G[i].Visited = 1;
    printf("{ %d ", i);
    PushAdjVNode(Graph, Queue, Graph->G[i].FirstEdge);
    while (!IsQueueEmpty(Queue))
    {
      int V = PopQueue(Queue);
      printf("%d ", V);
      PushAdjVNode(Graph, Queue, Graph->G[V].FirstEdge);
    }
    printf("}\n");
    ResetQueue(Queue);
  }

  return 0;
}

void PushAdjVNode(LGraph Graph, GQueue Queue, PtrToAdjVNode VNode)
{
  PtrToAdjVNode last = VNode;
  while (last)
  {
    if (!Graph->G[last->AdjV].Visited)
    {
      PushQueue(Queue, last->AdjV);
      Graph->G[last->AdjV].Visited = 1;
    }
    last = last->Next;
  }
}

int IsQueueEmpty(GQueue Queue)
{
  return Queue->Top > Queue->Last;
}

void ResetQueue(GQueue Queue)
{
  Queue->Top = 0;
  Queue->Last = -1;
}

int PopQueue(GQueue Queue)
{
  if (IsQueueEmpty(Queue))
    return -1;
  return Queue->Q[Queue->Top++];
}

void PushQueue(GQueue Queue, int Data)
{
  Queue->Q[++Queue->Last] = Data;
}

void DFS(LGraph Graph, PtrToAdjVNode AdjVNode)
{
  if (!AdjVNode)
    return;

  if (!Graph->G[AdjVNode->AdjV].Visited)
  {
    Graph->G[AdjVNode->AdjV].Visited = 1;
    printf("%d ", AdjVNode->AdjV);
    DFS(Graph, Graph->G[AdjVNode->AdjV].FirstEdge);
  }

  DFS(Graph, AdjVNode->Next);
}

void ResetVisited(LGraph Graph)
{
  for (int i = 0; i < Graph->Nv; i++)
    Graph->G[i].Visited = 0;
}

void InsertEdge(LGraph Graph, Edge E)
{
  PtrToAdjVNode NewNode, last;
  NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
  NewNode->AdjV = E->V2;
  NewNode->Weight = E->Weight;
  if (!Graph->G[E->V1].FirstEdge || Graph->G[E->V1].FirstEdge->AdjV > NewNode->AdjV)
  {
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;
  }
  else
  {
    last = Graph->G[E->V1].FirstEdge;
    while (last->Next && last->Next->AdjV < NewNode->AdjV)
      last = last->Next;
    NewNode->Next = last->Next;
    last->Next = NewNode;
  }

  NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
  NewNode->AdjV = E->V1;
  NewNode->Weight = E->Weight;
  if (!Graph->G[E->V2].FirstEdge || Graph->G[E->V2].FirstEdge->AdjV > NewNode->AdjV)
  {
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
  }
  else
  {
    last = Graph->G[E->V2].FirstEdge;
    while (last->Next && last->Next->AdjV < NewNode->AdjV)
      last = last->Next;
    NewNode->Next = last->Next;
    last->Next = NewNode;
  }
}

LGraph CreateGraph(int VertexNum)
{
  Vertex V, W;
  LGraph Graph;

  Graph = (LGraph)malloc(sizeof(struct GNode));
  Graph->Nv = VertexNum;
  Graph->Ne = 0;

  for (V = 0; V < Graph->Nv; V++)
  {
    Graph->G[V].FirstEdge = NULL;
    Graph->G[V].Visited = 0;
  }

  return Graph;
}
