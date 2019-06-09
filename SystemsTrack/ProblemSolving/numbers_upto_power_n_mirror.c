#include<stdio.h>
#include<stdlib.h>

void possible_numbers(char *mirror, char *str, int n, int index)
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
			possible_numbers(mirror, str, n - 1, index);
		else{
			str[index] = mirror[i];
			possible_numbers(mirror, str, n - 1, index + 1);
		}
	}
}

int main()
{
	int n;
	printf("power: ");
	scanf_s("%d", &n);
	char *str = (char *)malloc((n + 1)*sizeof(char));
	char *mirror = "012Eh59L86";
	possible_numbers(mirror, str, n - 1, 0);
	system("pause");
	return 0;
}
