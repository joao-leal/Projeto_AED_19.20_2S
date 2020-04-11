#ifndef _DEFS_H_
#define _DEFS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"


typedef void *Item;


typedef struct _list
{
    Item item;
    struct _list *next;
} list;

typedef struct _header
{
    int v;
    int a;
    char o;
    int k;
} header;



/*        List Interface        */
list *NewElement(Item);
void FreeElement(list *);
void InsertNext(list *, list *);
void DeleteNext(list *);
list Next(list *);
Item GetElement(list *);
/********************************/


/*            Wordz             */
char* OutputFile( int *, char const *);
void BuildHeader(FILE *, header *);
int* GetPath(FILE *, /*char*/ int *, int);
void BuildGraph(FILE *, Graph *);

int ModeA(Graph *, int, int *);
int ModeB(Graph *, int, int *);
int Validation(Graph *, int, int *, int *);
int ModeC(Graph *, int, int *, char *);
int ModeD(Graph *, int, int *, char *, char *);
int SearchDict(char *, char *);
int Alternatives(Graph *, int , int *, char *, char *, int *);


/********************************/


#endif