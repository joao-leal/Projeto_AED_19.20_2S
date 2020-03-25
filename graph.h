#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef struct edge Edge;
Edge *EDGE(int, int);

typedef struct graph Graph;

Graph *GRAPHinit(int); 

void GRAPHinsertE(Graph *, Edge *);
void GRAPHinsertString(Graph *, char*, int);
void GRAPHremoveE(Graph *, Edge *);
int GRAPHedges(Edge **, Graph *);
Graph *GRAPHcopy(Graph *);
void GRAPHdestroy(Graph *);



#endif