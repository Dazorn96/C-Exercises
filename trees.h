#include <stdlib.h>
#include <stdio.h>

typedef struct _Tree {
    struct _TreeNode *root;
} Tree;

typedef struct _TreeNode {
    short root;
    int value;
    struct _TreeNode *parent, *child, *sibling;
} TreeNode;

/*
 * CreateTree
 * --------------------
 * What it does:
 * allocates space for a new tree
 * 
 * Returns:
 * an empty tree
 */
Tree* CreateTree() {
    Tree *t = malloc(sizeof(Tree));

    t->root = NULL;
    
    return t;
}

/*
 * IsEmptyTree
 * --------------------
 * What it does:
 * checks if a tree is empty
 * 
 * Requires:
 * t = a pointer to a tree
 * 
 * Returns:
 * a boolean value, 1 if tree is empty else 0
 */
short IsEmptyTree(Tree *t) {
    return t->root == NULL;
}

/*
 * IsLeaf
 * --------------------
 * What it does:
 * checks if a tree node is a leaf
 * 
 * Requires:
 * u = a pointer to a node
 * 
 * Returns:
 * a boolean value, 1 if the node is a leaf else 0
 */
short IsLeaf(TreeNode *u) {
    return u->child == NULL;
}

/*
 * GetLastSibling
 * --------------------
 * What it does:
 * gets the last sibling of node
 * 
 * Requires:
 * u = a pointer to a node
 * 
 * Returns:
 * a pointer to a node
 */
TreeNode* GetLastSibling(TreeNode *u) {
    TreeNode *s = u;
    
    while(s->sibling != NULL) {
        s = s->sibling;
    }

    return s;
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
int GetLevel(TreeNode *u) {
    TreeNode *v = u;
    int level = 0;

    while(v->parent != NULL) {
        level++;
        v = v->parent;
    }

    return level;
}

/*
 * AddRoot
 * --------------------
 * What it does:
 * adds a node as tree's root
 * 
 * Requires:
 * t = a pointer to a tree
 * u = a pointer to a node
 */
void AddRoot(Tree *t, TreeNode *u) {
    u->root = 1;
    t->root = u;
}

/*
 * AddSiblingNode
 * --------------------
 * What it does:
 * adds a node to the tree
 * 
 * Requires:
 * p = a pointer to the previous node
 * u = a pointer to a node
 */
void AddSiblingNode(TreeNode *p, TreeNode *u) {
    if(p->root) {
        printf("NODE IS ROOT!\n");
        return;
    }

    if(p->sibling == NULL) {
        p->sibling = u;
    }
    else {
        u->sibling = p->sibling;
        p->sibling = u;
    }

    u->parent = p->parent;
}

/*
 * AddChildNode
 * --------------------
 * What it does:
 * adds a node to the tree
 * 
 * Requires:
 * p = a pointer to the parent node
 * u = a pointer to a node
 */
void AddChildNode(TreeNode *p, TreeNode *u) {
    if(p->child == NULL) {
        p->child = u;
    }
    else {
        AddSiblingNode(GetLastSibling(p->child), u);
    }
    
    u->parent = p;
}

/*
 * AddSubtree
 * --------------------
 * What it does:
 * adds a sub-tree to the tree
 * 
 * Requires:
 * p = a pointer to the parent node
 * s = a pointer to the sibling node
 * t = a pointer to the sub-tree
 */
void AddSubtree(TreeNode *p, TreeNode *s, Tree *t) {
    t->root->root = 0;
    
    if(p == s) {
        t->root->parent = p;
        t->root->sibling = p->child;
        p->child = t->root;
    }
    else {
        AddSiblingNode(s, t->root);
    }

    free(t);
}

void PreVisitTreeNodes(TreeNode *u) {
    PrintNode(u);

    if(!IsLeaf(u)) {
        TreeNode *v = u->child;

        while(v != NULL) {
            PreVisitTreeNodes(v);
            v = v->sibling;
        }
    }
}

void PostVisitTreeNodes(TreeNode *u) {
    if(!IsLeaf(u)) {
        TreeNode *v = u->child;

        while(v != NULL) {
            PostVisitTreeNodes(v);
            v = v->sibling;
        }
    }

    PrintNode(u);
}

void InVisitTreeNodes(TreeNode *u, int k) {
    int i = 0;

    if(IsLeaf(u)) {
        PrintNode(u);
    }
    else {
        TreeNode *v = u->child;

        while(i < k && v != NULL) {
            InVisitTreeNodes(v, k);
            v = v->sibling;
            i++;
        }

        PrintNode(u);

        while(v != NULL) {
            InVisitTreeNodes(v, k);
            v = v->sibling;
        }
    }
}

/*
 * PrintTree
 * --------------------
 * What it does:
 * prints all the nodes inside the tree
 * 
 * Requires:
 * t = a pointer to a tree
 */
void PrintTree(Tree *t) {
    printf("_____ TREE NODES _____\n");

    printf("PRE VISIT:\n");
    PreVisitTreeNodes(t->root);

    printf("POST VISIT:\n");
    PostVisitTreeNodes(t->root);

    printf("IN VISIT:\n");
    InVisitTreeNodes(t->root, 1);

    printf("\n\n");
}

void PrintNode(TreeNode *u) {
    for(int i = 0; i < GetLevel(u); i++) {
        printf("\t");
    }

    if(u->root == 1) {
        printf("%d[r]\n", u->value);
    }
    else {
        printf("%d[%d]\n", u->value, u->parent->value);
    }
}