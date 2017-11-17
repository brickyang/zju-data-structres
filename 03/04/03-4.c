#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

// void PreorderTraversal(BinTree BT); /* 先序遍历，由裁判实现，细节不表 */
// void InorderTraversal(BinTree BT);  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);
Position Find(BinTree BST, ElementType X);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    BST = Delete(BST, 8);
    printf("Preorder:");
    // PreorderTraversal(BST);
    printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL)
            printf("%d is not found\n", X);
        else
        {
            printf("%d is found\n", Tmp->Data);
            if (Tmp == MinP)
                printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp == MaxP)
                printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:");
    // InorderTraversal(BST);
    printf("\n");

    return 0;
}

BinTree Insert(BinTree BST, ElementType X)
{
    if (BST == NULL)
    {
        BST = (BinTree)malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = NULL;
        BST->Right = NULL;
        return BST;
    }

    if (BST->Data > X)
    {

        BinTree Left = Insert(BST->Left, X);
        BST->Left = Left;
    }
    else
    {
        BinTree Right = Insert(BST->Right, X);
        BST->Right = Right;
    }

    return BST;
}

BinTree Delete(BinTree BST, ElementType X)
{
    Position Tmp;
    if (!Find(BST, X))
    {
        printf("Not Found\n");
        return BST;
    }

    if (BST->Data > X)
        BST->Left = Delete(BST->Left, X);
    else if (BST->Data < X)
        BST->Right = Delete(BST->Right, X);
    else if (BST->Left && BST->Right)
    {
        Tmp = FindMax(BST->Left);
        BST->Data = Tmp->Data;
        BST->Left = Delete(BST->Left, BST->Data);
    }
    else
    {
        Tmp = BST;
        if (BST->Left == NULL)
            BST = BST->Right;
        else if (BST->Right == NULL)
            BST = BST->Left;
        free(Tmp);
    }
    return BST;
}

Position Find(BinTree BST, ElementType X)
{
    if (BST == NULL)
        return NULL;

    if (BST->Data == X)
        return BST;
    else if (BST->Data > X)
        return Find(BST->Left, X);
    else if (BST->Data < X)
        return Find(BST->Right, X);
    else
        return NULL;
}

Position FindMin(BinTree BST)
{
    if (BST == NULL)
        return NULL;

    if (BST->Left == NULL)
        return BST;
    else
        return FindMin(BST->Left);
}

Position FindMax(BinTree BST)
{
    if (BST == NULL)
        return NULL;

    if (BST->Right == NULL)
        return BST;
    else
        return FindMax(BST->Right);
}
