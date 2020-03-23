#ifndef _DEFS_H_
#define _DEFS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Item;

typedef struct _list
{
    Item item;
    struct _list *next;
} list;


/*        List Interface        */
list *NewElement(Item);
void FreeElement(list *);
void InsertNext(list *, list *);
void DeleteNext(list *);
list Next(list *);
Item GetElement(list *);
/********************************/


/*            Wordz             */
char* OutputName(char* p);
/********************************/


#endif