#include <stdio.h>

typedef struct
{
    char TenDoVat[30];
    int TL, GT, PA, SL;
    float DG;
} DoVat;

int min(int a, int b){return (a>b ? b : a);}

void Swap(DoVat *a, DoVat *b)
{
    DoVat temp = *a;
    *a = *b;
    *b = temp;
}

void readData(DoVat dsdv[], int *W, int *n)
{
    FILE *f;
    f = fopen("data3.txt", "r");
    int i = 0;
    if (f != NULL)
    {
        fscanf(f, "%d", W);
        while (!feof(f))
        {
            fscanf(f, "%d%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].TenDoVat);
            dsdv[i].PA = 0;
            dsdv[i].DG = (float)dsdv[i].GT / dsdv[i].TL;
            i++;
        }
    }
    *n = i;
}

void printData(DoVat dsdv[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d %d %s %.2f | Phuong an la: %d\n", dsdv[i].TL, dsdv[i].GT, dsdv[i].TenDoVat, dsdv[i].DG, dsdv[i].PA);
    }
    printf("\n");
}

int FindPivot(DoVat dsdv[], int i, int j)
{
    float firstkey;
    int k = i + 1;
    firstkey = dsdv[i].DG;
    while (k <= j && dsdv[k].DG == firstkey)
        k++;
    if (k > j){
        return -1;
    }
    if (dsdv[k].DG < firstkey){
        return k;
    }
       
    return i;
}

int Partition(DoVat dsdv[], int i, int j, float pivot)
{
    int l, r;
    l = i;
    r = j;
    while (l <= r)
    {
        while (dsdv[l].DG > pivot)
            l++;
        while (dsdv[r].DG <= pivot)
            r--;
        if (l < r)
            Swap(&dsdv[l], &dsdv[r]);
    }
    return l;
}

void QuickSort(DoVat dsdv[], int i, int j)
{
    float pivot;
    int k, pivotIndex;
    pivotIndex = FindPivot(dsdv, i, j);
    if (pivotIndex != -1)
    {
        pivot = dsdv[pivotIndex].DG;
        k = Partition(dsdv, i, j, pivot);
        QuickSort(dsdv, i, k-1);
        QuickSort(dsdv, k, j);
    }
}

void Greedy(DoVat dsdv[], int n, int W, int *TGT, int *TL){
    int TLConLai = W;
    for (int i=0;i<n;i++){
        int So_Luong_Do_Vat_Co_The_Chon = min(TLConLai/dsdv[i].TL, 1);
        TLConLai -= So_Luong_Do_Vat_Co_The_Chon*dsdv[i].TL;
        dsdv[i].PA = So_Luong_Do_Vat_Co_The_Chon;
        *TGT += dsdv[i].PA*dsdv[i].GT;
        *TL = TLConLai;
        if (TLConLai ==  0) break;
    }
}

int main()
{
    DoVat dsdv[20];
    int n, W, TGT=0, TLConLai=0;
    readData(dsdv, &W, &n);
    QuickSort(dsdv, 0, n-1);
    Greedy(dsdv, n, W, &TGT, &TLConLai);
    printData(dsdv, n);
    printf("Tong gia tri la: %d | Trong luong con lai la: %d", TGT, TLConLai);
    return 0;
}