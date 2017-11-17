#include <stdio.h>
#include <stdlib.h>

typedef struct Node *List;
struct Node
{
    int address;
    int data;
    int next;
    List link;
};
int total = 0;
int k = 0;
int n = 0;

List findByIndex(List const, int const);
List input();
List sort(List, int const);
List reverse(List const, int const);

int main()
{
    int first = 0;
    scanf("%d %d %d", &first, &total, &k);

    List list1 = input();
    List list2 = sort(list1, first);
    n = total / k;

    List section = list2;
    List last;
    for (int i = 0; i < n; ++i)
    {
        reverse(section, k);
        section = findByIndex(section->link, k);
    }

    while ((list2 = list2->link) && list2->link != NULL)
        printf("%05d %d %05d\n", list2->address, list2->data, list2->next);

    printf("%05d %d -1\n", list2->address, list2->data);

    return 0;
}

List reverse(List const head, int const k)
{
    if (head->link == NULL || head->link->link == NULL)
        return head;

    List last = head;
    List p;
    List rm;
    for (int i = 0; i < k - 1; ++i)
    {
        p = findByIndex(head->link, k - 1);
        rm = p->link;
        p->link = rm->link;
        p->next = (rm->link != NULL) ? rm->link->address : -1;
        rm->link = last->link;
        rm->next = last->link->address;
        last->link = rm;
        last->next = rm->address;
        last = rm;
    }

    return head->link;
}

List sort(List list1, int const first)
{
    total = 0;
    List list2 = (List)malloc(sizeof(struct Node));
    List last = list2;
    List p;
    int find = first;
    while (find != -1)
    {
        p = list1;
        while (p->link != NULL)
            if (p->link->address == find)
            {
                last->link = p->link;
                p->link = p->link->link;
                last = last->link;
                find = last->next;
                total++;
                break;
            }
            else
                p = p->link;
    }
    last->link = NULL;
    return list2;
}

List input()
{
    List head = (List)malloc(sizeof(struct Node));
    List last = head;
    for (int i = 0; i < total; ++i)
    {
        List node = (List)malloc(sizeof(struct Node));
        scanf("%d %d %d", &node->address, &node->data, &node->next);
        last->link = node;
        last = node;
    }
    return head;
}

List findByIndex(List const head, int const index)
{
    int i = 0;
    List last = head;
    while (++i != index && (last = last->link) != NULL)
        ;
    return last;
}
