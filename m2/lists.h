#include <stdlib.h>
#include <stdio.h>

typedef struct _List {
    int value;
    struct _List *prev, *next;
} List;

/*
 * CreateList
 * --------------------
 * What it does:
 * allocates space for a new bidirectional list with sentinel
 *
 * Returns:
 * an empty list
 */
List* CreateList() {
    // Allocates space for list head
    List *l = malloc(sizeof(List));

    // Setups list head values
    l->value = 0;
    l->prev = NULL;
    l->next = NULL;

    return l;
}

/*
 * IsEmptyList
 * --------------------
 * What it does:
 * checks if a list is empty
 *
 * Requires:
 * l = a pointer to a list
 * 
 * Returns:
 * a boolean value, 1 if list is empty else 0
 */
short IsEmptyList(List *l) {
    // Checks if list sentinel has a pointer to next cell
    return l->next == NULL;
}

/*
 * AddToList
 * --------------------
 * What it does:
 * adds an item at the end of the list
 *
 * Requires:
 * l = a pointer to a list
 * v = an integer value to add to the list
 */
void AddToList(List *l, int v) {
    // Allocates space for a list cell
    List *q = malloc(sizeof(List));
    q->value = v;

    // Checks if the list is empty
    if(IsEmptyList(l)) {
        // Setups cell values as first cell in list
        q->prev = l;
        q->next = l;
        l->next = q;
        l->prev = q;
    }
    else {
        List *n = l;

        // Searches for last list cell
        do {
            n = n->next;
        }
        while(n->next != l);

        // Links last cell to new cell
        q->prev = n;
        q->next = l;
        n->next = q;

        // Updates sentinel last cell pointer
        l->prev = q;
    }    
}

/*
 * AddToList
 * --------------------
 * What it does:
 * adds an item after a specified position of the list
 *
 * Requires:
 * l = a pointer to a list
 * p = an integer value represing the desired position to add the item
 * v = an integer value to add to the list
 */
void AddToListAt(List *l, int p, int v) {
    List *n = l;
    // Increases position by 1 to avoid sentinel
    int i = p + 1;

    // Allocates space for a list cell
    List *q = malloc(sizeof(List));
    q->value = v;

    // Checks if the list is empty
    if(IsEmptyList(l)) {
        // Setups cell values as first cell in list
        q->prev = l;
        q->next = l;
        l->next = q;
        l->prev = q;

        return;
    }

    // Searches for the desired position's cell
    do {
        n = n->next;
        i--;
    }
    while(n->next != l && i != 0);

    // Checks if the desired position has been found
    if(i == 0) {
        if(n->next == l) {
            l->prev = q;
        }

        q->prev = n;
        q->next = n->next;
        n->next = q;
    }
    else {
        free(q);
        printf("POSITION %d IS OVER LIST SIZE!\n", p);
    }
}

/*
 * RemoveFromList
 * --------------------
 * What it does:
 * removes an item from the list in a specified position
 *
 * Requires:
 * l = a pointer to a list
 * p = an integer value represting the item's position to remove
 */
void RemoveFromList(List *l, int p) {
    List *n = l;
    // Increases position by 1 to avoid sentinel
    int i = p + 1;

    // Searches for the desired position's cell
    do {
        n = n->next;
        i--;
    }
    while(n->next != l && i != 0);

    // Checks if the desired position has been found
    if(i == 0) {
        n->prev->next = n->next;
        n->next->prev = n->prev;
        free(n);
    }
    else {
        printf("POSITION %d IS OVER LIST SIZE!\n", p);
    }
}

/*
 * PrintList
 * --------------------
 * What it does:
 * prints all the items inside the list
 *
 * Requires:
 * l = a pointer to a list
 */
void PrintList(List *l) {
    List *n = l;

    printf("_____ LIST VALUES _____\n");

    if(IsEmptyList(l)) {
        printf("EMPTY LIST\n\n");
        return;
    }

    do {
        n = n->next;
        printf("%d", n->value);

        if(n->next != l) {
            printf(" - ");
        }
    }
    while(n->next != l);

    printf("\n\n");
}