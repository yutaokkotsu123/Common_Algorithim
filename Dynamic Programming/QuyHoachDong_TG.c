#include <stdio.h>
#define size 20

void readData(int tg[][size], int *n){
	FILE *f;
	f =  fopen("tg.txt", "r");
	int i=0;
	if (f!=NULL){
		while (!feof(f)){
			for (int j = 0 ; j <= i; j++){
				fscanf(f, "%d", &tg[i][j]);
			}
			i++;
		}
	}
	else printf("Loi mo file");
	*n = i;
}

void PrintTG(int tg[][size], int n){
	for (int i=0; i<n;i++){
		for (int j=0;j<=i;j++){
			printf("%d ", tg[i][j]);
		}
		printf("\n");
	}
}

int CS_max(int F[][size], int i, int j){
	if (j==0) return (F[i-1][0]>F[i-1][1]) ? 0 : 1;
	if (j==i) return i-1;
	if (j==i-1) return (F[i-1][i-1]>F[i-1][i-2]) ? (i-1) : (i-2);
	
	if (F[i-1][j-1]>F[i-1][j] && F[i-1][j-1]>F[i-1][j+1]) return j-1;
	if (F[i-1][j]>F[i-1][j-1] && F[i-1][j]>F[i-1][j+1]) return j;
	if (F[i-1][j+1]>F[i-1][j] && F[i-1][j+1]>F[i-1][j-1]) return j+1;
}



int main(){
	int n;
	int tg[10][size];
	readData(tg, &n);
	PrintTG(tg, n);
	return 0;
}










