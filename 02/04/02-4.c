#include <stdio.h>
#include <stdlib.h>

#define MAX 1001

typedef struct SNode *Stack;
typedef struct QNode *Queue;
struct SNode
{
    int data[MAX];
    int top;
};
struct QNode
{
    int data[MAX];
    int front;
    int rear;
};

int pushStack(Stack, int const, int const);
void pushQueue(Queue, int const);
int popStack(Stack);
int popQueue(Queue);
void initSeq(Stack, int);
void readTest(Queue, int);

int main()
{
    int m, n, k, i = 0;
    int results[MAX] = {-1};
    scanf("%d %d %d", &m, &n, &k);
    while (i++ < k)
    {
        Stack stack = (Stack)malloc(sizeof(struct SNode));
        Stack seq = (Stack)malloc(sizeof(struct SNode));
        Queue test = (Queue)malloc(sizeof(struct QNode));
        stack->top = 0;
        seq->top = 0;
        test->front = 0;
        test->rear = 0;
        initSeq(seq, n);
        readTest(test, n);

        int t, s, a, top;
        int posibility = 1;
        while ((t = popQueue(test)) != 0)
        {
            while (stack->top < m && (s = popStack(seq)) != 0 && s < t)
                top = pushStack(stack, s, m);

            if (s == t)
                continue;
            if (s > t)
                pushStack(seq, s, n);
            a = popStack(stack);
            if (a != t)
            {
                posibility = 0;
                break;
            }
        }

        results[i] = posibility;
    }

    {
        for (int i = 1; i <= k; ++i)
        {
            if (results[i] == 0)
                printf("NO\n");
            else
                printf("YES\n");
        }
    }

    return 0;
}

int pushStack(Stack stack, int const data, int const max)
{
    if (stack->top == max)
        return 0;

    stack->data[++stack->top] = data;
    return stack->top;
}

void pushQueue(Queue queue, int const data)
{
    if (queue->front == 0)
        queue->front++;
    queue->data[++queue->rear] = data;
}
int popStack(Stack stack)
{
    if (stack->top == 0)
        return 0;

    int data = stack->data[stack->top];
    stack->data[stack->top--] = 0;
    return data;
}

int popQueue(Queue queue)
{
    if (queue->front > queue->rear)
        return 0;
    int data = queue->data[queue->front];
    queue->data[queue->front++] = 0;
    return data;
}

void initSeq(Stack seq, int n)
{
    int max = n;
    for (; n > 0; n--)
        pushStack(seq, n, max);
}

void readTest(Queue test, int n)
{
    int data;
    int max = n;
    for (; n > 0; n--)
    {
        scanf("%d", &data);
        pushQueue(test, data);
    }
}
