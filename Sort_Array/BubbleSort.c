#include <stdio.h>
#include "general_declare.h"

void BubbleSort(recordtype list[], int n){
    for (int i=0;i<=n-2;i++){
        for (int j=n-1;j>=i+1;j--){
            if (list[j].recordfield < list[j-1].recordfield) Swap(&list[j], &list[j-1]);
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
    BubbleSort(list, n);
    printf("Input array after use selection sort: ");
    Print_List(list, n);
    return 0;
}