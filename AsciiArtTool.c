
#include "RLEList.h"
#include "AsciiArtTool.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

//----------definitions---------------------------------------------------------------------//
#define CHUNK_SIZE 256


//------------help_func---------------------------------------------------------------------//

typedef struct RLEList_t{
    char s;
    int times;
    struct RLEList_t *next;
}RLEList_t; 
//--------func---------------------------------------------------------------------//

RLEList asciiArtRead(FILE* in_stream)
{
    if(!in_stream)
    {
        printf("error! the func got null file pointer \n");
        return NULL;
    }
    RLEList list = RLEListCreate();
    if(!list)
    {
        printf("error in memory allocation for new list \n");
        return NULL;
    }
    if (!in_stream)
    {
        printf("error in opening file \n");
        return NULL;
    }
    char buffer[CHUNK_SIZE];
    while ( fgets( buffer, CHUNK_SIZE, in_stream) != NULL) 
    {
        int i=0;
        while(buffer[i]!='\0')
        {
            RLEListAppend( list , buffer[i]);
            i++;
        }
    }
    return list;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    if(!out_stream|| !list)
    {
        printf("error! the func got null file pointer \n");
        return RLE_LIST_NULL_ARGUMENT;
    }
    
    RLEList temp= list;
    int len= RLEListSize(list);
    char* arr =(char*) malloc(len+1);
    
    int j=0;
    while(j<len)
    {
        for(int i=0; i< temp->times; i++)
        {
            arr[j]=temp->s;
            j++;
        } 
        temp=temp->next;
    }
    fputs(arr, out_stream);
    free(arr);
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if(!out_stream|| !list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result;
    char* short_string= RLEListExportToString(list,result);
    
    if(result!=RLE_LIST_SUCCESS || !short_string )
    {
        free(short_string); 
        return RLE_LIST_ERROR;
    }
    
    else
    {
        fputs(short_string, out_stream);
        free(short_string);  
        return RLE_LIST_SUCCESS; 
    }
}