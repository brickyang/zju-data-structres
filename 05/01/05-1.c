#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct HeapStruct *MinHeap;
struct HeapStruct
{
  ElementType *Elements;
  int Size;
  int Capacity;
};

MinHeap Create(int, int);
int Insert(MinHeap, ElementType);
ElementType Delete(MinHeap H);
int IsFull(MinHeap);
int IsEmpty(MinHeap);
void Print(MinHeap, int);

int main()
{
  int N, M, i;
  ElementType item;
  MinHeap H = Create(1000, -99999);
  scanf("%d %d", &N, &M);
  for (i = 0; i < N; i++)
  {
    scanf("%d", &item);
    Insert(H, item);
  }

  int *MA = malloc(M * sizeof(int));
  for (i = 0; i < M; i++)
    scanf("%d", &MA[i]);
  for (i = 0; i < M; i++)
    Print(H, MA[i]);

  return 0;
}

MinHeap Create(int MaxSize, ElementType MaxData)
{
  MinHeap H = (MinHeap)malloc(sizeof(struct HeapStruct));
  H->Elements = malloc((MaxSize + 1) * sizeof(ElementType));
  H->Size = 0;
  H->Capacity = MaxSize;
  H->Elements[0] = MaxData;
  return H;
}

int Insert(MinHeap H, ElementType item)
{
  int i;
  if (IsFull(H))
    return 0;

  i = ++H->Size;

  for (; H->Elements[i / 2] > item; i /= 2)
    H->Elements[i] = H->Elements[i / 2];
  H->Elements[i] = item;

  return H->Size;
}

ElementType Delete(MinHeap H)
{
  int Parent, Child;
  ElementType RootItem, temp;

  if (IsEmpty(H))
    return -1;

  RootItem = H->Elements[1];
  temp = H->Elements[H->Size--];
  for (Parent = 1; Parent * 2 <= H->Size; Parent = Child)
  {
    Child = Parent * 2;
    if (Child != H->Size && (H->Elements[Child + 1] < H->Elements[Child]))
      Child++;
    if (temp <= H->Elements[Child])
      break;
    else
      H->Elements[Parent] = H->Elements[Child];
  }
  H->Elements[Parent] = temp;

  return RootItem;
}

int IsFull(MinHeap H)
{
  return H->Size == H->Capacity;
}

int IsEmpty(MinHeap H)
{
  return H->Size == 0;
}

void Print(MinHeap H, int i)
{
  for (; i > 0; i /= 2)
  {
    printf("%d", H->Elements[i]);
    if (i > 1)
      printf(" ");
    else
      printf("\n");
  }
}
