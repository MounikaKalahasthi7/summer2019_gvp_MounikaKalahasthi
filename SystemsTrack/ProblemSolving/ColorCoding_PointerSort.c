#include<stdio.h>
#include<stdlib.h>
#define CRT_SECURE_NO_WARNINGS

void display(int* array, int array_size) {
	printf("Array:\n");
	for (int i = 0; i < array_size; i++)
		printf("%d ", array[i]);
}

void pointer_sort(int *array, int array_size){
	int zero_pointer = array_size - 1;
	int one_pointer = 0;

	while (one_pointer < zero_pointer)
	{
		while (one_pointer < array_size && array[one_pointer] != 1)
			one_pointer++;
		while (zero_pointer >= 0 && array[zero_pointer] != 0)
			zero_pointer--;
		if (one_pointer < zero_pointer){
			array[one_pointer] = 0;
			array[zero_pointer] = 1;
		}
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

	pointer_sort(array, array_size);
	display(array, array_size);
	system("pause");
	return 0;
}