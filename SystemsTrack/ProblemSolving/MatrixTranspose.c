
#include<stdio.h>
#include<stdlib.h>

void read_matrix(int **matrix, int m, int n){

	printf("matrix elements:\n");
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			scanf_s("%d", &matrix[i][j]);
}

int **transpose(int **matrix, int m, int n){
	int **transp = (int **)malloc(sizeof(int *)*n);

	for (int i = 0; i < n; i++)
		transp[i] = (int *)malloc(sizeof(int)*m);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			transp[i][j] = matrix[j][i];

	return transp;
}

int main()
{
	int **matrix;

	int m, n;
	printf("order of matrix: ");
	scanf_s("%d %d", &m, &n);

	matrix = (int **)malloc(sizeof(int *)*m);

	for (int i = 0; i < m; i++)
		matrix[i] = (int *)malloc(sizeof(int)*n);

	read_matrix(matrix, m, n);

	int **transpose_matrix;
	transpose_matrix = transpose(matrix, m, n);

	printf("transpose:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%d ", transpose_matrix[i][j]);
		printf("\n");
	}

	system("pause");
	return 0;
}