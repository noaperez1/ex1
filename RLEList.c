#include "RLEList.h"
#include <stdlib.h>
typedef struct RLEList_t{
    char *s;
    struct RLEList *next;
}*RLEList_node;

//implement the functions here
RLEList RLEListCreate()
{
    RLEList_node new_node = malloc(sizeof(new_node));
    if(!new_node)
    {
        return NULL;
    }
    new_node->s = NULL;
	new_node->next = NULL;
	return new_node;
}