#include <stdio.h>
#include "general_declare.h"

void InsertionSort(recordtype list[], int n){
    for (int i=0;i<n;i++){
        int j=i;
        while(j>0 && list[j].recordfield < list[j-1].recordfield){
            Swap(&list[j], &list[j-1]);
            j--;
        }
    }
}

int main()
{
    recordtype list[MAX_INDEX];
    int n;
    Read_Data(list, &n);
    printf("Input Array: ");
    Print_List(list, n);
    InsertionSort(list, n);
    printf("Input array after use selection sort: ");
    Print_List(list, n);
    return 0;
}