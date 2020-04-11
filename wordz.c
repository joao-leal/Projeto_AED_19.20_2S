/***********************************************
*          Projeto WordZ 19/20 2S              *
*                                              *
*   Joao Leal-89486   &&   Inês Meira-93084    * 
***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"



int main(int argc, char const *argv[])
{   

    FILE *fp;
    FILE *fp_out;

    Graph *G = NULL;


    char *output = NULL;
    char *buf = NULL;
    char *dict = NULL;


   /*char*/ 


    /*N. Argumentos Minimo*/
    if(argc < 3)
    {
        fprintf(stderr, "ERROR: Missing Arguments.\n");
        exit(1);
    }

    /*abrir dicionario*/
    dict = (char*) malloc(strlen(argv[1]) * sizeof(char));
    strcpy(dict, argv[1]);
    if(dict == NULL){fprintf(stderr, "ERROR: File .dict"); exit(0);} 
    

    /*abrir grafo*/
    buf = strstr(argv[2], ".graph0");
    if(buf == NULL){fprintf(stderr, "ERROR: File .graph0"); exit(0);}

    fp = fopen(argv[2], "r");
    if(fp == NULL){fprintf(stderr, "ERRO: Non-Existant File"); exit(0);}

    /*Output File Name*/
    output = OutputFile(&argc, argv[2]);
    fp_out = fopen (output, "a");

    /*Le cabecalho ficheiro entrada*/
    while(!feof(fp))
    {
        header *hd = (header *) calloc(1, sizeof(header));
        int *path = NULL;
        int len = 0;
        char *str_output = NULL;

        BuildHeader(fp, hd);
        G = GRAPHinit(hd->v);
        path = GetPath(fp, path, hd->k);
        BuildGraph(fp, G);

        switch (hd->o)
        {
        case  'A':
            fprintf(fp_out, "%d %d %c %d %d\n\n", hd->v, hd->a, hd->o, hd->k, ModeA(G, hd->k, path));
            break;
        
        case 'B':
            fprintf(fp_out, "%d %d %c %d %d\n\n", hd->v, hd->a, hd->o, hd->k, ModeB(G, hd->k, path));
            break;
        
        case 'C':
            if(Validation(G, hd->k, path, &len))
            {
                str_output = (char*) calloc((len + 1), sizeof(char));

                fprintf(fp_out, "%d %d %c %d %d %s\n\n", hd->v, hd->a, hd->o, hd->k, ModeC(G, hd->k, path, str_output), str_output);

            }
            else
            {
                fprintf(fp_out, "%d %d %c %d %d\n\n", hd->v, hd->a, hd->o, hd->k, -1);
            }
            break;

        case 'D':
            if(ModeA(G, hd->k, path) == -1)
            {
                fprintf(fp_out, "%d %d %c %d %d\n\n", hd->v, hd->a, hd->o, hd->k, -1);
                break;
            }
            if(Validation(G, hd->k, path, &len))
            {
                str_output = (char*) calloc((len + 1), sizeof(char));

                fprintf(fp_out, "%d %d %c %d %d\n\n", hd->v, hd->a, hd->o, hd->k, ModeD(G, hd->k, path, str_output, dict));
            }
            else
            {
                fprintf(fp_out, "%d %d %c %d %d\n\n", hd->v, hd->a, hd->o, hd->k, -1);
            }
            break;

        default:
            fprintf(fp_out, "%d %d %c %d -1\n", hd->v, hd->a, hd->o, hd->k);
            break;
        }

        free(hd);
        free(path);
        free(str_output);
    }
    
    free(output);
    fclose(fp);
    fclose(fp_out);

    exit(0);

    return 0;
}








char* OutputFile(int *argc, char const *input)
{
    char *nome = NULL;
    int len = 0;

    nome = (char*) calloc(((strlen(input))+2), sizeof(char));
    len = strlen(input)-strlen(".graph0");

    strncpy(nome, input, len+1);
    nome[len] = '\0';
    strcat(nome, ".wordz0");

    return nome;
}

void BuildHeader(FILE *fp, header *hd)
{
    if(fscanf(fp, "%d %d %c %d\n" , &hd->v, &hd->a, &hd->o, &hd->k) < 4) 
    {
        fprintf(stderr, "ERROR: Invalid Header for Graph\n");
        exit(-1);
    }
}

int* GetPath(FILE * fp, int *path, int k)
{
    int i = 0;
    
    path = (int*) calloc((k+1), sizeof(int));

    while(i < k && fscanf(fp, "%d ", &path[i++]) == 1);
    path[i] = -1;

    return path;

   /* char * buf = (char*) malloc( sizeof(char));

    path = (char*) calloc((max + 1), sizeof(char));

    for(i = 0; i < max; i++)
    {  
        if(fscanf(fp, "%s ", buf) != 1)
        {
            fprintf(stderr, "ERROR: Invalid Path");
            exit(-1);
        }
        strcat(path, buf);
    }*/
    

}

