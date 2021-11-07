#include <stdlib.h>
#include <stdio.h>

#define PREVISIT 1
#define POSTVISIT 2
#define INVISIT 3

typedef struct _BinTree {
    struct _BinTreeNode *root;
} BinTree;

typedef struct _BinTreeNode {
    int value;
    struct _BinTreeNode *parent, *sx, *dx;
} BinTreeNode;

/*
 * CreateBinTree
 * --------------------
 * What it does:
 * allocates space for a new binary tree
 * 
 * Returns:
 * an empty binary tree
 */
BinTree* CreateBinTree() {
    BinTree *t = malloc(sizeof(BinTree));

    t->root = NULL;
    
    return t;
}

/*
 * IsEmptyBinTree
 * --------------------
 * What it does:
 * checks if a binary tree is empty
 * 
 * Requires:
 * t = a pointer to a binary tree
 * 
 * Returns:
 * a boolean value, 1 if binary tree is empty else 0
 */
short IsEmptyBinTree(BinTree *t) {
    return t->root == NULL;
}

/*
 * GetLevel
 * --------------------
 * What it does:
 * gets the vertical level of a node
 * 
 * Requires:
 * u = a pointer to a node
 * 
 * Returns:
 * an integer value representing the node vertical level
 */
int GetLevel(BinTreeNode *u) {
    BinTreeNode *v = u;
    int level = 0;

    while(v->parent != NULL) {
        level++;
        v = v->parent;
    }

    return level;
}

/*
 * MergeBinTrees
 * --------------------
 * What it does:
 * merges two binary trees into a single one
 * 
 * Requires:
 * t = a pointer to a binary tree
 * u = a pointer to a binary tree
 * 
 * Returns:
 * a binary tree, with t as sx and u as dx
 */
BinTree* MergeBinTrees(BinTree *t, BinTree *u) {
    BinTree *z = malloc(sizeof(BinTree));

    BinTreeNode *r = malloc(sizeof(BinTreeNode));
    z->root = r;

    t->root->parent = z->root;
    u->root->parent = z->root;

    z->root->sx = t->root;
    z->root->dx = u->root;

    free(t);
    free(u);

    return z;
}

void VisitBinTreeNodes(BinTreeNode *u, int mode) {
    if(mode == PREVISIT) {
        PrintNode(u);
    }

    if(u->sx != NULL) {
        VisitBinTreeNodes(u->sx, mode);
    }

    if(mode == INVISIT) {
        PrintNode(u);
    }

    if(u->dx != NULL) {
        VisitBinTreeNodes(u->dx, mode);
    }

    if(mode == POSTVISIT) {
        PrintNode(u);
    }
}

/*
 * PrintBinTree
 * --------------------
 * What it does:
 * prints all the nodes inside the binary tree
 * 
 * Requires:
 * t = a pointer to a binary tree
 */
void PrintBinTree(BinTree *t) {
    printf("_____ BINARY TREE NODES _____\n");

    printf("PRE VISIT:\n");
    VisitBinTreeNodes(t->root, PREVISIT);

    printf("POST VISIT:\n");
    VisitBinTreeNodes(t->root, POSTVISIT);

    printf("IN VISIT:\n");
    VisitBinTreeNodes(t->root, INVISIT);

    printf("\n\n");
}

void PrintNode(BinTreeNode *u) {
    for(int i = 0; i < GetLevel(u); i++) {
        printf("\t");
    }

    if(u->parent == NULL) {
        printf("%d[r]\n", u->value);
    }
    else {
        printf("%d[%d]\n", u->value, u->parent->value);
    }
}