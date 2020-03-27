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
void GetPath(FILE *, char *, int);
void BuildGraph(FILE *, Graph *);
/********************************/


#endif