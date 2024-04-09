#include <stdio.h>
#include "general_declare.h"

void PushDown(recordtype a[], int first, int last){
	int r = first;
	while(r<=(last-1)/2){
		if (last == 2*r+1){
			if (a[r].recordfield > a[last].recordfield){
				Swap(&a[r], &a[last]);
			}
			r=last;
		}
		else{
			if (a[r].recordfield > a[2*r+1].recordfield && a[2*r+1].recordfield <= a[2*r+2].recordfield){
				Swap(&a[r], &a[2*r+1]);
				r = 2*r+1;
			}
			else{
				if (a[r].recordfield > a[2*r+2].recordfield && a[2*r+1].recordfield > a[2*r+2].recordfield){
					Swap(&a[r], &a[2*r+2]);
					r = 2*r+2;
				}
				else r = last;
			}
		}
	}
}

void HeapSort(recordtype ds[], int n){
	for (int i=(n-2)/2;i>=0;i--){
		PushDown(ds, i, n-1);
	}
		
	for (int i=n-2;i>=2;i--){
		Swap(&ds[0], &ds[i]);
		PushDown(ds, 0, i-1);
	}
	Swap(&ds[0], &ds[1]);
}


int main()
{
    recordtype list[MAX_INDEX];
    int n;
    Read_Data(list, &n);
    printf("Input Array: ");
    Print_List(list, n);
    HeapSort(list, n+1);
    printf("Input array after use selection sort: ");
    Print_List(list, n);
    return 0;
}