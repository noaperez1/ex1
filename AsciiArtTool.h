#ifndef HW1_ASCII_ART_TOOL_H
#define HW1_ASCII_ART_TOOL_H

#include "RLEList.h"
#include <stdio.h>
#include <stdbool.h>

/**
* Ascii Art Tool
*
* The following functions are available:
*   asciiArtRead	        - Reads a file and compresses it in RLE list.
*   asciiArtPrint		    - Writes a picture that represented in RLE list into file.
*   asciiArtPrintEncoded    - Writes the picture in compressed way.
*
*/

/** 
* Typedef for defining the RLE list.
* Complete the implementation of struct RLEList_t defined in RLEList.c
*/
typedef struct RLEList_t *RLEList;

/** Enum used for returning error codes from RLE list functions */
typedef enum {
    RLE_LIST_SUCCESS,
    RLE_LIST_OUT_OF_MEMORY,
    RLE_LIST_NULL_ARGUMENT,
    RLE_LIST_INDEX_OUT_OF_BOUNDS,
    RLE_LIST_ERROR
} RLEListResult;


/** 
 * Type of function for mapping characters.
 * This function should accept a character in the list and return the mapped character
 */
typedef char (*MapFunction)(char);

/**
*asciiArtRead: Reads a file and compresses it in RLE list.
*
* @param in_stream - a pointer to the file with the Ascii Art picture
* @return
* 	NULL if a NULL was sent as one of the parameters
* 	RLEList list with compressed RLEList 
*/
RLEList asciiArtRead(FILE* in_stream);

/**
*asciiArtPrint: Writes a picture that represented in RLE list into file.
*
* @param list - RLEList list with compressed picture data
* @param out_stream - a pointer to the file the function writes the Ascii Art picture to
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
* 	RLE_LIST_SUCCESS in case of success 
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);


/**
*asciiArtPrintEncoded: Writes the picture in compressed way.
*
* @param list - RLEList list with compressed picture data
* @param out_stream - a pointer to the file the function writes the compressed list to
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
* 	RLE_LIST_SUCCESS in case of success 
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);




#endif // HW1_ASCII_ART_TOOL_H