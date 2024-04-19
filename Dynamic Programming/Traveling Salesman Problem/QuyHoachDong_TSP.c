#include <stdio.h>
#define size 100

typedef float bang[50][100];
int mark[10];
int min(int a, int b) { return (a > b ? b : a); }

typedef struct
{
	float length;
	int start, end;
	int used;
} Edge;

void readFile(Edge a[], int *n, int *d)
{
	FILE *f = fopen("TSP.txt", "r");
	if (f != NULL)
	{
		int k, l = 0;
		float temp;
		fscanf(f, "%d", &k);
		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j < k; j++)
			{
				if (j <= i)
				{
					fscanf(f, "%f", &temp);
				}
				else
				{
					fscanf(f, "%f", &a[l].length);
					a[l].start = i;
					a[l].end = j;
					a[l].used = 0;
					l++;
				}
			}
		}
		*n = l;
		*d = k;
	}
	else
		printf("Loi mo file!.");
}

void printArr(Edge a[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d %d %.2f\n", a[i].start, a[i].end, a[i].length);
	}
}

void PrintTable(bang F, bang X, int n)
{
	printf("Bang duoc tao:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%6.2f|%2.0f    ", F[i][j], X[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

float findLength(Edge a[], int n, int i, int j)
{
	for (int k = 0; k < n; k++)
	{
		if ((a[k].start == i && a[k].end == j) || (a[k].start == j && a[k].end == i)){

			return a[k].length;
		}
			
	}
	return 0;
}

void reset(bang F, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			F[i][j] = 0;
		}
	}
}

void Tao_Bang(Edge a[], int n, int d, int start, bang F, bang X)
{
	// Dien gia tri
	F[0][start] = 0;
	X[0][start] = -1;

	for (int i = 0; i < d; i++)
	{
		F[1][i] = findLength(a, n, start, i);
		X[1][i] = start;
	}

	// Tinh toan chu trinh
	for (int i=2;i<d-1;i++){
		for (int j=0;j<d;j++){

		}
	}
}

int main()
{
	Edge a[100];
	int n, d, start;
	bang F, X;
	readFile(a, &n, &d);
	for (int i = 0; i < n; i++)
		mark[i] = 0;
	printf("Nhap dinh muon bat dau (0,1,2,3,4,5): ");
	scanf("%d", &start);
	printf("Danh sach cac duong di: ");
	printArr(a, n);
	reset(F, d);
	reset(X, d);
	Tao_Bang(a, n, d, start, F, X);
	PrintTable(F, X, d);

	return 0;
}
