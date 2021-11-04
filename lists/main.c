#include "../lists.h"
#include <stdio.h>

void main()
{
    List *l = CreateList();

    AddToListAt(l, 0, 99);

    PrintList(l);

    for(int i = 0; i < 10; i++) {
        AddToList(l, i + 1);
    }

    PrintList(l);

    AddToListAt(l, 10, 100);

    PrintList(l);

    RemoveFromList(l, 11);

    PrintList(l);

    printf("\n");
}