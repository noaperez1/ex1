#include "RLEList.h"
#include <stdlib.h>
#include <assert.h>

#define INITIALIZED_TIMES 1

//s - the char 
//times - number of times that char appears
//next - pointer to next node 
typedef struct RLEList_t{
    char s;
    int times;
    struct RLEList_t *next;
}*RLEList;

//creates new RLEList node
// is used in RLEListCreate and RLEListAppend
static RLEList RLEList_new_node()
{
    //supposed to be free in noas func
    RLEList new_node = malloc(sizeof(new_node));
    if(!new_node)
    {
        return NULL;
    }
    new_node->s = NULL;
    new_node->times=0;
	new_node->next = NULL;
	return new_node;
}

RLEList RLEListCreate()
{
    RLEList head= RLEList_new_node();
    if(!head)
    {
        return NULL;
    }
    head->next = RLEList_new_node() ;
    if(!head->next)
    {
        return NULL;
    }
    return head;
}

//gets head of list and returns last node in it (if null returns null)
//returns null in case of allocation fail, returns RLEList node in case of success
//is used for RLEListAppend function
static RLEList last_node (RLEList head)
{
    if(!head)
    {
        return NULL;
    }
    RLEList ptr = head;
    while (ptr->next != NULL)
    {
        ptr=ptr->next;
    } 
    return ptr;
}

//gets node and value and initialize the value of c, and times to 1
//is used for RLEListAppend function
static void initialize(RLEList last, char value)
{
    assert( last && value );
    last->s = value;
    last->times = INITIALIZED_TIMES;
}

RLEListResult RLEListAppend(RLEList list, char value)
{
    RLEList last= last_node(list);
    if ( last==NULL || value==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if ( last->s == NULL )
    {
        initialize( last , value );
        return RLE_LIST_SUCCESS;
    }
    else if ( last->s == value)
    {
        last->times ++ ;
        return RLE_LIST_SUCCESS;
    }
    else
    {
        RLEList new_node = RLEList_new_node();
        if( !new_node )
        {
            return RLE_LIST_OUT_OF_MEMORY;
        }
        initialize( new_node , value );
        last->next = new_node;
        return RLE_LIST_SUCCESS;
    }
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if( !list || index==0 )
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    // noas function, supposed to work in final check
    if ( index > RLEListSize(list) )
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    int count = 0 ;
    int count_nodes= 0;
    RLEList runner = list ;
    assert(runner);
    while (count < runner->times)
    {
        count = count + runner->times ;
        runner = runner->next ; 
        count_nodes ++ ;
    }
    assert( runner && runner->times !=0 && runner->s );
    if ( runner->times > 1)
    {
        runner->times-- ;
        assert(runner->times!=0);
        return RLE_LIST_SUCCESS;
    }
    else
    {
        assert(runner->times == 1);
        RLEList runner_del = list ;
        assert(runner_del);
        for(int i=0 ; i<count_nodes ; i++)
        {
            runner_del = runner_del->next ;
        }
        assert( runner_del && runner_del->next);
        runner_del->next = (runner_del->next)->next;
        runner_del = runner_del->next;
        //free(runner_del);
        return RLE_LIST_SUCCESS;
    }
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if( !list || !map_function )
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    // list begins with extra node to prevent boundry restrictions
    RLEList previous = list ;
    list = list->next ;
    char c = NULL;
    while (list)
    {
        assert( list->times > 0 );
        for( int i=0 ; i< list->times ; i++)
        {
            c = map_function(list->s);
            if( c == list->s)
            {
                continue;
            }
            else
            {
                if( RLEListAppend( previous , c ) != RLE_LIST_SUCCESS )
                {
                    return RLE_LIST_ERROR;
                }
                if( previous->next != list )
                {
                    previous->next->next = list;
                    previous = previous->next;
                }
                list->times -- ;
            }
        }
        if ( list->times ==0 )
        {
            previous->next = list->next;
            free(list);
            RLEList list = previous->next ;
        }
        list = list->next ;  
    }
    return RLE_LIST_SUCCESS;  
}