void BuildGraph(FILE *fp, Graph * G)
{
    int v, t, count = 0;
    char *buf = (char*) malloc(5 * sizeof(char));
    
    while (count < G->V && fscanf(fp, "%d %s %d\n", &v, buf, &t) == 3)
    {
        GRAPHinsertValue(G, v, t);
        GRAPHinsertString(G, buf, v);
        count++;
    }
    
    while(fscanf(fp, "%d %d\n", &v, &t) == 2)
    {
        Edge *e = NULL;
        e = (Edge*) malloc(sizeof(struct edge));
        e->v = v; e->w = t;
        GRAPHinsertE(G, e);
    }
    
}

int ModeA(Graph *G, int k, int *path)
{
    int i, j;


   /*Repeated Vertices?*/
   for(i = 0; i < k; i++)
   {
       for(j = i+1; j < k; j++)
        {
            if(path[i]==path[j])  return -1;
        }
        if(path[i] > G->V) return -1; /*Is part of graph?*/
   }

   /*Are al the vertices connected?*/
   for(i = 0; i+1 < k; i++)
   {
       if (path[i] < path[i+1])
       {
           if (G->adj[path[i+1]-1][path[i]-1] != 1) return -1;
       }
        else if(G->adj[path[i]-1][path[i+1]-1] != 1) return -1;
    }

    return 1;
   
}

int ModeB(Graph *G, int k, int *path)
{
    int sum = 0, i;

    for ( i = 0; i < k; i++)
    {
        if(path[i] > G->V) return -1;/*Is part of the graph?*/ 
        sum+=G->adj[path[i] - 1][path[i] - 1];
    }
    
    return sum;
}

int Validation(Graph *G, int k, int *path, int *len)
{
    int i;

    for(i = 0; i < k; i++)
    {

        if(path[i] > G->V) return 0; /*Is part of graph?*/

        /*Is there any vertice with a sufix but the last?*/
        if(i > 0 && i < k - 1 && G->string[path[i] - 1][0] == '-') return 0;

        /*Is there any vertice with a prefix but the first?*/
        if(G->string[path[i] - 1][strlen(G->string[path[i] - 1])] == '-') return 0;

        if(i == k-1 && G->string[path[i] - 1][0] == '-')
        {
           sscanf(G->string[path[i] - 1], "-%s", G->string[path[i] - 1]);
        }

        if(i == 0 && G->string[path[i] - 1][strlen(G->string[path[i] - 1])-1] == '-')
        {
           sscanf(G->string[path[i] - 1], "%[^-]", G->string[path[i] - 1]);
        }
        len += strlen(G->string[path[i] - 1]);
    }

  return 1;
}

int ModeC(Graph *G, int k, int *path, char *str)
{
    int i;

    for(i = 0; i < k; i++)
    {

        sscanf(G->string[path[i] - 1], "%[^/]", G->string[path[i] - 1]);
       
        strcat(str, G->string[path[i] - 1]);
        puts(G->string[path[i] - 1]);

    }

    return 1;
}

int ModeD(Graph *G, int k, int *path, char *str, char *dict)
{   
    int i, j;
    int *alt;


    alt = (int*) calloc(k , sizeof(int));

    for(i = 0; i < k; i++)
    {
        for(j = 0; j < strlen(G->string[path[i] - 1]); j++)
        {
            if(G->string[path[i] - 1][j] == '/') alt[path[i-1]]++;
        }
    }

    return Alternatives(G, 0, path, str, dict, alt);

    if(SearchDict(dict, str)) return 1;

    return 0;
}

int SearchDict(char * name, char * str)
{
    char *buf;
    FILE *dict ;
    
    dict = fopen(name, "r");
    if(dict == NULL){fprintf(stderr, "ERRO: Non-Existant Dictionary File"); exit(0);}

    while(!feof(dict))
    {
        buf =(char*) malloc((strlen(str)+1) * sizeof(char));
        
        if(fscanf(dict, "%s ", buf) < 1) return 0;

        if(!strcmp(str, buf)){free(buf); return 1;} 
        free(buf);
    }

    return 0;
}

int Alternatives(Graph *G, int k, int *path, char *str, char *dict, int *alt)
{   
    int i;
    char *cpy = NULL, *str_;

    if(path[k] == -1) /*Last vertice, serach for the word in the dict*/
    {
        if(cpy != NULL) free(cpy);
        if(SearchDict(dict, str)) return 1;
        return 0;
    }
    else
    {
        cpy = (char*) malloc(strlen(G->string[path[k] - 1]) * sizeof(char));
    
        str_ = (char*) malloc(strlen(G->string[path[k] - 1]) * sizeof(char));
        strcpy(cpy, G->string[path[k] - 1]);

    }
    
    

    

    for(i = 0; i <= alt[path[k-1]]; i++) /*Total of alternatives in this vertice*/
    {
        char *buf = (char*) malloc(strlen(G->string[path[k] - 1]) * sizeof(char));

        strcpy(str_, str);

        /*Append to the string which will contain the final word the alternative and remove that alternative from this iteration*/
        sscanf(cpy, "%[^/]", buf);
        strcat(str_, buf);
        sscanf(G->string[path[k] - 1], "%*[^/]/%s", cpy);
        free(buf);

        /*Next vertice*/
        if(Alternatives(G, k+1, path, str_, dict, alt)) return 1;
    
    }

    free(cpy);


    return 0;
}
