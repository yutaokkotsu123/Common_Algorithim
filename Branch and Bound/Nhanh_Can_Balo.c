#include <stdio.h>

typedef struct{
	int key;
	float otherfield;
}recordtype;

void Swap(recordtype *a, recordtype *b){
	recordtype t = *a;
	*a = *b;
	*b = t; 
}

void SelectionSort(recordtype ds[], int n){
	int low_key, low_index;
	for (int i=0;i<n;i++){
		low_key = ds[i].key;
		low_index = i;
		for (int j=i+1;j<n;j++){
			if (ds[j].key<low_key){
				low_index = j;
				low_key = ds[j].key;
			}
		}
		Swap(&ds[i], &ds[low_index]);
	}
}

void create_root(float w, float *TLConLai, float *CT, float *GiaLNTT, float *TGT, float Don_Gia_Lon_Nhat){
	*TGT = 0.0;
	*TLConLai = w;
	*CT = *TLConLai*Don_Gia_Lon_Nhat;
	*GiaLNTT = 0.0;
}


