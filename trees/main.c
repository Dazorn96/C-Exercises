#include "../trees.h"
#include <stdio.h>

void main()
{
    Tree *t = CreateTree();

    TreeNode *r = malloc(sizeof(TreeNode));
    r->value = 1;
    AddRoot(t, r);

    TreeNode *u = malloc(sizeof(TreeNode));
    u->value = 2;
    AddChildNode(r, u);

    TreeNode *u2 = malloc(sizeof(TreeNode));
    u2->value = 3;
    AddChildNode(r, u2);

    TreeNode *u3 = malloc(sizeof(TreeNode));
    u3->value = 4;
    AddChildNode(u2, u3);

    TreeNode *u4 = malloc(sizeof(TreeNode));
    u4->value = 5;
    AddSiblingNode(u2, u4);

    Tree *t2 = CreateTree();
    TreeNode *r2 = malloc(sizeof(TreeNode));
    r2->value = 7;
    AddRoot(t2, r2);

    AddSubtree(u, u, t2);

    PrintTree(t);

    printf("\n");
}