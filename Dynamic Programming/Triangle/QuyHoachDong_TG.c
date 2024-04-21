#include <stdio.h>
#define size 20

void readData(int tg[][size], int *n)
{
	FILE *f;
	f = fopen("tg.txt", "r");
	int i = 0;
	if (f != NULL)
	{
		while (!feof(f))
		{
			for (int j = 0; j <= i; j++)
			{
				fscanf(f, "%d", &tg[i][j]);
			}
			i++;
		}
	}
	else
		printf("Loi mo file");
	*n = i;
}

void PrintTG(int tg[][size], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			printf("%d ", tg[i][j]);
		}
		printf("\n");
	}
}

int CS_max(int F[][size], int i, int j)
{
	if (j == 0)
		return (F[i - 1][0] > F[i - 1][1]) ? 0 : 1;
	if (j == i)
		return i - 1;
	if (j == i - 1)
		return (F[i - 1][i - 1] > F[i - 1][i - 2]) ? (i - 1) : (i - 2);

	if (F[i - 1][j - 1] > F[i - 1][j] && F[i - 1][j - 1] > F[i - 1][j + 1])
		return j - 1;
	if (F[i - 1][j] > F[i - 1][j - 1] && F[i - 1][j] > F[i - 1][j + 1])
		return j;
	if (F[i - 1][j + 1] > F[i - 1][j] && F[i - 1][j + 1] > F[i - 1][j - 1])
		return j + 1;
}

int CS_max_dong_cuoi(int F[], int j)
{
	int somax = F[0];
	int maxindex = 0;
	int k;
	for (k = 1; k <= j; k++)
		if (F[k] > somax)
		{
			somax = F[k];
			maxindex = k;
		}
	return maxindex;
}

void Tao_Bang(int a[][size], int n, int F[][size])
{
	int i, j;
	F[0][0] = a[0][0];
	F[1][0] = a[1][0] + F[0][0];
	F[1][1] = a[1][1] + F[0][0];
	for (i = 2; i < n; i++)
		for (j = 0; j <= i; j++)
		{
			int k = CS_max(F, i, j);
			F[i][j] = a[i][j] + F[i - 1][k];
		}
}

void Tra_Bang(int a[][size], int n, int F[][size], int PA[])
{
	int i, j;
	j = CS_max_dong_cuoi(F[n - 1], n - 1);
	PA[n - 1] = a[n - 1][j];
	for (i = n - 1; i >= 1; i--)
	{
		j = CS_max(F, i, j);
		PA[i - 1] = a[i - 1][j];
	}
}

int main()
{
	int n;
	int tg[10][size], a[10][size];
	int PA[10];
	readData(a, &n);
	PrintTG(a, n);
	Tao_Bang(a, n, tg);
	Tra_Bang(a, n, tg, PA);
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += PA[i];
	}
	printf("%d\n", sum);
	PrintTG(tg, n);
	return 0;
}
