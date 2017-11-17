#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct TNode *Tree;
struct TNode
{
    int Data;
    Tree Left;
    Tree Right;
};
typedef struct SNode *Stack;
struct SNode
{
    Tree Data;
    Stack Next;
};
Stack S;

Tree makeTree(int);
Stack push(Stack, Tree);
Tree pop(Stack);
int isEmpty(Stack);
Tree top(Stack);
void traverse(Tree, int);

int main()
{
    S = (Stack)malloc(sizeof(struct SNode));
    char s[5];
    int n, v, prevPush = 1;
    scanf("%d", &n);
    n = n * 2 - 1;

    scanf("%s %d", s, &v);
    Tree T = makeTree(v);
    push(S, T);

    Tree newNode, lastPop, parent;
    while (n--)
    {
        scanf("%s", s);
        if (s[1] == 'u')
        {
            scanf("%d", &v);
            newNode = makeTree(v);

            if (prevPush)
                parent = top(S);
            else
                parent = lastPop;

            if (parent->Left == NULL)
                parent->Left = newNode;
            else
                parent->Right = newNode;

            push(S, newNode);
            prevPush = 1;
        }
        else
        {
            lastPop = pop(S);
            prevPush = 0;
        }
    }

    traverse(T, T->Data);
    return 0;
}

void traverse(Tree T, int head)
{
    if (T == NULL)
        return;
    traverse(T->Left, head);
    traverse(T->Right, head);
    printf("%d", T->Data);
    if (T->Data != head)
        printf(" ");
    else
        printf("\n");
}

Tree top(Stack S)
{
    if (isEmpty(S))
        return NULL;

    Stack last = S;
    while (last->Next)
        last = last->Next;

    return last->Data;
}

int isEmpty(Stack S)
{
    return (S->Next == NULL);
}

Tree pop(Stack S)
{
    if (isEmpty(S))
        return NULL;

    Stack last = S;
    while (last->Next->Next)
        last = last->Next;

    Tree node = last->Next->Data;
    free(last->Next);
    last->Next = NULL;
    return node;
}

Stack push(Stack S, Tree t)
{
    Stack node = (Stack)malloc(sizeof(struct SNode));
    node->Data = t;

    Stack last = S;
    while (last->Next)
        last = last->Next;

    last->Next = node;
    return S;
}

Tree makeTree(int value)
{
    Tree node = (Tree)malloc(sizeof(struct TNode));
    node->Data = value;
    node->Left = NULL;
    node->Right = NULL;
    return node;
}
