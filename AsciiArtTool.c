
#include "RLEList.h"
//#include "AsciiArtTool.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

//----------definitions---------------------------------------------------------------------//
#define CHUNK_SIZE 256


//------------help_func---------------------------------------------------------------------//


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
    in_stream = fopen("file.txt" , "r");
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
    fclose(in_stream);
    return list;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);
{
    
}