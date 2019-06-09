#include<stdio.h>
#include<stdlib.h>
#define CRT_SECURE_NO_WARNINGS

char *compress(char *input){
	int size = 0;
	for (; input[size] != '\0'; size++);

	char *output = (char *)malloc(size);
	char count_string[10];
	int counter = 1;
	int input_index = 1;
	int output_index = 0;

	while (input[input_index] != '\0'){
		if (input[input_index] != input[input_index - 1])
		{
			output[output_index++] = input[input_index - 1];
			if (counter > 9){
				_itoa_s(counter, count_string, 10, 10);
				for (int i = 0; count_string[i] != '\0'; i++, output_index++)
					output[output_index] = count_string[i];
			}
			else if (counter > 1)
				output[output_index++] = '0' + counter;
			counter = 1;
		}
		else
			counter++;

		input_index++;
	}

	output[output_index++] = input[input_index - 1];
	if (counter > 9){
		_itoa_s(counter, count_string, 10, 10);
		for (int i = 0; count_string[i] != '\0'; i++, output_index++)
			output[output_index] = count_string[i];
	}
	else if (counter > 1)
		output[output_index++] = '0' + counter;

	output[output_index] = '\0';

	return output;
}

int main()
{
	char input[100];
	char *output;
	printf("string to be compressed: ");
	gets_s(input, 20);
	output = compress(input);
	printf("answer: %s\n", output);

	system("pause");
	return 0;
}