#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef struct edge Edge;
Edge *EDGE(int, int);

typedef struct graph
{
    int V;
    int E;
    int **adj;
    char **string; 
} Graph;

Graph *GRAPHinit(int); 

void GRAPHinsertE(Graph *, Edge *);
void GRAPHinsertValue(Graph *, int, int);
void GRAPHinsertString(Graph *, char*, int);
void GRAPHremoveE(Graph *, Edge *);
int GRAPHedges(Edge **, Graph *);
Graph *GRAPHcopy(Graph *);
void GRAPHdestroy(Graph *);



#endif