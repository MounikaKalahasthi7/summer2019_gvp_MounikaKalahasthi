#include<stdio.h>
#include<stdlib.h>
#define CRT_SECURE_NO_WARNINGS

void display(int* array, int array_size) {
	printf("Array:\n");
	for (int i = 0; i < array_size; i++)
		printf("%d ", array[i]);
}

void count_sort(int *array, int array_size){
	int count = 0;
	for (int index = 0; index < array_size; index++)
		count += array[index];
	
	int zeroes = array_size - count;
	for (int index = 0; index < zeroes; index++)
		array[index] = 0;
	for (int index = zeroes; index < array_size; index++)
		array[index] = 1;
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