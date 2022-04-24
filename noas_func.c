#include "RLEList.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define INITIALIZED_TIMES 1


//----------definitions---------------------------------------------------------------------//
//s - the char 
//times - number of times that char appears
//next - pointer to next node 


//------------help_func---------------------------------------------------------------------//

typedef struct RLEList_t{
    char s;
    int times;
    struct RLEList_t *next;
}*RLEList;

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
    if (list==NULL)     //(if list->next==NULL) ?
        return;
    else {   
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

int RLEListSize(RLEList list)
{
    if (list==NULL)
        return 0;
    RLEList temp = list->next;
    int counter=1;
    
    while (temp!=NULL)
    {
        counter++;
        temp= temp->next;
    }

    return counter;
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

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if (list==NULL)
        return RLE_LIST_NULL_ARGUMENT;
    if (RLEListSize(list)<index+1)
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;

    int counter=0;
    RLEList temp = list;

    while (counter!=index)
        {
            temp= temp->next;
            counter++; 
        } 

    char letter= temp->s;
    if (letter==NULL)        
        return 0;
    else 
    {
        *result= letter;
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

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    int len= RLEListSize(list);
    char* arr= (char*)malloc(4*len*sizeof(char));
    char* p_arr=arr[0];

    int counter=0;
    char temp_letter=list->s;

    while(list!=NULL)
    {
        if (temp_letter==list->s)
        {
            counter++;
            list= list->next;
        }
        else if(temp_letter!='\0')  //איך לסמל שהערך ריק? המטרה לבדוק שהערך חוקי
        {
            *p_arr = temp_letter;
            p_arr++;
            sprintf(p_arr,"%d", counter);

           //find the num of chars that is used to symbolize the len 
            int temp_len_num=0;
            do{
                counter/=10;
                temp_len_num++;
            }   while(counter!=0);
            
            p_arr+=temp_len_num;
            *p_arr="/n";
            p_arr+=2;

            temp_letter= list->s;
            counter=1;
            list= list->next;
            

        }
    } 
    
}
