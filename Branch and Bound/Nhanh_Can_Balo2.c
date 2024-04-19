#include <stdio.h>

typedef struct
{
	char TenDoVat[25];
	int GT, TL, PA, SL;
	float DG;
} DoVat;

void Swap(DoVat *a, DoVat *b)
{
	DoVat t = *a;
	*a = *b;
	*b = t;
}

int min(int a, int b){return (a>b ? b : a);}

void SelectionSort(DoVat ds[], int n)
{
	int max_key, max_index;
	for (int i = 0; i < n; i++)
	{
		max_key = ds[i].DG;
		max_index = i;
		for (int j = i + 1; j < n; j++)
		{
			if (ds[j].GT > max_key)
			{
				max_index = j;
				max_key = ds[j].DG;
			}
		}
		Swap(&ds[i], &ds[max_index]);
	}
}

void create_root(float w, float *TLConLai, float *CT, float *GiaLNTT, float *TGT, float Don_Gia_Lon_Nhat)
{
	*TGT = 0.0;
	*TLConLai = w;
	*CT = *TLConLai * Don_Gia_Lon_Nhat;
	*GiaLNTT = 0.0;
}

void update_best_Possible(float TGT, float *GiaLNTT, int x[], DoVat dsdv[], int n)
{
	int i;
	if (*GiaLNTT < TGT)
	{
		*GiaLNTT = TGT;
		for (i = 0; i < n; i++)
		{
			dsdv[i].PA = x[i];
		}
	}
}

void readData(DoVat ds_vat[], int *n, int *W)
{
	FILE *f;
	f = fopen("data2.txt", "r");
	int i = 0;
	if (f != NULL)
	{
		fscanf(f, "%d", W);
		while (!feof(f))
		{
			fscanf(f, "%d%d%d%[^\n]", &ds_vat[i].TL, &ds_vat[i].GT, &ds_vat[i].SL , &ds_vat[i].TenDoVat);
			ds_vat[i].DG = (float)ds_vat[i].GT / ds_vat[i].TL;
			ds_vat[i].PA = 0;
			i++;
		}
	}
	else
		printf("Loi mo file.");
	*n = i;
}

void PrintDSDV(DoVat ds_vat[], int n)
{
	printf("Danh sach do vat:\n");
	for (int i = 0; i < n; i++)
	{
		printf(" %2d %2d %2d %2s %.2f | Phuong an la: %d\n", ds_vat[i].TL, ds_vat[i].GT, ds_vat[i].SL, ds_vat[i].TenDoVat, ds_vat[i].DG, ds_vat[i].PA);
	}
	printf("\n");
}

void Branch_and_Bound(int i, float *TGT, float *CT, float *TLConLai, float *GiaLNTT, int x[], DoVat dsdv[], int n)
{
	int j;
	int So_Do_Vat_Co_The_Chon = min( *TLConLai / dsdv[i].TL, dsdv[i].SL);

	for (j = So_Do_Vat_Co_The_Chon; j >= 0; j--)
	{
		*TGT = *TGT + j * dsdv[i].GT;
		*TLConLai = *TLConLai - j * dsdv[i].TL;

		if (*CT > *GiaLNTT)
		{
			x[i] = j;
			if (i == n - 1 || *TLConLai == 0)
			{
				update_best_Possible(*TGT, GiaLNTT, x, dsdv, n);
			}
			else
			{
				Branch_and_Bound(i + 1, TGT, CT, TLConLai, GiaLNTT, x, dsdv, n);
			}
		}

		x[i] = 0;
		*TGT = *TGT - j * dsdv[i].GT;
		*TLConLai = *TLConLai + j * dsdv[i].TL;
	}
}

int main()
{
	DoVat dsdv[20]; 
	int x[20];
	int n, W;
	float TLConLai, GiaLNTT, CT, TGT;
	readData(dsdv, &n, &W);
	for (int i=0;i<n;i++){
		x[i]=0;
	}
	PrintDSDV(dsdv, n);
	SelectionSort(dsdv, n);
	create_root(W, &TLConLai, &CT, &GiaLNTT, &TGT, dsdv[0].DG);
	Branch_and_Bound(0, &TGT, &CT, &TLConLai, &GiaLNTT, x, dsdv, n);
	PrintDSDV(dsdv, n);
	printf("Tong gia tri: %.3f", GiaLNTT);
	return 0;
}