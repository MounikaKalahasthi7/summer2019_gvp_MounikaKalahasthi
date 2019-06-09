#include<stdio.h>
#include<stdlib.h>

void possible_numbers( char *str, int n, int index)
{
	// If number becomes N-digit, print it 
	if (n == 0)
	{
		str[index] = '\0';
		printf("%s\n", str);
		return;
	}

	for (int i = 0; i <= 9; i++)
	{
		if (index == 0 && i == 0)
			possible_numbers(str, n - 1, index);
		else{
			str[index] = '0' + i;
			possible_numbers(str, n - 1, index + 1);
		}
	}
}

int main()
{
	int n;
	printf("power: ");
	scanf_s("%d", &n);
	char *str = (char *)malloc((n+1)*sizeof(char));
	possible_numbers( str, n-1, 0);
	system("pause");
	return 0;
}
