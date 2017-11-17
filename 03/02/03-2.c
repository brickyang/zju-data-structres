#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct TNode *Tree;
struct TNode
{
    int Left;
    int Right;
};
typedef struct QNode *Queue;
struct QNode
{
    int Data;
    Queue Next;
};

Tree T[MAX];
int root[MAX];
int output[MAX];
Queue Q;

int input(Tree[]);
void makeQueue(int);
Queue push(Queue, int);
Queue pop(Queue);
int isEmpty(Queue);

int main()
{
    int i;
    for (i = 0; i < 10; ++i)
        output[i] = -1;

    Q = (Queue)malloc(sizeof(struct QNode));
    int R = input(T);
    push(Q, R);

    Queue node;
    int len = 0;
    while (!isEmpty(Q))
    {
        node = pop(Q);
        if ((T[node->Data]->Left == -1) && (T[node->Data]->Right == -1))
        {
            output[len] = node->Data;
            len++;
            continue;
        }
        push(Q, T[node->Data]->Left);
        push(Q, T[node->Data]->Right);
    }

    if (len > 0)
        for (i = 0; i < len; ++i)
        {
            printf("%d", output[i]);

            if (i < len - 1)
                printf(" ");
            else
                printf("\n");
        }
    return 0;
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

        scanf("%c %c", &l, &r);
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
            break;

    return i;
}

Queue push(Queue Q, int value)
{
    if (value != -1)
    {
        Queue last = Q;
        while (last->Next != NULL)
            last = last->Next;

        Queue node = (Queue)malloc(sizeof(struct QNode));
        node->Data = value;
        node->Next = NULL;
        last->Next = node;
    }

    return Q;
}

Queue pop(Queue Q)
{
    Queue node = Q->Next;
    Q->Next = Q->Next->Next;
    return node;
}

int isEmpty(Queue Q)
{
    return (Q->Next == NULL);
}
