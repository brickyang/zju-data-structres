#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct TNode *Tree;
struct TNode
{
    char Data;
    int Left;
    int Right;
    int head;
};
Tree T1[MAX];
Tree T2[MAX];
int root[MAX];

int input(Tree[]);
int isomophic(int, int);

int main()
{
    for (int i = 0; i < 10; ++i)
        T1[i] = T2[i] = NULL;

    int R1 = input(T1);
    int R2 = input(T2);

    if (isomophic(R1, R2))
        printf("Yes\n");
    else
        printf("No\n");

    return 0;
}

int isomophic(int R1, int R2)
{
    if (R1 == -1 && R2 == -1)
        return 1;
    if ((R1 == -1 && R2 != -1) || (R1 != -1 && R2 == -1))
        return 0;
    if (T1[R1]->Data != T2[R2]->Data)
        return 0;
    if ((T1[R1]->Left == -1) && (T2[R2]->Left == -1))
        return isomophic(T1[R1]->Right, T2[R2]->Right);
    if (((T1[R1]->Left != -1) && (T2[R2]->Left != -1)) && (T1[T1[R1]->Left]->Data == T2[T2[R2]->Left]->Data))
        return (isomophic(T1[R1]->Left, T2[R2]->Left) && isomophic(T1[R1]->Right, T2[R2]->Right));
    else
        return (isomophic(T1[R1]->Left, T2[R2]->Right) && isomophic(T1[R1]->Right, T2[R2]->Left));
}

int input(Tree T[])
{
    int n, i;
    char l, r;
    scanf("%d", &n);

    if (n == 0)
        return -1;

    for (i = 0; i < n; ++i)
        root[i] = 1;

    for (i = 0; i < n; i++)
    {
        getchar();
        Tree node = (Tree)malloc(sizeof(struct TNode));
        node->Left = -1;
        node->Right = -1;

        scanf("%c %c %c", &node->Data, &l, &r);
        if (l != '-')
        {
            node->Left = l - '0';
            root[node->Left] = 0;
        }
        if (r != '-')
        {
            node->Right = r - '0';
            root[node->Right] = 0;
        }

        T[i] = node;
    }

    for (i = 0; i < n; ++i)
        if (root[i])
            return i;
}
