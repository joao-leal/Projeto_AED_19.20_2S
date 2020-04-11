#ifndef _GRAPH_H_
#define _GRAPH_H_


typedef struct edge
{
    int v;
    int w;
} Edge;

typedef struct graph
{
    int V;
    int E;
    int **adj;
    char **string; 
} Graph;

Edge *EDGE(int, int);

Graph *GRAPHinit(int); 

void GRAPHinsertE(Graph *, Edge *);
void GRAPHinsertValue(Graph *, int, int);
void GRAPHinsertString(Graph *, char*, int);
void GRAPHremoveE(Graph *, Edge *);
int GRAPHedges(Edge **, Graph *);
Graph *GRAPHcopy(Graph *);
void GRAPHdestroy(Graph *);



#endif