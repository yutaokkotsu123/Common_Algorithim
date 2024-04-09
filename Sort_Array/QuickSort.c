#include <stdio.h>
#include "general_declare.h"

int FindPivot(recordtype list[], int i, int j)
{
    int firstkey;
    int k = i + 1;
    firstkey = list[i].recordfield;
    while (k <= j && list[k].recordfield == firstkey)
        k++;
    if (k > j)
        return -1;
    if (list[k].recordfield > firstkey)
        return k;
    return i;
}

int Partition(recordtype list[], int i, int j, int pivot)
{
    int l, r;
    l = i;
    r = j;
    while (l <= r)
    {
        while (list[l].recordfield < pivot)
            l++;
        while (list[r].recordfield >= pivot)
            r--;
        if (l < r)
            Swap(&list[l], &list[r]);
    }
    return l;
}

void QuickSort(recordtype list[], int i, int j)
{
    int pivot, pivotIndex, k;
    pivotIndex = FindPivot(list, i, j);
    if (pivotIndex != -1)
    {
        pivot = list[pivotIndex].recordfield;
        k = Partition(list, i, j, pivot);
        QuickSort(list, i, k - 1);
        QuickSort(list, k, j);
    }
}

int main()
{
    recordtype list[MAX_INDEX];
    int n;
    Read_Data(list, &n);
    printf("Input Array: ");
    Print_List(list, n);
    QuickSort(list, 0, n-1);
    printf("Input array after use selection sort: ");
    Print_List(list, n);
    return 0;
}