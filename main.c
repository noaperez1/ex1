#include "RLEList.h"
#include "AsciiArtTool.h"
#include <stdio.h>
#include <assert.h>

#define FOUR 4
#define THREE 3
#define TWO 2
#define TAB ' '
#define AT '@'
#define INVERTED 'i'
#define ENCODED 'e'
#define READ "r"
#define WRITE "w"
#define ERROR -1



// error func- prints the error
void error(char* message, char* filename)
{
	printf("%s %s\n", message, filename ? filename : "");
}

//closing function
void closingFunc (FILE* fileTarget, FILE* fileSource , RLEList list)
{
    assert(fileTarget && fileSource && list );
    fclose(fileSource);
    fclose(fileTarget);
    RLEListDestroy(list);
}

//map function that inverets ' ' to @
char invert (char c)
{
    if(c==TAB)
    {
        return AT;
    }
    return c;
}


int main(int argc, char** argv) 
{ // add -1 return in case of fail
    if (argc != FOUR) 
    {
		error("error! main didnt get 3 arguments", NULL);
		return ERROR;
    }
    char mode = *argv[1];
    if( mode!= INVERTED && mode!= ENCODED )
    {
        error("error! wrong flag was entred", NULL);
        return ERROR;
    }
    FILE* fileSource = fopen( argv[TWO] , READ);
    if (!fileSource)
    {
        error("error! problem in opening source file", NULL);
        return ERROR;
    }
    FILE* fileTarget = fopen(argv[THREE] , WRITE);
    if (!fileTarget)
    {
        error("error! problem in opening target file", NULL);
        fclose(fileSource);
        return ERROR;
    }
    RLEList list = asciiArtRead(fileSource);
    if(!list)
    {
        error("error! problem in compressing picture to list", NULL);
        fclose(fileSource);
        fclose(fileTarget);
        return ERROR;
    } 
    if( mode == INVERTED )
    {
        //inverted option
        if(RLEListMap( list , invert) != RLE_LIST_SUCCESS)
        {
            error("error! the invertion of the picture didnt work", NULL);
            closingFunc(fileTarget , fileSource , list);
            return ERROR;
        }
        if(asciiArtPrint( list , fileTarget ) != RLE_LIST_SUCCESS)
        {
            error("error! the invertion of the picture didnt work", NULL);
            closingFunc(fileTarget , fileSource , list);
            return ERROR;
        }
        closingFunc(fileTarget , fileSource , list);
        return 0;
    }
    else
    {
        //encoded option
        assert( mode == ENCODED);
        if (asciiArtPrintEncoded(list , fileTarget) != RLE_LIST_SUCCESS)
        {
            error("error! the encoding of the picture didnt work", NULL);
            closingFunc(fileTarget , fileSource , list);
            return ERROR; 
        }
        closingFunc(fileTarget , fileSource , list);
        return 0;   
    }
}