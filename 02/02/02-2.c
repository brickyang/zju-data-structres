#include <stdio.h>
#include <stdlib.h>

typedef struct Term * List;
struct Term
{
    int coefficient;
    int degree;
    List next;
};

List createNode(int const coefficient, int const degree)
{
    List node = (List)malloc(sizeof(struct Term));
    node->coefficient = coefficient;
    node->degree = degree;
    node->next = NULL;
    return node;
}

List create()
{
    List head;
    List last;
    int coefficient;
    int degree;

    int n = 0;
    scanf("%d\n", &n);

    for ( int i = 0; i < n; ++i)
    {
        scanf("%d", &coefficient);
        scanf("%d", &degree);
        List node = createNode(coefficient, degree);

        if (i == 0)
            head = node;
        else
            last->next = node;

        last = node;

//        printf("Term %d @ %p with coeff %d and degree %d\n", i, last, last->coefficient, last->degree);
    }

    return head;
}

List pop(List p)
{
    if (p == NULL)
        return NULL;

    List rm = p;
    p = p->next;
    free(rm);
    return p;
}

List add(List p1, List p2)
{
    List head = NULL;
    List last;
    List p;
    int coefficient;
    int degree;

    if (p1 == NULL)
        return p2;
    if (p2 == NULL)
        return p1;

    while (p1 != NULL && p2 != NULL)
    {
        if (p1->degree == p2->degree)
        {
            coefficient = p1->coefficient + p2->coefficient;
            degree = p1->degree;
            p1 = pop(p1);
            p2 = pop(p2);
            if (coefficient == 0)
                continue;
        }
        else if (p1->degree > p2->degree)
        {
            coefficient = p1->coefficient;
            degree = p1->degree;
            p1 = pop(p1);
        }
        else
        {
            coefficient = p2->coefficient;
            degree = p2->degree;
            p2 = pop(p2);
        }

        List node = createNode(coefficient, degree);
        if (head == NULL)
            head = node;
        else
            last->next = node;

        last = node;
    }

    if (p1 != NULL)
        p = p1;
    else
        p = p2;

    while (p != NULL)
    {
        List node = createNode(p->coefficient, p->degree);
        last->next = node;
        last = node;
        p = pop(p);
    }

    return head;
}

List times(List const p, List const s)
{
    List head = (List)malloc(sizeof(struct Term));
    List last = head;
    List sP = p;
    int coefficient;
    int degree;
    while (sP !=NULL)
    {
        last->coefficient = sP->coefficient * s->coefficient;
        last->degree = sP->degree + s->degree;
        if (sP->next != NULL)
        {
            List node = (List)malloc(sizeof(struct Term));
            last->next = node;
            last = node;
        }
        sP = sP->next;
    }
    return head;
}

List multiple(List p1, List p2)
{
    List last = p2;
    List result = NULL;
    while (last != NULL)
    {
        result = add(result, times(p1, last));
        last = last->next;
    }

    return result;
}

void print(List const p)
{
    if (p == NULL)
    {
        printf("%d %d", 0, 0);
        return;
    }
    List last = p;
    while (last != NULL)
    {
        printf("%d %d", last->coefficient, last->degree);
        last = last->next;
        if (last != NULL)
            printf(" ");
    }
}

int main()
{
    List p1 = create();
    List p2 = create();
    List result;

    result = multiple(p1, p2);
    print(result);
    result = add(p1, p2);
    printf("\n");
    print(result);

    return 0;
}

