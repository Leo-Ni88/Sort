#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "sortfun.h"

struct _sort_ my_sort[]={
    {"bubble",  DEFAULT_ARRAY_ON,   DEFAULT_ARRAY,  DEFAULT_ARRAY_LEN,  bubbleSort},
    {"select",  DEFAULT_ARRAY_ON,   DEFAULT_ARRAY,  DEFAULT_ARRAY_LEN,  selectSort},
    {"insert",  DEFAULT_ARRAY_ON,   DEFAULT_ARRAY,  DEFAULT_ARRAY_LEN,  insertSort},
    {"shell",   DEFAULT_ARRAY_ON,   DEFAULT_ARRAY,  DEFAULT_ARRAY_LEN,  shellSort},
    {"heap",    DEFAULT_ARRAY_ON,   DEFAULT_ARRAY,  DEFAULT_ARRAY_LEN,  heapSort},
    {"merge",   DEFAULT_ARRAY_ON,   DEFAULT_ARRAY,  DEFAULT_ARRAY_LEN,  mergeSort}
};
#define MY_SORT_LEN     sizeof(my_sort)/sizeof(struct _sort_)

void main(int argc, char * argv[])
{
    int nums[] = {9,1,5,8,3,7,4,6,2};
    int len = sizeof(nums)/sizeof(int);
    int ch,i;

    if(1 == argc || 2 == argc)
    {
        printMenu();
        return;
    }
    
    while((ch = getopt(argc,argv,"t:i")) != -1)
    {
        switch(ch)
        {
            case 't':
                for(i = 0; i < MY_SORT_LEN; ++i)
                {
                    if(strcmp(optarg,my_sort[i].name) == 0)
                    {
                        if(my_sort[i].df_array == DEFAULT_ARRAY_ON)
                        {
                            printArrayBeforeSorted(my_sort[i].nums,len);

                            my_sort[i].cb(my_sort[i].nums,len);

                            printArrayAfterSorted(my_sort[i].nums,len);
                        }
                        else
                        {
                            printArrayBeforeSorted(nums,len);

                            my_sort[i].cb(nums,len);

                            printArrayAfterSorted(nums,len);
                        }
                    }
                }
                break;
            case 'i':
                printf("Please input numbers...\n");
                break;
            default:
                printMenu();
        }
    }
}
