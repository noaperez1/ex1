#include <stdio.h>
int counter=1;
char letter[2]="";



int main()
{
    int temp_num=0;
        do{
            counter/=10;
            temp_num++;
        }   while(counter!=0);
    printf("%d", temp_num); 
    
    
    return 0;
}