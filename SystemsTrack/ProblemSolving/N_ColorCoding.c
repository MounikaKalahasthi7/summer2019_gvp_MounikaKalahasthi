#define CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

void display(int* array, int array_size) {
	printf("Array:\n");
	for (int i = 0; i < array_size; i++)
		printf("%d ", array[i]);
}

void swap(int *array, int index_1, int index_2){
	int temp = array[index_1];
	array[index_1] = array[index_2];
	array[index_2] = temp;
}

void count_sort(int *array, int array_size){
	int upper_boundary = array_size - 1;
	int lower_boundary = 0;
	int pointer = 0;

	while (pointer <= upper_boundary)
	{
		if (array[pointer] == 0)
			swap(array, pointer++, lower_boundary++);
		else if (array[pointer] == 2)
			swap(array, pointer, upper_boundary--);
		else
			pointer++;
	} 
}

int main() {

	int *array;
	int array_size;

	printf("no.of elements: ");
	scanf_s("%d", &array_size);

	array = (int *)malloc(sizeof(int) * array_size);
	for (int i = 0; i < array_size; i++)
		scanf_s("%d", &array[i]);

	count_sort(array, array_size);
	display(array, array_size);
	system("pause");
	return 0;
}