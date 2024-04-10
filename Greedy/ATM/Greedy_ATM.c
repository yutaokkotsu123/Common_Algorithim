#include <stdio.h>

typedef struct{
    char TenTien[25];
    int MG, PA;
}Tien;

void readFile(Tien ds[], int *n){
    FILE *f;
    f = fopen("ATM.txt", "r");
    int i=0;
    if (f!=NULL){
        while (!feof(f)){
            fscanf(f, "%d%[^\n]", &ds[i].MG, ds[i].TenTien);
            ds[i++].PA = 0;
        }
    }
    else printf("Loi mo file.");
    *n = i;
    fclose(f);
}

void Swap(Tien *a, Tien *b)
{
    Tien t = *a;
    *a = *b;
    *b = t;
}

void BubbleSort(Tien list[], int n){
    for (int i=0;i<=n-2;i++){
        for (int j=n-1;j>=i+1;j--){
            if (list[j].MG > list[j-1].MG) Swap(&list[j], &list[j-1]);
        }
    }
}

void printData(Tien ds[], int n){
    for (int i=0;i<n;i++){
        printf("%d %s\n",ds[i].MG, ds[i].TenTien);
    }
}

void printPA(Tien ds[], int n){
    printf("PA   Tien So      Tien Chu");
    for (int i=0;i<n;i++){
        printf("\n %d   %d      %s", ds[i].PA, ds[i].MG, ds[i].TenTien);
    }
}

void Greedy(Tien ds[], int n, int TienCanRut){
    int i=0;
    BubbleSort(ds, n);
    while(i<n && TienCanRut>0){
        ds[i].PA = TienCanRut/ds[i].MG;
        TienCanRut -= (ds[i].PA*ds[i].MG);
        i++;
    }
}

int main(){
    int n, TienCanRut;
    Tien ds[100];
    readFile(ds, &n);
    printf("Nhap so tien can rut: ");
    scanf("%d", &TienCanRut);
    Greedy(ds, n, TienCanRut);
    printPA(ds, n);
    return 0;
}