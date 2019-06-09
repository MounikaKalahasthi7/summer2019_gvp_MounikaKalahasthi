#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void display(int *array, int array_size){
	for (int index = 0; index < array_size; index++)
		printf("%d ", array[index]);
	printf("\n");
}

void permutation(int *array, int start, int end)
{
	if (start == end)
	{
		display(array, end + 1);
		return;
	}

	int index;
	for (index = start; index <= end; index++)
	{
		swap((array + index), (array + start));
		permutation(array, start + 1, end);
		swap((array + index), (array + start));
	}
}

int main()
{
	int size;
	printf("size of array: ");
	scanf_s("%d", &size);

	int *arr=(int *)malloc(size*sizeof(int));
	printf("elements: ");
	for (int index = 0; index<size; index++)
		scanf_s("%d", &arr[index]);

	permutation(arr, 0, size - 1);
	system("pause");
	return 0;
}