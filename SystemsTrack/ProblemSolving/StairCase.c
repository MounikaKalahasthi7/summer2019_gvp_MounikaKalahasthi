#include<stdio.h>

long possible_num_of_ways(int size, int step){
	if (size == 0)
		return 1;

	long count = 0;
	for (int step_size = 1; step_size <= size && step_size < step; step_size++){
		count += possible_num_of_ways(size - step_size, step);
	}
	return count;
}

int main(){
	int size_of_staircase, max_step_size;
	printf("size ofstaircase: ");
	scanf_s("%d", &size_of_staircase);

	printf("maximum step size: ");
	scanf_s("%d", &max_step_size);

	printf("possible no. of ways: %ld\n", possible_num_of_ways(size_of_staircase + 1, max_step_size));
	system("pause");
	return 0;
}