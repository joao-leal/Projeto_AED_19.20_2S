#include "defs.h"




list *NewElement(Item ptr)
{
    list *El = (list *) malloc(sizeof(list));
    El->next = NULL;
    El->item = ptr;
    return(El);
}