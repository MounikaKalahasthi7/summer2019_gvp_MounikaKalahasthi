#include<stdio.h>
#include<stdlib.h>

long sum_of_elements_linear(int *array,int size){
	if (size == 1)
		return array[0];
	return array[0] + sum_of_elements_linear(array+1, size - 1);
}

long sum_of_elements_DnC(int *array, int lb, int ub){
	if (lb < ub){
		int mid = (lb + ub)/2;
		long sum_left = sum_of_elements_DnC(array, lb, mid);
		long sum_right = sum_of_elements_DnC(array, mid+1, ub);
		return sum_left + sum_right;
	}
	return array[lb];
}

int main(){
	int *array;
	int array_size;
	printf("array size: ");
	scanf_s("%d", &array_size);
	array = (int *)malloc(sizeof(int)*array_size);
	
	for (int index = 0; index < array_size; index++)
		scanf_s("%d", &array[index]);
	printf("sum of elements:(linear) %ld\n", sum_of_elements_linear(array,array_size));
	printf("sum of elements:(DnC) %ld", sum_of_elements_DnC(array, 0, array_size - 1));


	system("pause");
	return 0;
}