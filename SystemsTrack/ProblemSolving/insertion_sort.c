#include<stdio.h>
#include<stdlib.h>

void insertion_sort(int *array, int arraysize){
	if (arraysize == 1)
		return;
	insertion_sort(array, arraysize - 1);
	
	//insert last element of current list
	int last_element = array[arraysize - 1];
	int index = arraysize - 2;

	while (index >= 0 && array[index] > last_element)
	{
		array[index + 1] = array[index];
		index--;
	}
	array[index + 1] = last_element;
}

int main()
{
	int *array;
	int array_size;
	printf("no.of elements: ");
	scanf_s("%d", &array_size);
	array = (int *)malloc(array_size*sizeof(int));
	printf("elements: ");
	for (int index = 0; index < array_size; index++)
		scanf_s("%d", &array[index]);
	insertion_sort(array, array_size);
	for (int index = 0; index < array_size; index++)
		printf("%d ", array[index]);
	system("pause");
	return 0;
}