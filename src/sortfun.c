#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "sortfun.h"

void printMenu()
{
    printf("usage: sort [option]\n");
    printf("option:\n");
    printf("       -t [type]    type of sort\n");
    printf("          bubble    bubble sort\n");
    printf("          select    simple select sort\n");
    printf("          insert    straignt insert sort\n");
    printf("          shell     shell sort\n");
    printf("          heap      heap sort\n");
    printf("          merge     merging sort\n");
}

void printSortedArray(int * nums,int len)
{
    int i = 0;
    printf("array[%d] = {",len);
    for(i; i < len-1; ++i)
    {
        printf("%d, ",nums[i]);
    }
    printf("%d}\n",nums[len-1]);
}

void printArrayBeforeSorted(int * nums, int len)
{
    printf("before sorted:\n");
    printSortedArray(nums,len);
}

void printArrayAfterSorted(int * nums, int len)
{
    printf("after soterd:\n");
    printSortedArray(nums,len);
}

void swap(int * nums, int a, int b)
{
    nums[a] = nums[a] ^ nums[b];
    nums[b] = nums[a] ^ nums[b];
    nums[a] = nums[a] ^ nums[b];
}

/* 思路：
 * 对正常的冒泡排序做了优化,用flag标记是否已经排好序
 * 对于排好序的数组直接跳过，不需要继续排序了
 * 时间复杂度:O(n^2)
 */
void bubbleSort(int * nums, int len)
{
    int i,j;
    int flag = TRUE;

    for(i = 0; i < len && flag; ++i)
    {
        flag = FALSE;
        for(j = len-2; j >= i; --j )
        {
            if(nums[j] > nums[j+1])
            {
                swap(nums,j,j+1);
                flag = TRUE;
            }
        }
    }
}

/* 思路：
 * 每次选择剩下的数组中的最小值的位置
 * 然后与当前的位置交换
 * 时间复杂度:O(n^2)
 */
void selectSort(int * nums, int len)
{
    int i, j,min;

    for(i = 0; i < len - 1; ++i)
    {
        min = i;
        for(j = i+1; j < len; ++j)
        {
            if(nums[min] > nums[j])
            {
                min = j;
            }
        }
        if(min != i)
        {
            swap(nums,i,min);
        }
    }
}

/* 思路：
 * 从数组的第二个元素开始，依次往有序的数组中添加元素
 * i用来表示当前的元素，如果比他前一个元素大的话则保持不变，
 * 否则用j表示前一个元素，依次往前遍历，直到找到比他小的元素为止
 * 期间所有的元素往后移。
 * 最后把这个元素插进去
 * 时间复杂度:O(n^2)
 */
void insertSort(int * nums, int len)
{
    int i,j,key;
    for(i = 1; i < len; ++i)
    {
        if(nums[i] < nums[i-1])
        {
            key = nums[i];
            for(j = i -1; nums[j] > key && j >= 0; --j) //所有比nums[i]大的元素都往后移,注意控制j的大小
            {
                nums[j+1] = nums[j];
            }
            nums[j+1] = key; //插入这个元素
        }
    }
}

/* 备注：
 * 希尔排序是在插入排序的基础上进行优化，排序的总体思路和插入排序一样
 * 直接插入排序的优势在于：1、对基本有序的数组排序时，只需要将少量的数进行插入操作就可完成整个记录的排序。2、记录数比较少
 * 但是现实中基本有序的数组属于特殊情况，而记录数较少同样如此，两个条件比较苛刻
 * 希尔排序是对此进行了优化，创造这样的条件：
 * 将原本就有大量记录数的数组进行分组，分割成若干子序列，此时子序列待排序的记录数就相对减小，
 * 然后对这些子序列分别进行插入排序，当整个序列基本有序时，在对全体记录进行一次直接插入排序
 * 时间复杂度:O(n^3/2)
 */
void shellSort(int * nums, int len)
{
    int i,j,key;
    int inc = len;

    while(inc > 1)
    {
        inc = inc/3 +1;
        for(i = inc; i < len; ++i)
        {
            if(nums[i]<nums[i-inc])
            {
                key = nums[i];
                for(j=i-inc; j >= 0 && nums[j] > key; j-=inc)
                {
                    nums[j+inc] = nums[j];
                }
                nums[j+inc] = key;
            }
        }
    }
}

/*
 * 找出以某个子节点为根节点的子树中的最大值
 * 然后与根节点交换
 * pos:根节点位置
 * len:数的大小
 */
void heapBigTop(int * nums, int pos, int len)
{
    int i,tmp;

    tmp = nums[pos];  //记录某个子节点的值，方便后续交换
    for(i = pos*2; i <= len; i*=2)  //完全二叉树的特性：节点i的孩子分别为2i,2i+1
    {
        if(i < len && nums[i] < nums[i+1]) //找出孩子节点中的最大值
        {
            ++i;
        }

        if(tmp > nums[i])  //最大值tmp交换
        {
            break;
        }
        else
        {
            nums[pos] = nums[i];
            pos = i;
        }
    }
    nums[pos] = tmp;  //完成交换
}

/* 原理：
 * 将数组构造成大顶堆，此时数组中的最大值就是堆顶的根节点，将他移走
 * (其实就是将其与堆数组末尾元素交换，此时末尾元素就是最大值)
 * 然后将剩下的n-1个数重新构造大顶堆，这样就得到n-1个元素中的次小值
 * 如此反复循环就能得到一个有序的数组。
 *
 * 核心代码就是heapBigTop部分代码
 * 所谓的构建大顶堆就是从下往上，从右到左，
 * 将每个节点当作根节点，将其和子树调成大顶堆
 * 时间复杂度:O(nlogn)
 */
void heapSort(int * nums, int len)
{
    int i;

    //因为堆排序是利用完全二叉树的特性，所以根节点必须为1，所以把原先数组整体后移
    int mem[len+1];
    memcpy(&mem[1],nums,len*sizeof(int));

    //构建大顶堆，使得所有子节点都比其孩子节点大
    //使得根节点为所有节点中最大值，但是除根节点外，其他节点不一定有序
    //i为什么从len/2开始？因为len/2是最后一个非叶节点，他上面所有节点都有子节点
    for(i = len/2; i > 0; --i)
    {
        heapBigTop(mem,i,len);
    }

    //把所有的根节点交换到末尾，树长度减1，然后继续找到最大的值
    for(i = len; i > 1; --i)
    {
        swap(mem,1,i);  //交换根节点与最后一个节点
        heapBigTop(mem,1,i-1);  //剩下的节点继续
    }
    memcpy(nums,&mem[1],sizeof(int)*len);
}

void mergeSort(int * nums, int len)
{

}
