#include<stdio.h> 
#include<stdlib.h>

void possible_permutations_with_length(int arr[], int data[], int start, int end, int index, int length)
{
	if (index == length)
	{
		for (int j = 0; j<length; j++)
			printf("%d ", data[j]);
		printf("\n");
		return;
	}

	for (int i = start; i <= end && end - i + 1 >= length - index; i++)
	{
		data[index] = arr[i];
		possible_permutations_with_length(arr, data, i + 1, end, index + 1, length);
	}
}


void all_permutations(int arr[], int size, int length)
{
	int *data = (int *)malloc(length*(sizeof(int)));
	possible_permutations_with_length(arr, data, 0, size - 1, 0, length);
}

int main()
{
	int size;
	printf("size of array: ");
	scanf_s("%d", &size);

	int *arr = (int *)malloc(size*sizeof(int));
	printf("elements: ");
	for (int index = 0; index<size; index++)
		scanf_s("%d", &arr[index]);

	for (int length = 1; length <= size; length++)
		all_permutations(arr, size, length);
	system("pause");
}
