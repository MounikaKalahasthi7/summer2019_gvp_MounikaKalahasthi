#include<stdio.h>
#include<stdlib.h>
#include<map>

long fibonacci(long n){
	if (n == 0 || n == 1)
		return n;
	return fibonacci(n - 1) + fibonacci(n - 2);
}

long m_fibonacci(long *array, long n){
	if (array[n] == -1)
		array[n] = m_fibonacci(array, n - 1) + m_fibonacci(array, n - 2);
	return array[n];
}

long fibonacci_memorisation(long n){
	long *array;
	array = (long *)malloc((n + 1)*sizeof(long));
	for (long index = 2; index <= n; index++)
		array[index] = -1;
	array[0] = 0;
	array[1] = 1;

	// finding fibonacci num
	return m_fibonacci(array, n);
}

long **matrix_mul(long **matrix_1, long **matrix_2){

	long **array = (long **)malloc(2 * sizeof(long *));
	array[0] = (long *)malloc(2 * sizeof(long));
	array[0][0] = (matrix_1[0][0] * matrix_2[0][0]) + (matrix_1[0][1] * matrix_2[1][0]);
	array[0][1] = (matrix_1[0][0] * matrix_2[0][1]) + (matrix_1[0][1] * matrix_2[1][1]);
	array[1] = (long *)malloc(2 * sizeof(long));
	array[1][0] = (matrix_1[1][0] * matrix_2[0][0]) + (matrix_1[1][1] * matrix_2[1][0]);
	array[1][1] = (matrix_1[1][0] * matrix_2[0][1]) + (matrix_1[1][1] * matrix_2[1][1]);
	return array;
}

long **co_efficient_power_n(long n){
	if (n == 1){
		long **array = (long **)malloc(2 * sizeof(long *));
		array[0] = (long *)malloc(2 * sizeof(long));
		array[0][0] = 0;
		array[0][1] = 1;
		array[1] = (long *)malloc(2 * sizeof(long));
		array[1][0] = 1;
		array[1][1] = 1;
		return array;
	}
	else
		return matrix_mul(co_efficient_power_n(1), co_efficient_power_n(n - 1));
}

long fibonacci_matrix_exponentiation(int n){
	long **array = co_efficient_power_n(n);
	return array[0][1];
}
int main(){
	int n;
	printf("********** fibonacci **********\n");
	printf("n value: ");
	scanf_s("%d", &n);
//	printf("simple recursion: %lsd\n", fibonacci(n));
//	printf("memorisation: %ld\n", fibonacci_memorisation(n));
	printf("matrix exponentiation: %ld\n", fibonacci_matrix_exponentiation(n));
	system("pause");
	return 0;
}