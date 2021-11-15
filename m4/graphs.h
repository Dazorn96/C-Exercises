#include <stdlib.h>
#include <stdio.h>
#include "../m2/lists.h"
#include "../m2/queues.h"

List *spanningTreeList;

typedef struct _GraphNode {
    int value;
    int weight;
    struct _GraphNode **adjacents;
    int adjacentSize;
    short visited;
} GraphNode;

typedef struct _Graph {
    struct _GraphNode **nodes;
    int size;
    int length;
    short oriented;
    int edges;
} Graph;

Graph* CreateGraph(int n, short o);
GraphNode* GetNode(Graph *g, int u);
int GetEdge(Graph *g, int u, int v);
void AddNode(Graph *g, int v, int w);
void AddEdge(Graph *g, int u, int v);
void ReallocateAdjacents(Graph *g, int u, int v);
void DFS(Graph *g, GraphNode *u);
void BFS(Graph *g, GraphNode *u);
void PrintGraph(Graph *g);
void ClearVisitState(Graph *g);
int GetNodeIndexByValue(Graph *g, int v);

/*
 * CreateGraph
 * --------------------
 * What it does:
 * allocates space for a new graph
 * 
 * Requires:
 * n = an integer value representing the desired number of graph's nodes
 * o = a boolean value, 1 for oriented graph else 0
 * 
 * Returns:
 * an empty graph
 */
Graph* CreateGraph(int n, short o) {
    Graph *g = malloc(sizeof(Graph));

    g->size = n;
    g->oriented = o;
    g->length = 0;
    g->nodes = malloc(sizeof(GraphNode*) * g->size);

    return g;
}

GraphNode* GetNode(Graph *g, int u) {
    return g->nodes[u];
}

void AddNode(Graph *g, int v, int w) {
    if(g->length == g->size) {
        printf("GRAPH IS FULL!\n");
        return;
    }

    g->nodes[g->length] = malloc(sizeof(GraphNode));

    g->nodes[g->length]->value = v;
    g->nodes[g->length]->weight = w;
    g->nodes[g->length]->adjacents = malloc(sizeof(GraphNode*));
    g->nodes[g->length]->adjacentSize = 0;
    g->nodes[g->length]->visited = 0;

    g->length++;
}

void AddEdge(Graph *g, int u, int v) {
    if(u >= g->size) {
        printf("GRAPH HAS NO NODE AT POSITION %d!\n", u);
        return;
    }

    if(u == v) {
        printf("CAN NOT ADD EDGE BETWEEN SAME NODE!\n");
        return;
    }

    int max = g->size * (g->size - 1);

    if(g->oriented == 0) {
        max = max / 2;
    }

    if(g->edges == max) {
        printf("GRAPH HAS REACHED MAXIMUM EDGES COUNT!\n");
        return;
    }

    ReallocateAdjacents(g, u, v);

    if(g->oriented == 0) {
        ReallocateAdjacents(g, v, u);
    }
}

void ReallocateAdjacents(Graph *g, int u, int v) {
    GraphNode *n = g->nodes[u]->adjacents[0];
    int i = 1;

    while (n != NULL) {
        if(n == g->nodes[v]) {
            printf("EDGE ALREADY EXISTING!\n");
            return;
        }

        n = g->nodes[u]->adjacents[i];
        i++;
    }

    g->nodes[u]->adjacents = realloc(g->nodes[u]->adjacents, sizeof(GraphNode*) * i);
    g->nodes[u]->adjacents[i - 1] = g->nodes[v];
    g->nodes[u]->adjacentSize++;
}

void DFS(Graph *g, GraphNode *u) {
    u->visited = 1;
    printf("VISITED NODE %d\n\n", u->value);
    AddToList(spanningTreeList, u->value);

    for(int i = 0; i < u->adjacentSize; i++) {
        GraphNode *v = u->adjacents[i];

        printf("NAVIGATING FROM %d TO %d\n", u->value, v->value);

        if(v->visited == 0) {
            DFS(g, v);
        }
        else {
            printf("NODE %d ALREADY VISITED, SKIPPING IT\n", v->value);
        }
    }
}

void BFS(Graph *g, GraphNode *u) {
    Queue *q = CreateQueue(g->size);
    
    AddToQueue(q, u->value);
    PrintQueue(q);

    while (IsEmptyQueue(q) != 1) {
        int k = RemoveFromQueue(q);
        int j = GetNodeIndexByValue(g, k);

        g->nodes[j]->visited = 1;
        printf("VISITED NODE %d\n", g->nodes[j]->value);
        AddToList(spanningTreeList, g->nodes[j]->value);

        for(int i = 0; i < g->nodes[j]->adjacentSize; i++) {
            GraphNode *v = g->nodes[j]->adjacents[i];

            printf("NAVIGATING FROM %d TO %d\n", g->nodes[j]->value, v->value);

            if(v->visited == 0 && IsInQueue(q, v->value) == 0) {
                AddToQueue(q, v->value);
            }
            else {
                printf("NODE %d ALREADY VISITED, SKIPPING IT\n", v->value);
            }
        }
        
        PrintQueue(q);
    }
}

void PrintGraph(Graph *g) {
    printf("_____ GRAPH _____\n");

    for(int i = 0; i < g->length; i++) {
        printf("%d [%d]", g->nodes[i]->value, g->nodes[i]->weight);

        for(int j = 0; j < g->nodes[i]->adjacentSize; j++) {
            printf("\t=> %d [%d]", g->nodes[i]->adjacents[j]->value, g->nodes[i]->adjacents[j]->weight);
        }

        printf("\n");
    }

    ClearVisitState(g);
    printf("_____ DFS _____\n");

    DFS(g, g->nodes[0]);

    printf("\nSPANNING TREE:\n");
    PrintList(spanningTreeList);

    ClearVisitState(g);
    printf("_____ BFS _____\n");

    BFS(g, g->nodes[0]);

    printf("\nSPANNING TREE:\n");
    PrintList(spanningTreeList);

    printf("\n\n");
}

void ClearVisitState(Graph *g) {
    for(int i = 0; i < g->length; i++) {
        g->nodes[i]->visited = 0;
    }

    free(spanningTreeList);
    spanningTreeList = CreateList();
}

int GetNodeIndexByValue(Graph *g, int v) {
    for(int i = 0; i < g->size; i++) {
        if(g->nodes[i]->value == v) {
            return i;
        }
    }

    return -1;
}