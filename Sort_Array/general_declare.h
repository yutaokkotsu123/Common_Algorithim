// this max index is up to you.
#define MAX_INDEX 100

typedef struct
{
    int recordfield;
    float otherfield;
} recordtype;

void Swap(recordtype *a, recordtype *b)
{
    recordtype t = *a;
    *a = *b;
    *b = t;
}

void Read_Data(recordtype list[], int *n){
    FILE *f;
    f = fopen("data.txt", "r");
    if (f!=NULL){
        int i = 0;
        while (!feof(f)){
            fscanf(f, "%d%d%[^\n]", &list[i].recordfield, &list[i].otherfield);
            i++;
        }
        *n = i;
    }
    else{ printf("Error to open file data.txt !");return;}
    fclose(f);
}

void Print_List(recordtype list[], int n){
    for (int i=0;i<n;i++){
        printf("%d ", list[i].recordfield);
    }
    printf("\n");
}

