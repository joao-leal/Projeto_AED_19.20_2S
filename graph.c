#include <stdlib.h>
#include "graph.h"

struct graph
{
    int V;
    int W;
    int **adj;
};

struct edge
{
    int v;
    int w;
};

Graph *GRAPHinit(int V)
{
    Graph *G = (Graph*) malloc(sizeof(struct graph));
    G->V = V; G->E = 0;
    G->adj = MATRIXint(V, V, 0);
    
    return G;
}
