#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode *Position;
typedef Position AVLTree;
typedef int ElementType;
/* AVL树类型 */
struct AVLNode
{
  ElementType Data; /* 结点数据 */
  AVLTree Left;     /* 指向左子树 */
  AVLTree Right;    /* 指向右子树 */
  int Height;       /* 树高 */
};

int Max(int a, int b);
AVLTree SingleLeftRotation(AVLTree);
AVLTree SingleRightRotation(AVLTree);
AVLTree DoubleLeftRightRotation(AVLTree);
AVLTree DoubleRightLeftRotation(AVLTree A);
AVLTree Insert(AVLTree, ElementType);
int GetHeight(AVLTree);

int main()
{
  int n, v;
  AVLTree T = NULL;
  scanf("%d", &n);
  while (n--)
  {
    scanf("%d", &v);
    T = Insert(T, v);
  }

  printf("%d\n", T->Data);
  return 0;
}

int Max(int a, int b)
{
  return a > b ? a : b;
}

int GetHeight(AVLTree A)
{
  if (!A)
    return -1;

  if (!A->Left && !A->Right)
    return 0;

  if (!A->Right)
    return GetHeight(A->Left) + 1;

  if (!A->Left)
    return GetHeight(A->Right) + 1;

  return Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
}

AVLTree SingleLeftRotation(AVLTree A)
{
  /* 注意：A 必须有一个左子结点 B */
  /* 将 A 与 B 做左单旋，更新 A 与 B 的高度，返回新的根结点 B */
  AVLTree B = A->Left;
  A->Left = B->Right;
  B->Right = A;
  A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
  B->Height = Max(GetHeight(B->Left), A->Height) + 1;
  return B;
}

AVLTree SingleRightRotation(AVLTree A)
{
  /* 注意：A 必须有一个右子结点 B */
  /* 将 A 与 B 做右单旋，更新 A 与 B 的高度，返回新的根结点 B */
  AVLTree B = A->Right;
  A->Right = B->Left;
  B->Left = A;
  A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
  B->Height = Max(GetHeight(B->Right), A->Height) + 1;
  return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A)
{
  /* 注意：A 必须有一个左子结点 B，且 B 必须有一个右子结点 C */
  /* 将 A、B 与 C 做两次单旋，返回新的根结点 C */
  /* 将 B 与 C 做右单旋，C 被返回 */
  A->Left = SingleRightRotation(A->Left);
  /* 将 A 与 C 做左单旋，C 被返回 */
  return SingleLeftRotation(A);
}

AVLTree DoubleRightLeftRotation(AVLTree A)
{
  A->Right = SingleLeftRotation(A->Right);
  return SingleRightRotation(A);
}

/* 将 X 插入 AVL 树 T 中，并且返回调整后的 AVL 树 */
AVLTree Insert(AVLTree T, ElementType X)
{
  if (!T)
  {
    T = (AVLTree)malloc(sizeof(struct AVLNode));
    T->Data = X;
    T->Height = 0;
    T->Left = T->Right = NULL;
  }
  else if (X < T->Data)
  {
    T->Left = Insert(T->Left, X);
    /* 如果需要左旋 */
    if (GetHeight(T->Left) - GetHeight(T->Right) == 2)
    {
      if (X < T->Left->Data)
        T = SingleLeftRotation(T);
      else
        T = DoubleLeftRightRotation(T);
    }
  }
  else if (X > T->Data)
  {
    T->Right = Insert(T->Right, X);
    /* 如果需要右旋 */
    if (GetHeight(T->Left) - GetHeight(T->Right) == -2)
    {
      if (X > T->Right->Data)
        T = SingleRightRotation(T);
      else
        T = DoubleRightLeftRotation(T);
    }
  }

  T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;

  return T;
}
