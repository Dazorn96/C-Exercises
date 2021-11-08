#include "../priority_queues.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void main()
{
    PriorityQueue *q = CreatePriorityQueue(10);

    srand(time(NULL));

    for(int i = 0; i < q->size; i++) {
        AddToPriorityQueue(q, rand() % 100, 0);
    }

    PrintPriorityQueue(q);

    ExtractFromPriorityQueue(q, 0);

    PrintPriorityQueue(q);

    printf("\n");
}