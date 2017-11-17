#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

typedef struct TNode *HuffmanTree;
struct TNode
{
  char Data;
  int Weight;
  HuffmanTree Left, Right;
};

typedef struct HeapStruct *MinHeap;
struct HeapStruct
{
  HuffmanTree Elements;
  int Size;
  int Capacity;
};

int StrLen(char *);
HuffmanTree CreateTree();
int InsertTree(HuffmanTree, int, char *);
int FindWeight(HuffmanTree, char);
int WPL(HuffmanTree T, int Depth);
HuffmanTree Huffman(MinHeap);
MinHeap CreateHeap(int);
int InsertHeap(MinHeap, HuffmanTree);
HuffmanTree DeleteHeap(MinHeap H);
int IsFull(MinHeap);
int IsEmpty(MinHeap);

void InputHeap(MinHeap H, int N)
{
  for (int i = 0; i < N; i++)
  {
    HuffmanTree Ti = CreateTree();
    scanf("%c %d", &Ti->Data, &Ti->Weight);
    InsertHeap(H, Ti);
    getchar();
  }
}

int main()
{
  int N, M;
  scanf("%d\n", &N);

  MinHeap H = CreateHeap(N);
  InputHeap(H, N);

  HuffmanTree T = Huffman(H);
  int CodeLength = WPL(T, 0);

  scanf("%d\n", &M);
  while (M--)
  {
    HuffmanTree ST = CreateTree();
    int Length = 0;
    int isValid = 1;

    for (int i = 0; i < N; i++)
    {
      int j = 0;
      char ch;
      char code[64] = {0};
      scanf("%c", &ch);
      getchar();

      while ((code[j] = getchar()) != '\n')
        j++;

      int l = StrLen(code);
      if (l > N - 1)
        isValid = 0;
      if (!isValid)
        continue;

      int w = FindWeight(T, ch);
      if ((Length += l * w) > CodeLength)
      {
        isValid = 0;
        continue;
      }

      isValid = InsertTree(ST, w, code);
    }
    if (isValid)
      printf("Yes\n");
    else
      printf("No\n");
  }
  return 0;
}

int InsertTree(HuffmanTree T, int Weight, char *code)
{
  int i = 0;
  HuffmanTree cursor = T;
  while (code[i] != '\n')
  {
    if (code[i] == '1')
    {
      if (!cursor->Right)
        cursor->Right = CreateTree();
      cursor = cursor->Right;
    }
    else
    {
      if (!cursor->Left)
        cursor->Left = CreateTree();
      cursor = cursor->Left;
    }
    i++;
  }

  if (cursor->Left || cursor->Right)
    return 0;
  if (cursor->Weight)
    return 0;
  cursor->Weight = Weight;
  return 1;
}

HuffmanTree CreateTree()
{
  HuffmanTree T = (HuffmanTree)malloc(sizeof(struct TNode));
  T->Data = 0;
  T->Weight = 0;
  T->Left = T->Right = NULL;
  return T;
}

int FindWeight(HuffmanTree T, char ch)
{
  if (!T)
    return 0;

  if (T->Data == ch)
    return T->Weight;

  return FindWeight(T->Left, ch) + FindWeight(T->Right, ch);
}

int WPL(HuffmanTree T, int Depth)
{
  if (!T)
    return 0;
  if (!T->Left && !T->Right)
    return Depth * T->Weight;
  else
    return WPL(T->Left, Depth + 1) + WPL(T->Right, Depth + 1);
}

HuffmanTree Huffman(MinHeap H)
{
  HuffmanTree T;
  while (H->Size > 1)
  {
    T = (HuffmanTree)malloc(sizeof(struct TNode));
    T->Left = DeleteHeap(H);
    T->Right = DeleteHeap(H);
    T->Weight = T->Left->Weight + T->Right->Weight;
    InsertHeap(H, T);
  }
  T = DeleteHeap(H);
  return T;
}

MinHeap CreateHeap(int MaxSize)
{
  MinHeap H = (MinHeap)malloc(sizeof(struct HeapStruct));
  H->Elements = (HuffmanTree)malloc((MaxSize + 1) * sizeof(struct TNode));
  H->Size = 0;
  H->Capacity = MaxSize;
  H->Elements[0].Data = 0;
  H->Elements[0].Weight = -1;
  H->Elements[0].Left = H->Elements[0].Right = NULL;
  return H;
}

int InsertHeap(MinHeap H, HuffmanTree item)
{
  int i;
  if (IsFull(H))
    return 0;

  i = ++H->Size;

  for (; H->Elements[i / 2].Weight > item->Weight; i /= 2)
    H->Elements[i] = H->Elements[i / 2];

  H->Elements[i] = *item;

  return H->Size;
}

HuffmanTree DeleteHeap(MinHeap H)
{
  int Parent, Child;
  HuffmanTree RootItem = (HuffmanTree)malloc(sizeof(struct TNode));
  HuffmanTree temp = (HuffmanTree)malloc(sizeof(struct TNode));

  if (IsEmpty(H))
    return NULL;

  *RootItem = H->Elements[1];
  *temp = H->Elements[H->Size--];
  for (Parent = 1; Parent * 2 <= H->Size; Parent = Child)
  {
    Child = Parent * 2;
    if (Child != H->Size && (H->Elements[Child + 1].Weight < H->Elements[Child].Weight))
      Child++;
    if (temp->Weight <= H->Elements[Child].Weight)
      break;
    else
      H->Elements[Parent] = H->Elements[Child];
  }
  H->Elements[Parent] = *temp;

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

int StrLen(char *str)
{
  regex_t regex;
  char *pattern = "[0-9a-zA-Z_]";
  int regexInit = regcomp(&regex, pattern, REG_EXTENDED);
  if (regexInit)
    printf("Compile regex failed\n");

  int len = 0;
  while (regexec(&regex, str, 0, NULL, 0))
  {
    len++;
    str++;
  }
  regfree(&regex);
  return len;
}
