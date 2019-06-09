#include<stdio.h>
#include<stdlib.h>

void read_matrix(int **matrix, int m, int n){

	printf("matrix elements:\n");
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			scanf_s("%d", &matrix[i][j]);
}

int *unwrap_spiral(int **matrix, int rows, int cols){
	int *array = (int *)malloc(rows*cols*sizeof(int));
	int array_index = 0;

	//spiral traverse
	int h_index = 0;
	int v_index = 0;

	int h_range = cols;
	int v_range = rows;

	int moves;
	while (h_range != 0 && v_range != 0){

		// move right
		if (h_range > 0){
			for (moves = 0; moves < h_range; moves++)
				array[array_index++] = matrix[h_index][v_index++];
			v_range--;
			h_index++;
			v_index--;
		}
		else break;

		// move down
		if (v_range > 0){
			for (moves = 0; moves < v_range; moves++)
				array[array_index++] = matrix[h_index++][v_index];
			h_range--;
			v_index--;
			h_index--;
		}
		else break;

		// move left
		if (h_range > 0){
			for (moves = 0; moves < h_range; moves++)
				array[array_index++] = matrix[h_index][v_index--];
			v_range--;
			h_index--;
			v_index++;
		}
		else break;

		// move up
		if (v_range > 0){
			for (moves = 0; moves < v_range; moves++)
				array[array_index++] = matrix[h_index--][v_index];
			h_range--;
			v_index++;
			h_index++;
		}
	}

	return array;
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

	int *spiral_array = unwrap_spiral(matrix, m, n);
	int size = m*n;
	for (int i = 0; i < size; i++)
		printf("%d ", spiral_array[i]);
	system("pause");
	return 0;
}