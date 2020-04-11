#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"


/*typedef struct node link;

struct node
{
    int v;
    link *next;
};*/






/*
link *New(int v, link *next)
{
    link *x = (link *) malloc(sizeof(struct node));
    x->v = v;
    x->next = next;
    return x;
}*/


Graph *GRAPHinit(int V) /*Matriz de Adjacencias*/
{
    int v, i;
    Graph *G = (Graph*) malloc(sizeof(struct graph));

    G->V = V; G->E = 0;

    G->adj = (int**) malloc(V * sizeof(int*));
    for(v = 0; v < V; v++)
    {
        G->adj[v] = (int*) malloc((v + 1) * sizeof(int)); /*Matriz simetrica logo apenas precisamos de alocar metade*/  
        for(i = 0; i < v+1; i++)
        {
            G->adj[v][i] = 0;
        } 
    }

    G->string = (char**) malloc((G->V) * sizeof(char*));
    for(v = 0; v < V; v++)
    {
        G->string[v] = NULL;
    }

    return G;
}

void GRAPHinsertE(Graph *G, Edge *e)
{
    int v, w;
    v = e->v -1;
    w = e->w -1;

    if(G->adj[v][w] == 0) G->E++;    
    if(v < w) G->adj[w][v] = 1;     /*se adj[i][j] = 1 entao i liga a j, em adj[i][i] -> valor do vertice*/
    else G->adj[v][w] = 1;
}

void GRAPHinsertValue(Graph *G, int v, int t)
{
    G->adj[v-1][v-1] = t;
}



void GRAPHinsertString(Graph *G, char* string, int v)
{
    G->string[v-1] = (char*) malloc((strlen(string)+1) * sizeof(char));
    strcpy(G->string[v-1], string);
}


