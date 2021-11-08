#include <stdlib.h>
#include <stdio.h>

typedef struct _Stack {
    int head, size;
    int* elements;
} Stack;

/*
 * CreateStack
 * --------------------
 * What it does:
 * allocates space for a new stack
 * 
 * Requires:
 * n = an integer value representing the desired number of stack's items
 *
 * Returns:
 * an empty stack of dimension n
 */
Stack* CreateStack(int n) {
    Stack *s = malloc(sizeof(Stack));

    s->head = 0;
    s->size = n;
    s->elements = malloc(sizeof(int) * n);

    return s;
}

/*
 * IsEmptyStack
 * --------------------
 * What it does:
 * checks if a stack is empty
 *
 * Requires:
 * s = a pointer to a stack
 * 
 * Returns:
 * a boolean value, 1 if stack is empty else 0
 */
short IsEmptyStack(Stack *s) {
    return s->head == 0;
}

/*
 * ReadFromStack
 * --------------------
 * What it does:
 * reads the value on the stack's head
 *
 * Requires:
 * s = a pointer to a stack
 * 
 * Returns:
 * an integer value representing the item's value
 */
int ReadFromStack(Stack *s) {
    if(IsEmptyStack(s)) {
        printf("THE STACK IS EMPTY!\n");
        return -1;
    }

    return s->elements[s->head - 1];
}

/*
 * AddToStack
 * --------------------
 * What it does:
 * adds an item to the stack's head
 *
 * Requires:
 * s = a pointer to a stack
 * v = an integer value to add
 */
void AddToStack(Stack *s, int v) {
    if(s->head == s->size) {
        printf("THE STACK IS FULL!\n");
    }
    else {
        s->elements[s->head] = v;
        s->head++;
    }
}

/*
 * RemoveFromStack
 * --------------------
 * What it does:
 * removes the item on the stack's head
 *
 * Requires:
 * s = a pointer to a stack
 */
void RemoveFromStack(Stack *s) {
    if(IsEmptyStack(s)) {
        printf("THE STACK IS EMPTY!\n");
        return;
    }

    s->head--;
    s->elements[s->head] = 0;
}

/*
 * PrintStack
 * --------------------
 * What it does:
 * prints all the items inside the stack
 * head is represented by two squared brackets
 *
 * Requires:
 * s = a pointer to a stack
 */
void PrintStack(Stack *s) {
    printf("_____ STACK VALUES _____\n");

    if(IsEmptyStack(s)) {
        printf("EMPTY STACK\n\n");
        return;
    }

    for(int i = 0; i < s->head; i++) {
        if(i == s->head - 1) {
            printf("[ %d ]", s->elements[i]);
        }
        else {
            printf("%d", s->elements[i]);
        }

        if(i + 1 < s->head) {
            printf(" - ");
        }
    }

    printf("\n\n");
}