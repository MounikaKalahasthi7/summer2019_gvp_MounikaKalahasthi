#include<stdio.h>
#include<stdlib.h>
#define CRT_SECURE_NO_WARNINGS

int read_array(int* array) {
	int array_size;
	printf("no.of elements: ");
	scanf_s("%d", &array_size);

	array = (int *)malloc(sizeof(int) * array_size);
	for (int i = 0; i < array_size; i++)
		scanf_s("%d", &array[i]);
	return array_size;
}

void merge(int *array, int lower_boundary, int mid, int upper_boundary) {
	int* temp = (int*)malloc((upper_boundary - lower_boundary + 1) * sizeof(int));
	int temp_index = 0;
	int left_array_index = lower_boundary;
	int right_array_index = mid + 1;

	while (left_array_index <= mid && right_array_index <= upper_boundary) {
		if (array[left_array_index] < array[right_array_index])
			temp[temp_index++] = array[left_array_index++];
		else
			temp[temp_index++] = array[right_array_index++];
	}

	while (left_array_index <= mid)
		temp[temp_index++] = array[left_array_index++];
	while (right_array_index <= upper_boundary)
		temp[temp_index++] = array[right_array_index++];

	for (int i = 0, array_index = lower_boundary; array_index <= upper_boundary; i++, array_index++)
		array[array_index] = temp[i];
}

void merge_sort(int *array, int lower_boundary, int upper_boundary) {
	if (lower_boundary < upper_boundary) {
		int mid = (lower_boundary + upper_boundary) / 2;
		merge_sort(array, lower_boundary, mid);
		merge_sort(array, mid + 1, upper_boundary);
		merge(array, lower_boundary, mid, upper_boundary);
	}
}

void display(int* array, int array_size) {
	printf("Array:\n");
	for (int i = 0; i < array_size; i++)
		printf("%d ", array[i]);
}

int main() {

	int *array;
	int array_size;
	printf("no.of elements: ");
	scanf_s("%d", &array_size);

	array = (int *)malloc(sizeof(int) * array_size);
	for (int i = 0; i < array_size; i++)
		scanf_s("%d", &array[i]);

	merge_sort(array, 0, array_size - 1);
	display(array, array_size);
	system("pause");
	return 0;
}