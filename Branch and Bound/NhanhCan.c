#include <stdio.h>
#define size 100

typedef struct{
	float length;
	int start, end;
	int used;
}Edge;

void readFile(Edge a[][size], int *n){
	FILE *f = fopen("TSP.txt", "r");
	if (f!=NULL){
		int k;
		fscanf(f, "%d", &k);
		for (int i=0;i<k;i++){
			for (int j=0;j<k;j++){
				fscanf(f, "%f", &a[i][j].length);
				a[i][j].start = i;
				a[i][j].end = j;
				a[i][j].used = 0;
			}
		}
		*n = k;
	}
	else printf("Loi mo file!.");
}

void printArr(Edge a[][size], int n){
	for (int i=0;i<n;i++){
		for (int j=i+1;j<n;j++){
			printf("%d %d %.2f\n", a[i][j].start+1, a[i][j].end+1, a[i][j].length);		
		}
	}
}

int cycle(Edge x[], int k, int next){
	int has_cycle = 0, i=0;
	while(i<k && !has_cycle){
		if (x[i].start == next) has_cycle = 1;
		else i++;
	}
	return has_cycle;
}

float min_edge(Edge a[][size], int n){
	float Cmin = 3.40282e+38;
	int i,j;
	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
			if(i!=j && !a[i][j].used && a[i][j].length < Cmin) Cmin = a[i][j].length;
		}
	}
	return Cmin;
}

float under_limit(Edge a[][size], float TGT, int n, int i){
	return TGT + (n-i)*min_edge(a, n);
}

void update_bestPossible_solve(Edge a[][size], int n, float TGT, float *GiaNNTT, Edge x[], Edge PA[]){
	int i;
	x[n-1] = a[x[n-2].end][x[0].start];
	TGT = TGT + x[n-1].length;
	if (*GiaNNTT>TGT){
		*GiaNNTT = TGT;
		for (i=0;i<n;i++){
			PA[i] = x[i];
		} 
	}
}

void Nhanh_Can(Edge a[][size], int n, int i, int start, float *TGT, float *CD, float *GiaNNTT, Edge x[], Edge PA[]){	
	int j;
	for (j=0;j<n;j++){
		if (start!=j && !a[start][j].used && !cycle(x, i, j)){
			*TGT = *TGT + a[start][j].length;
			*CD = under_limit(a, *TGT, n, i+1);
			if (*CD < *GiaNNTT){
				x[i] = a[start][j];
				a[start][j].used = a[j][start].used = 1;
				if (i==n-2) update_bestPossible_solve(a, n, *TGT, GiaNNTT, x, PA); // if 3
				else Nhanh_Can(a, n, i+1, j, TGT, CD, GiaNNTT, x, PA);
			} // if 2
			*TGT = *TGT - a[start][j].length;
			a[start][j].used = a[j][start].used = 0;
		}// if 1
	}
}


int main(){
	Edge a[100][100];
	int n, i=0, start;
	float TGT = 0, CD = 0, GiaNNTT = 999999;
	readFile(a, &n);
//	printArr(a, n);
	Edge x[n], PA[n];
	printf("Nhap noi muon bat dau: ");
	scanf("%d", &start);
	Nhanh_Can(a, n, i, start, &TGT, &CD, &GiaNNTT, x, PA);
	for (int j=0;j<n-2;j++){
		printf("%d,%d ->  ", PA[j].start, PA[j].end);
	}
	printf("%d,%d", PA[n-2].start, PA[n-2].end);
	printf("\n%.3f", GiaNNTT);
	return 0;
}
