#include <stdlib.h> //שגיאה - לשנות את הגרשיים
#include <string.h>
#include <assert.h>
#include <stdio.h>

char* stringDuplicator(char* s, int times)
{   //שגיאת קונבנציה
    assert(s);  //assert(!s);
    assert(times > 0);
    int LEN = strlen(s);
    char* out = malloc(LEN*times);  //malloc(LEN*times*sizeof(char))האם שגיאה? -

    assert(out);     //assert(out);
    for (int i=0; i<times; i++)    //for (int i=0; i<=times; i++)
    {
        out = out + LEN;
        strcpy(out,s);
    }
    out-=(times-1)*LEN; //חזרנו לפוינטר ההתחלתי
    return out;
}


int main()
{
    char *tali= "noa";
    //char* p=tali;

    char* n= stringDuplicator(tali,3);
    for (int i=0; i<12; i++)
    {
    printf("%c", *n);
    n++;
    }



    return 0;
}