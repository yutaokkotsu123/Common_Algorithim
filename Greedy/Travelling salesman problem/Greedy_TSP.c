#include <stdio.h>

typedef struct
{
    float len;
    int strt, end;
} Edge;

void Swap(Edge *a, Edge *b)
{
    Edge t = *a;
    *a = *b;
    *b = t;
}

void BubbleSort(Edge lst[], int n)
{
    for (int i = 0; i <= n - 2; i++)
    {
        for (int j = n - 1; j >= i + 1; j--)
        {
            if (lst[j].len < lst[j - 1].len)
                Swap(&lst[j], &lst[j - 1]);
        }
    }
}

void readFile(Edge lst[], int *n, int *m)
{
    FILE *f;
    f = fopen("TSP.txt", "r");
    int k = 0;
    float temp;
    if (f != NULL)
    {
        fscanf(f, "%d", n);
        for (int i = 0; i < *n; i++)
        {
            for (int j = i; j < *n; j++)
            {
                if (i == j)
                    for (int t = 0; t <= j; t++)
                        fscanf(f, "%f", &temp);
                else
                {
                    fscanf(f, "%f", &lst[k].len);
                    lst[k].strt = i;
                    lst[k].end = j;
                    k++;
                }
            }
        }
    }
    else
        printf("Loi mo file");
    *m = k;
}

void printData(Edge lst[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%.2d - %d | %d | %.2f\n", i, lst[i].strt, lst[i].end, lst[i].len);
    }
}

int check_level_3(Edge PA[], int k, Edge newEdge)
{
    int i = 0, count = 0;
    while (i < k && count < 2)
    {
        if (newEdge.strt == PA[i].strt || newEdge.strt == PA[i].end)
            count++;
        i++;
    }
    if (count == 2)
        return 1;
    i = 0;
    count = 0;
    while (i < k && count < 2)
    {
        if (newEdge.end == PA[i].strt || newEdge.end == PA[i].end)
            count++;
        i++;
    }
    return count == 2;
}

void init_forest(int p[], int n)
{
    for (int i = 0; i < n; i++)
        p[i] = i;
}

void update_forest(int p[], int r1, int r2)
{
    p[r2] = r1;
}

int findRoot(int p[], int u)
{
    while (u != p[u])
    {
        u = p[u];
    }
    return u;
}

int cycle(int strt, int end)
{
    return strt == end;
}

void Greedy(Edge lst[], int n, Edge PA[])
{
    int i, j, p[n];
    init_forest(p, n);
    int r_strt, r_end;

    j = 0;
    for (i = 0; i < n * (n - 1) / 2 && j < n - 1; i++)
    {
        r_strt = findRoot(p, lst[i].strt);
        r_end = findRoot(p, lst[i].end);
        if (!check_level_3(PA, j, lst[i]) && !cycle(r_strt, r_end))
        {
            PA[j] = lst[i];
            j++;
            update_forest(p, r_strt, r_end);
        }
    }

    for (; i < n * (n - 1) / 2; i++)
    {

        r_strt = findRoot(p, lst[i].strt);
        r_end = findRoot(p, lst[i].end);
        if (!check_level_3(PA, n - 1, lst[i]) && cycle(r_strt, r_end))
        {
            PA[n - 1] = lst[i];
            break;
        }
    }
}

int main()
{
    int n, m;
    Edge lst[40];
    readFile(lst, &n, &m);
    printf("Danh sach canh: \n");
    printData(lst, m);
    Edge PA[n];
    BubbleSort(lst, m);
    printf("Danh sach canh duoc sap xep: \n");
    printData(lst, m);
    Greedy(lst, n, PA);
    printf("Danh sach phuong an: \n");
    printData(PA, n);
    return 0;
}