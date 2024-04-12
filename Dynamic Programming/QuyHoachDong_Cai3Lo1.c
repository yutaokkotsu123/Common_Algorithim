#include <stdio.h>

typedef struct{
	char Ten[20];
	int TL, GT, PA;
}Do_Vat;

typedef int bang[50][100];

void readData(Do_Vat ds_vat[], int *n, int *W){
	FILE *f;
	f = fopen("data.txt", "r");
	int i = 0;
	if (f!=NULL){
		fscanf(f, "%d", W);
		while(!feof(f)){
			fscanf(f, "%d%d%[^\n]", &ds_vat[i].TL, &ds_vat[i].GT, &ds_vat[i].Ten);
			i++;
		}
	}
	else printf("Loi mo file.");
	*n = i;
}

void PrintDSDV(Do_Vat ds_vat[], int n){
	printf("Danh sach do vat:\n");
	for (int i = 0; i<n;i++){
		printf(" %d %d %s\n", ds_vat[i].TL, ds_vat[i].GT, ds_vat[i].Ten);
	}
	printf("\n");
}

void PrintTable(bang F, bang X, int n, int W){
	printf("Bang duoc tao:\n");
	for (int i=0;i<n;i++){
		for (int j=0;j<W;j++){
			printf("%4d|%2d ", F[i][j], X[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void PrintPA(Do_Vat ds_vat[], int n){
	printf("Phuong an duoc dua ra: \n");
	for (int i=0;i<n;i++){
		printf("%d %d %s -> %d\n", ds_vat[i].TL, ds_vat[i].GT, ds_vat[i].Ten, ds_vat[i].PA);
	}
}

void Tao_Bang(Do_Vat ds_vat[], int n, int W, bang F, bang X){
	int xk, yk, k, Fmax, Xmax, V;
	for (V=0; V<=W;V++){
		X[0][V] = V/ds_vat[0].TL;
		F[0][V] = X[0][V]*ds_vat[0].GT;
	}
	
	for (k=1;k<n;k++){
		for (V=0;V<=W;V++){
			Fmax = 0;
			yk = V/ds_vat[k].TL;
			for (xk=0;xk<=yk;xk++){
				if (F[k-1][V-xk*ds_vat[k].TL] + xk*ds_vat[k].GT > Fmax){
					Fmax = F[k-1][V-xk*ds_vat[k].TL] + xk*ds_vat[k].GT;
					Xmax = xk;
				}
			}
			F[k][V] = Fmax;
			X[k][V] = Xmax;
		}
	}
}


void Tra_Bang(Do_Vat ds_vat[], int n, int W, bang X){
	int k, V = W;
	for (k=n-1; k>=0; k--){
		ds_vat[k].PA = X[k][V];
		V = V - X[k][V]*ds_vat[k].TL;
	}
}

int main(){
	int n, W;
	Do_Vat ds[100];
	bang F, X;
	readData(ds, &n, &W);
	PrintDSDV(ds, n);
	Tao_Bang(ds, n, W, F, X);
	Tra_Bang(ds, n, W, X);
	PrintTable(F, X, n, W);
	PrintPA(ds, n);
	return 0;
}



