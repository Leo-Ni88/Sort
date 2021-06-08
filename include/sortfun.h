#ifndef __SORTFUN_H__
#define __SORTFUN_H__

#define bool    int
#define TRUE    1
#define FALSE   0

#define DEFAULT_ARRAY_ON    1 
#define DEFAULT_ARRAY_OFF   0 
#define DEFAULT_ARRAY       {9,1,5,8,3,7,4,6,2}
#define DEFAULT_ARRAY_LEN   9

typedef void (* func)(int * nums, int len);

typedef struct _sort_
{
    char name [8];
    char df_array;
    int nums[DEFAULT_ARRAY_LEN];
    int len;
    func cb;
}_sort;

void printMenu(void);
void printSortedArray(int * nums,int size);
void printArrayBeforeSorted(int * nums, int len);
void printArrayAfterSorted(int * nums, int len);
void swap(int * nums, int a, int b);
void bubbleSort(int * nums, int size);
void selectSort(int * nums, int len);
void insertSort(int * nums, int len);
void shellSort(int * nums, int len);
void heapBigTop(int * nums, int pos, int len);
void heapSort(int * nums, int len);
void mergeSort(int * nums, int len);
    

#endif //__SORTFUN_H__


