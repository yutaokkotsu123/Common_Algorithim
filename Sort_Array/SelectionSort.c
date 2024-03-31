#include <stdio.h>
#include "general_declare.h"

void SelectionSort(recordtype list[], int n)
{
    int min_value, min_index;
    for (int i = 0; i < n; i++)
    {
        min_index = i;
        min_value = list[i].recordfield;
        for (int j = i; j < n; j++)
        {
            if (list[j].recordfield < min_value){
                min_value = list[j].recordfield;
                min_index = j;
            }
        }
        Swap(&list[i], &list[min_index]);
    }
}

int main()
{
    recordtype list[MAX_INDEX];
    int n;
    Read_Data(list, &n);
    printf("Input Array: ");
    Print_List(list, n);
    SelectionSort(list, n);
    printf("Input array after use selection sort: ");
    Print_List(list, n);
    return 0;
}