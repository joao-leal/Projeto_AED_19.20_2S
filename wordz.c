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
    FILE *fp1;

    Graph *G = NULL;

    header *hd = (header *) calloc(1, sizeof(header));

    char *output = NULL;
    char *buf = NULL ;
    char *path = NULL;


    /*N. Argumentos Minimo*/
    if(argc < 3)
    {
        fprintf(stderr, "ERROR: Missing Arguments.\n");
        exit(1);
    }

    /*abrir dicionario*/
    buf = strstr(argv[1], ".dict");
    if(buf == NULL){fprintf(stderr, "ERRO: Ficheiro .dict"); exit(0);} 

    /*abrir grafo*/
    buf = strstr(argv[2], ".graph0");
    if(buf == NULL){fprintf(stderr, "ERRO: Ficheiro .graph0"); exit(0);}

    fp = fopen(argv[2], "r");
    if(fp == NULL)  exit(0);

    /*Output File Name*/
    output = OutputFile(&argc, argv[2]);
    fp1 = fopen (output, "a");

    /*Le cabecalho ficheiro entrada*/
    while(!feof(fp))
    {
        BuildHeader(fp, hd);
        G = GRAPHinit(hd->v);
        GetPath(fp, path, hd->k);
        BuildGraph(fp, G);
    }
    
    free(output);
    free(hd);
    fclose(fp);
    fclose(fp1);


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
        fprintf(stderr, "ERROR: Invalid Header for Graph");
        return;
    }
}

void GetPath(FILE * fp, char *path, int max)
{
    int i;
    char * buf = (char*) malloc( sizeof(char));

    path = (char*) calloc((max + 1), sizeof(char));

    for(i = 0; i < max; i++)
    {  
        if(fscanf(fp, "%s ", buf) != 1)
        {
            fprintf(stderr, "ERROR: Invalid Path");
            exit(0);
        }
        strcat(path, buf);
    }

}

void BuildGraph(FILE *fp, Graph * G)
{
    int v, t;
    char *buf = (char*) malloc(5 * sizeof(char));
    
    while (fscanf(fp, "%d %s %d\n", &v, buf, &t) < 3)
    {
        GRAPHinsertString(G, buf, v);
        GRAPHinsertValue(G, v, t);
    }
    
}