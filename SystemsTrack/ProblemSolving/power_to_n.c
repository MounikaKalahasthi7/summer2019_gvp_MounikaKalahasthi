#include<stdio.h>
#include<stdlib.h>

long power_to_n(int base, int power){
	if (power <= 0)
		return 1;
	long val = power_to_n(base, power / 2);
	if (power % 2 == 0)
		return val*val;
	else
		return val*val*base;
}

int main()
{
	int base, power;
	printf("number: ");
	scanf_s("%d", &base);

	printf("power: ");
	scanf_s("%d", &power);

	printf("result: %ld\n", power_to_n(base, power));
	system("pause");
	return 0;
}