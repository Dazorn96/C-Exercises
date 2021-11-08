#include "../priority_queues.h"
#include <time.h>
#include <stdio.h>

void main()
{
    PriorityQueue *q = CreatePriorityQueue(10);

    srand(time(NULL));

    for(int i = 0; i < q->size; i++) {
        AddToPriorityQueue(q, rand() % 100, 1);
    }

    PrintPriorityQueue(q);

    ExtractFromPriorityQueue(q, 1);

    PrintPriorityQueue(q);

    printf("\n");
}