#include "RLEList.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define INITIALIZED_TIMES 1
#define TEN 10
#define THREE 3
#define TWO 2

typedef struct RLEList_t{
    char s;
    int times;
    struct RLEList_t *next;
}*RLEList;

static RLEList RLEList_new_node();
static RLEList last_node (RLEList head);
static void initialize(RLEList last, char value);

RLEList RLEListCreate();
void RLEListDestroy(RLEList list);
RLEListResult RLEListAppend(RLEList list, char value);
int RLEListSize(RLEList list);
RLEListResult RLEListRemove(RLEList list, int index);
char RLEListGet(RLEList list, int index, RLEListResult *result);
RLEListResult RLEListMap(RLEList list, MapFunction map_function);
char* RLEListExportToString(RLEList list, RLEListResult* result);


//----------definitions---------------------------------------------------------------------//
//s - the char 
//times - number of times that char appears
//next - pointer to next node 


int main()
{
    RLEList one= RLEListCreate();
    printf("%c", one->s);



    return 0;
}










//------------help_func---------------------------------------------------------------------//



/*this func creates new empty RLEList node
is used in RLEListCreate and RLEListAppend */
static RLEList RLEList_new_node()
{
    //supposed to be free in noas func
    RLEList new_node = malloc(sizeof(*new_node));   // add * in sizeof
    if(!new_node)
    {
        return NULL;
    }
    new_node->s = NULL;
    new_node->times=0;
	new_node->next = NULL;
	return new_node;
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


//--------func---------------------------------------------------------------------//

RLEList RLEListCreate()
{
    RLEList head= RLEList_new_node();
    if(!head)
    {
        return NULL;
    }
    head->next = RLEList_new_node() ;
    if(!(head->next))
    {
        return NULL;
    }
    return head;
}

void RLEListDestroy(RLEList list)
{
    if (list==NULL)    //(if list->next==NULL) ?
        {
        return;
        }
    else 
    {   
        RLEListDestroy(list->next);
        free(list);
    }
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
        last->times++ ;
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

int RLEListSize(RLEList list)
{
    if (list==NULL)
    {
        return -1;
    }
    else
    {
        RLEList temp = list->next;
        int counter=list->times;
    
        while (temp!=NULL)
        {
            counter+=temp->times;
            temp= temp->next;
        }
        return counter; 
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
    while (count < index)
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
        RLEList temp= runner_del->next;
        runner_del->next = (runner_del->next)->next;
        free(temp);
        return RLE_LIST_SUCCESS;
    }
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if (result!=NULL)
    {
        if (list==NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
            return '\0';
        }
        else if (RLEListSize(list)<index+1 || index<=0)
        {
            *result= RLE_LIST_INDEX_OUT_OF_BOUNDS;
            return '\0';
        }
    }
    else if (list==NULL || RLEListSize(list)<index+1 || index<=0)
    {
        return '\0';
    }
    
    int counter=list->times;
    RLEList temp = list;

    while (counter<index)
        {
            temp= temp->next;
            counter+=temp->times;  
        } 
    
    if (temp->s ==NULL)  
    {
       return '\0'; 
    }          
    else 
    {
        if (result!=NULL)
        {
            *result= RLE_LIST_SUCCESS;
            return temp->s;
        }
        else
        {
            return temp->s;
        }
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

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (list==NULL)
    {
        if (result==NULL)
        {
            return NULL;
        }
        else
        {
            *result= RLE_LIST_NULL_ARGUMENT;
            return NULL;
        }
    }
    
    int counter=0, count_nodes= 0, //counting nodes without the first
    temp_len_num=0, temp_times=0;
    RLEList temp= list->next;
    
    while(temp!=NULL)
    {
        //converting int to char
        count_nodes++;
        temp_times=temp->times;
        temp_len_num=0;
        do
        {
            temp_times/=TEN;        
            temp_len_num++;
        }   while(temp_times!=0);

        counter +=temp_len_num;
        temp=temp->next;
    }

    char* arr= (char*)malloc(counter+1+(THREE*count_nodes)*sizeof(char));   
    if(arr==NULL)
    {
        printf("error allocate memory");
        return NULL;
    }
    char* p_arr=arr;
    temp= list->next;
    for(int i=0; i<count_nodes;i++)
    {
        *p_arr= temp->s;
        p_arr++;
        sprintf(p_arr,"%d", temp->times);
        temp_len_num=0, temp_times=temp->times;
        do
        {
            temp_times/=TEN;
            temp_len_num++;
        }   while(temp_times!=0);
        p_arr+=temp_len_num;
        *p_arr='\n';
        p_arr+=TWO; 
    }
}