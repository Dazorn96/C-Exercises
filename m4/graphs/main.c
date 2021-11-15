#include "../graphs.h"
#include <stdio.h>

void main()
{
    Graph *g = CreateGraph(4, 1);

    AddNode(g, 0, 0);
    AddNode(g, 1, 3);
    AddNode(g, 2, 2);
    AddNode(g, 3, 5);

    AddEdge(g, 0, 1);
    AddEdge(g, 0, 2);
    AddEdge(g, 2, 1);
    AddEdge(g, 1, 3);
    AddEdge(g, 2, 3);

    PrintGraph(g);

    printf("\n");
}