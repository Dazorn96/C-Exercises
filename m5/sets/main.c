#include "../sets.h"
#include <stdio.h>

void main()
{
    Set *s = CreateSet();

    AddToSet(s, 1);
    AddToSet(s, 2);
    AddToSet(s, 3);
    AddToSet(s, 5);
    AddToSet(s, 7);

    RemoveFromSet(s, 2);

    AddToSet(s, 9);

    PrintSet(s);

    Set *t = CreateSet();

    AddToSet(t, 1);
    AddToSet(t, 3);
    AddToSet(t, 11);

    PrintSet(t);

    Set *k = Union(s, t);
    
    printf("\nUNION:\n");
    PrintSet(k);

    printf("\nMERGE:\n");
    Set *k2 = Merge(s, t);
    
    PrintSet(k2);

    printf("\nDIFFERENCE:\n");
    Set *k3 = Difference(s, t);
    
    PrintSet(k3);

    printf("\n");
}