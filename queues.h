#include <stdlib.h>
#include <stdio.h>

typedef struct _Queue {
    int head, length, size;
    int* elements;
} Queue;

/*
 * CreateQueue
 * --------------------
 * What it does:
 * allocates space for a new queue
 * 
 * Requires:
 * n = an integer value representing the desired number of queue's items
 *
 * Returns:
 * an empty queue of dimension n
 */
Queue* CreateQueue(int n) {
    Queue *q = malloc(sizeof(Queue));

    q->head = q->length = 0;
    q->size = n;
    q->elements = malloc(sizeof(int) * n);

    return q;
}

/*
 * IsEmptyQueue
 * --------------------
 * What it does:
 * checks if a queue is empty
 *
 * Requires:
 * q = a pointer to a queue
 * 
 * Returns:
 * a boolean value, 1 if queue is empty else 0
 */
short IsEmptyQueue(Queue *q) {
    return q->length == 0;
}

/*
 * ReadFromQueue
 * --------------------
 * What it does:
 * reads the value on the queue's head
 *
 * Requires:
 * q = a pointer to a queue
 * 
 * Returns:
 * an integer value representing the item's value
 */
int ReadFromQueue(Queue *q) {
    if(IsEmptyQueue(q)) {
        printf("THE QUEUE IS EMPTY!\n");
        return -1;
    }

    return q->elements[q->head];
}

/*
 * AddToQueue
 * --------------------
 * What it does:
 * adds an item to the queue's end
 *
 * Requires:
 * q = a pointer to a queue
 * v = an integer value to add
 */
void AddToQueue(Queue *q, int v) {
    if(q->length == q->size) {
        printf("THE QUEUE IS FULL!\n");
    }
    else {
        int p = (q->head + q->length) % q->size;

        q->elements[p] = v;
        q->length++;
    }
}

/*
 * RemoveFromQueue
 * --------------------
 * What it does:
 * removes the item on the queue's head
 *
 * Requires:
 * q = a pointer to a queue
 * 
 * Returns:
 * an integer value dequeued from queue
 */
int RemoveFromQueue(Queue *q) {
    if(IsEmptyQueue(q)) {
        printf("THE QUEUE IS EMPTY!\n");
        return -1;
    }

    int v = q->elements[q->head];

    q->length--;

    for(int i = q->head; i < q->length; i++) {
        q->elements[i] = q->elements[i + 1];
    }

    q->elements[q->length] = 0;

    printf("DEQUEUED %d FROM QUEUE\n", v);

    return v;
}

/*
 * PrintQueue
 * --------------------
 * What it does:
 * prints all the items inside the queue
 * head is represented by two squared brackets
 * end is represented by two rounded brackets
 *
 * Requires:
 * q = a pointer to a queue
 */
void PrintQueue(Queue *q) {
    printf("_____ QUEUE VALUES _____\n");

    if(IsEmptyQueue(q)) {
        printf("EMPTY QUEUE\n\n");
        return;
    }

    for(int i = q->head; i < q->length; i++) {
        if(i == q->head) {
            printf("[ %d ]", q->elements[i]);
        }
        else if(i + 1 == q->length) {
            printf("( %d )", q->elements[i]);
        }
        else {
            printf("%d", q->elements[i]);
        }

        if(i + 1 < q->length) {
            printf(" - ");
        }
    }

    printf("\n\n");
}