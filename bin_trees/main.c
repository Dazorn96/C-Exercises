#include "../bin_trees.h"
#include <stdio.h>

void main()
{
    BinTree *t = CreateBinTree();

    BinTreeNode *r = malloc(sizeof(BinTreeNode));
    r->value = 1;
    t->root = r;
    
    BinTreeNode *u = malloc(sizeof(BinTreeNode));
    u->value = 2;
    u->parent = r;
    r->sx = u;

    BinTreeNode *u2 = malloc(sizeof(BinTreeNode));
    u2->value = 3;
    u2->parent = r;
    r->dx = u2;

    BinTree *t2 = CreateBinTree();

    BinTreeNode *r2 = malloc(sizeof(BinTreeNode));
    r2->value = 4;
    t2->root = r2;
    
    BinTreeNode *u3 = malloc(sizeof(BinTreeNode));
    u3->value = 5;
    u3->parent = r2;
    r2->sx = u3;

    BinTreeNode *u4 = malloc(sizeof(BinTreeNode));
    u4->value = 6;
    u4->parent = r2;
    r2->dx = u4;

    PrintBinTree(t);
    PrintBinTree(t2);

    BinTree *t3 = MergeBinTrees(t, t2);

    PrintBinTree(t3);

    printf("\n");
}