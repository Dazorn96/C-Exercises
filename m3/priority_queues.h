#include <stdlib.h>
#include <stdio.h>

typedef struct _PriorityQueue {
    int size;
    int length;
    int *queue;
} PriorityQueue;

PriorityQueue* CreatePriorityQueue(int n);
int GetParentIndex(int i);
int GetLeftChildIndex(int i);
int GetRightChildIndex(int i);
void MinHeapify(PriorityQueue *q, int i);
void SwapValues(int *x, int *y);
int GetPriorityQueueMin(PriorityQueue *q);
void AddToPriorityQueue(PriorityQueue *q, int v, short min);
void GrantProprietyThree(PriorityQueue *q, int i, short min);
int ExtractFromPriorityQueue(PriorityQueue *q, short min);
void MinHeapify(PriorityQueue *q, int i);
void MaxHeapify(PriorityQueue *q, int i);
void PrintPriorityQueueAsBinTree(PriorityQueue * q, int i, int l);
void PrintPriorityQueue(PriorityQueue *q);

/*
 * CreatePriorityQueue
 * --------------------
 * What it does:
 * allocates space for a new priority queue
 * 
 * Requires:
 * n = an integer value representing the desired number of queue's items
 * 
 * Returns:
 * an empty priority queue
 */
PriorityQueue* CreatePriorityQueue(int n) {
    PriorityQueue *q = malloc(sizeof(PriorityQueue));

    q->size = n;
    q->queue = malloc(sizeof(int) * q->size);
    q->length = 0;

    return q;
}

int GetParentIndex(int i) {
    return (i - 1) / 2;
}

int GetLeftChildIndex(int i) {
    return (i * 2) + 1;
}

int GetRightChildIndex(int i) {
    return (i * 2) + 2;
}

/*
 * GetPriorityQueueMin
 * --------------------
 * What it does:
 * gets the minimum value inside the priority queue
 * 
 * Requires:
 * q = a pointer to the priority queue
 * 
 * Returns:
 * an integer value which is the minimum of the queue
 */
int GetPriorityQueueMin(PriorityQueue *q) {
    return q->queue[0];
}

/*
 * AddToPriorityQueue
 * --------------------
 * What it does:
 * adds a new item to the priority queue
 * 
 * Requires:
 * q = a pointer to the priority queue
 * v = an integer value to add to the priority queue
 */
void AddToPriorityQueue(PriorityQueue *q, int v, short min) {
    if(q->length == q->size) {
        printf("PRIORITY QUEUE IS FULL!\n");
        return;
    }

    if(q->length == 0) {
        q->queue[0] = v;
        q->length++;
    }
    else {
        q->length++;

        int i = q->length - 1;
        q->queue[i] = v;

        GrantProprietyThree(q, i, min);
    }
}

void GrantProprietyThree(PriorityQueue *q, int i, short min) {
    if(min == 1) {
        while(i != 0 && q->queue[GetParentIndex(i)] > q->queue[i]) {
            SwapValues(&q->queue[i], &q->queue[GetParentIndex(i)]);
            i = GetParentIndex(i);
        }
    }
    else {
        while(i != 0 && q->queue[GetParentIndex(i)] < q->queue[i]) {
            SwapValues(&q->queue[i], &q->queue[GetParentIndex(i)]);
            i = GetParentIndex(i);
        }
    }
}

/*
 * ExtractMinFromPriorityQueue
 * --------------------
 * What it does:
 * extracts the minimum value from the priority queue
 * 
 * Requires:
 * q = a pointer to the priority queue
 * 
 * Returns:
 * an integer value which is the minimum of the queue
 */
int ExtractFromPriorityQueue(PriorityQueue *q, short min) {
    if(q->length == 0) {
        printf("PRIORITY QUEUE IS EMPTY!\n");
        return __INT_MAX__;
    }
    else if (q->length == 1) {
        q->length--;
        return q->queue[0];
    }

    int value = q->queue[0];
    q->queue[0] = q->queue[q->length - 1];
    q->length--;

    printf("EXTRACTED VALUE: %d\n", value);

    if(min == 1) {
        MinHeapify(q, 0);
    }
    else {
        MaxHeapify(q, 0);
    }

    return value;
}

void MinHeapify(PriorityQueue *q, int i) {
    printf("BINARY TREE STATUS WHILE MIN-HEAPIFY\n");
    PrintPriorityQueueAsBinTree(q, 0, 0);
    printf("\n");

    int l = GetLeftChildIndex(i);
    int r = GetRightChildIndex(i);
    int min = i;

    if(l < q->length && q->queue[l] < q->queue[min]) {
        min = l;
    }

    if(r < q->length && q->queue[r] < q->queue[min]) {
        min = r;
    }

    if(min != i) {
        SwapValues(&q->queue[i], &q->queue[min]);
        MinHeapify(q, min);
    }
}

void MaxHeapify(PriorityQueue *q, int i) {
    printf("BINARY TREE STATUS WHILE MAX-HEAPIFY\n");
    PrintPriorityQueueAsBinTree(q, 0, 0);
    printf("\n");

    int l = GetLeftChildIndex(i);
    int r = GetRightChildIndex(i);
    int max = i;

    if(l < q->length && q->queue[l] > q->queue[max]) {
        max = l;
    }

    if(r < q->length && q->queue[r] > q->queue[max]) {
        max = r;
    }

    if(max != i) {
        SwapValues(&q->queue[i], &q->queue[max]);
        MaxHeapify(q, max);
    }
}

void PrintPriorityQueueAsBinTree(PriorityQueue * q, int i, int l) {
    int si = GetLeftChildIndex(i);
    
    if(si < q->length) {
        PrintPriorityQueueAsBinTree(q, si, l + 1);
    }

    for(int k = 0; k < l; k++) {
        printf("\t");
    }

    printf("%d\n", q->queue[i]);

    int di = GetRightChildIndex(i);

    if(di < q->length) {
        PrintPriorityQueueAsBinTree(q, di, l + 1);
    }
}

/*
 * PrintPriorityQueue
 * --------------------
 * What it does:
 * prints the priority queue as array first and also as binary tree
 * 
 * Requires:
 * q = a pointer to the priority queue
 */
void PrintPriorityQueue(PriorityQueue *q) {
    printf("_____ PRIORITY QUEUE VALUES _____\n");

    for(int i = 0; i < q->length; i++) {
        printf("%d", q->queue[i]);

        if(i + 1 < q->length) {
            printf(" - ");
        }
    }

    printf("\n_____ PRIORITY QUEUE BINARY TREE _____\n");

    PrintPriorityQueueAsBinTree(q, 0, 0);

    printf("\n\n");
}

void SwapValues(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}