#include "../stacks.h"
#include <stdio.h>

void main()
{
    Stack *s = CreateStack(10);

    PrintStack(s);

    AddToStack(s, 1);

    PrintStack(s);

    AddToStack(s, 2);

    PrintStack(s);

    AddToStack(s, 3);

    PrintStack(s);

    RemoveFromStack(s);

    PrintStack(s);

    printf("\n");
}