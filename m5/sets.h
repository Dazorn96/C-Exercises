#include <stdlib.h>
#include <stdio.h>

typedef struct _Set {
    struct _SetElement **elements;
    int size;
} Set;

typedef struct _SetElement {
    int value;
} SetElement;

Set* CreateSet();
short IsSetEmpty(Set *s);
short BelongsToSet(Set *s, int v);
void AddToSet(Set *s, int v);
void RemoveFromSet(Set *s, int v);
Set* Union(Set *a, Set *b);
Set* Merge(Set *a, Set *b);
Set* Difference(Set *a, Set *b);
void PrintSet(Set *s);

Set* CreateSet() {
    Set *s = malloc(sizeof(Set));

    s->size = 0;
    s->elements = malloc(sizeof(SetElement*));

    return s;
}

short IsSetEmpty(Set *s) {
    return s->size == 0;
}

short BelongsToSet(Set *s, int v) {
    short belongs = 0;

    for(int i = 0; i < s->size; i++) {
        if(s->elements[i]->value == v) {
            belongs = 1;
        }
    }

    return belongs == 1;
}

void AddToSet(Set *s, int v) {
    if(BelongsToSet(s, v) == 1) {
        printf("ELEMENT %d ALREADY EXISTS!\n", v);
        return;
    }

    s->size++;

    s->elements = realloc(s->elements, sizeof(SetElement*) * s->size);

    s->elements[s->size - 1] = malloc(sizeof(SetElement));
    s->elements[s->size - 1]->value = v;
}

void RemoveFromSet(Set *s, int v) {
    short found = 0;

    for(int i = 0; i < s->size; i++) {
        if(s->elements[i]->value == v) {
            s->elements[i]->value = s->elements[s->size - 1]->value;
            found = 1;
        }
    }

    if(found == 0) {
        printf("ELEMENT %d DOES NOT EXISTS!\n", v);
        return;
    }

    s->size--;
    s->elements = realloc(s->elements, sizeof(SetElement*) * s->size);
}

Set* Union(Set *a, Set *b) {
    Set *c = CreateSet(a->size + b->size);

    for(int i = 0; i < a->size; i++) {
        AddToSet(c, a->elements[i]->value);
    }

    for(int i = 0; i < b->size; i++) {
        AddToSet(c, b->elements[i]->value);
    }

    return c;
}

Set* Merge(Set *a, Set *b) {
    Set *c = CreateSet();

    for(int i = 0; i < a->size; i++) {
        for(int j = 0; j < b->size; j++) {
            if(a->elements[i]->value == b->elements[j]->value) {
                AddToSet(c, a->elements[i]->value);
                break;
            }
        }
    }

    return c;
}

Set* Difference(Set *a, Set *b) {
    Set *c = CreateSet();

    for(int i = 0; i < a->size; i++) {
        AddToSet(c, a->elements[i]->value);
    }

    for(int i = 0; i < b->size; i++) {
        if(BelongsToSet(c, b->elements[i]->value)) {
            RemoveFromSet(c, b->elements[i]->value);
        }
    }

    return c;
}

void PrintSet(Set *s) {
    printf("_____ SET VALUES _____\n");

    if(IsSetEmpty(s)) {
        printf("EMPTY SET\n\n");
        return;
    }

    for(int i = 0; i < s->size; i++) {
        printf("%d", s->elements[i]->value);

        if((i + 1) < s->size) {
            printf(" - ");
        }
    }

    printf("\nCARDINALITY: %d", s->size);

    printf("\n\n");
}