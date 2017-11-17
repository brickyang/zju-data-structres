#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *BinTree;
struct TNode
{
  ElementType Data;
  BinTree Left;
  BinTree Right;
};

int compareTree(BinTree, BinTree);
BinTree makeTree(int);
BinTree insertTree(BinTree tree, int value);
BinTree makeNode(int);

int main()
{
  int n, l;
  scanf("%d", &n);
  while (n)
  {
    scanf("%d", &l);
    BinTree tree_1 = makeTree(n);
    while (l--)
    {
      BinTree tree = makeTree(n);
      int result = compareTree(tree_1, tree);
      if (result == 1)
        printf("Yes\n");
      else
        printf("No\n");
    }
    scanf("%d", &n);
  }
  return 0;
}

int compareTree(BinTree t_1, BinTree t_2)
{
  if (t_1 == NULL && t_2 == NULL)
    return 1;
  if ((t_1 == NULL && t_2 != NULL) || (t_1 != NULL && t_2 == NULL))
    return 0;
  if (t_1->Data == t_2->Data)
    return compareTree(t_1->Left, t_2->Left) && compareTree(t_1->Right, t_2->Right);
  return 0;
}

BinTree makeTree(int n)
{
  BinTree tree = NULL;
  for (int i = 0, v = 0; i < n; i++)
  {
    scanf("%d", &v);
    tree = insertTree(tree, v);
  }
  return tree;
}

BinTree insertTree(BinTree tree, int value)
{
  if (!tree)
    tree = makeNode(value);
  else if (tree->Data > value)
    tree->Left = insertTree(tree->Left, value);
  else if (tree->Data < value)
    tree->Right = insertTree(tree->Right, value);

  return tree;
}

BinTree makeNode(int value)
{
  BinTree node = (BinTree)malloc(sizeof(struct TNode));
  node->Data = value;
  node->Left = node->Right = NULL;
  return node;
}
