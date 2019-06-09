#include<stdio.h>
#include<stdlib.h>

void read_matrix(int **matrix, int m, int n){

	printf("matrix elements:\n");
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			scanf_s("%d", &matrix[i][j]);
}

void unwrap_spiral(int *array,int array_index, int **matrix, int rows, int cols, int row_start, int col_start){

	for (int i = row_start; i <= cols; i++) 
		array[array_index++] = matrix[row_start][i];

	for (int i = row_start + 1; i <= rows; i++)
		array[array_index++] = matrix[i][cols];

	if (row_start + 1 <= rows){
		for (int i = cols - 1; i >= col_start; i--) 
			array[array_index++] = matrix[rows][i];
	}
	if (col_start + 1 <= cols){
		for (int i = rows - 1; i > row_start; i--) 
			array[array_index++] = matrix[i][col_start];
	}

	if (row_start + 1 <= rows - 1 && col_start + 1 <= cols - 1)
		unwrap_spiral(array, array_index, matrix, rows - 1, cols - 1, row_start + 1, col_start + 1);;
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

	int *array = (int *)malloc((n*m)*sizeof(int));

	unwrap_spiral(array, 0, matrix, m-1, n-1, 0, 0);
	int size = m*n;
	for (int i = 0; i < size; i++)
		printf("%d ", array[i]);
	system("pause");
	return 0;
}