#include "../queues.h"
#include <stdio.h>

void main()
{
    Queue *q = CreateQueue(10);

    for(int i = 0; i < 10; i++) {
        AddToQueue(q, i + 1);
    }

    PrintQueue(q);

    RemoveFromQueue(q);

    PrintQueue(q);

    printf("\n");
}