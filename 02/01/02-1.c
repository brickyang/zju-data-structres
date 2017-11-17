List Merge(List L1, List L2)
{
    List list = (List)malloc(sizeof(struct Node));
    List last = list;
    while (L1->Next != NULL && L2->Next != NULL)
    {
        if (L1->Next->Data <= L2->Next->Data)
        {
            last->Next = L1->Next;
            L1->Next = L1->Next->Next;
            last = last->Next;
        }
        else if (L1->Next->Data > L2->Next->Data)
        {
            last->Next = L2->Next;
            L2->Next = L2->Next->Next;
            last = last->Next;
        }
    }
    if (L1->Next == NULL)
        last->Next = L2->Next;
    else
        last->Next = L1->Next;
    L1->Next = NULL;
    L2->Next = NULL;
    return list;
}
