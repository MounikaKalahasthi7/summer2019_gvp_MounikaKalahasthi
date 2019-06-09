#include<stdio.h>
#include<stdlib.h>

int find(char *str, char **puzzle, int row_index, int col_index, int row_inc, int col_inc){
	if (str[0] != puzzle[row_index][col_index])
		return 0;
	if (str[1] == '\0')
		return 1;
	return find(str + 1, puzzle, row_index + row_inc, col_index + col_inc, row_inc, col_inc);
}

int find_occurances(char *string, char **puzzle, int rows, int cols){
	char ch = string[0];
	int count=0;
	for (int row_index = 0; row_index < rows; row_index++)
		for (int col_index = 0; col_index < cols; col_index++)
		{
			char temp = puzzle[row_index][col_index];
			if (temp == ch){
				char ch1= string[1];
				if (ch1 != '\0'){
					// south-east
					if (row_index + 1 < rows && col_index + 1 < cols && puzzle[row_index + 1][col_index + 1] == ch1)
						count += find(string, puzzle, row_index, col_index, 1, 1);
					
					// south
					if (row_index + 1 < rows && puzzle[row_index + 1][col_index] == ch1)
						count += find(string, puzzle, row_index, col_index, 1, 0);
					
					// south-west
					if (row_index + 1 < rows && col_index - 1 > -1 && puzzle[row_index + 1][col_index - 1] == ch1)
						count += find(string, puzzle, row_index, col_index, 1, -1);

					// north-east
					if (row_index - 1>-1 && col_index + 1<cols && puzzle[row_index - 1][col_index + 1] == ch1)
						count += find(string, puzzle, row_index, col_index, -1, 1);

					// north
					if (row_index - 1>-1 && puzzle[row_index - 1][col_index] == ch1)
						count += find(string, puzzle, row_index, col_index, -1, 0);

					// north-west
					if (row_index - 1>-1 && col_index - 1>-1 && puzzle[row_index - 1][col_index - 1] == ch1)
						count += find(string, puzzle, row_index, col_index, -1, -1);

					// east
					if (col_index + 1<cols && puzzle[row_index][col_index + 1] == ch1)
						count += find(string, puzzle, row_index, col_index, 0, 1);

					// west
					if (col_index - 1>-1 && puzzle[row_index][col_index - 1] == ch1)
						count += find(string, puzzle, row_index, col_index, 0, -1);
				}
				else
					count++;
			}
		}
	return count;
}

void find_words_and_occurances(char *str, char **puzzle, int rows, int cols){
	int num_of_occurances = find_occurances(str, puzzle, rows, cols);
	printf("word: %s  occurances: %d", str, num_of_occurances);
}

/*
void find_words_and_occurances(FILE *file_ptr, char **puzzle, int rows, int cols){
	char ch = fgetc(file_ptr);
	while (ch!=EOF){
		char str[100];
		int index = 0;
		do
		{
			str[index++] = ch;
			ch = fgetc(file_ptr);
		} while (ch != EOF && ch != '\n');

		str[index] = '\0';

		int num_of_occurances = find_occurances(str, puzzle, rows, cols);
		printf("word: %s  occurances: %d", num_of_occurances);
	}
}
*/

int main(){
	char *word = "hi";

	char **puzzle;
	int rows, cols;
	printf("puzzle dimensions: ");
	scanf_s("%d %d", &rows, &cols);

	puzzle = (char **)malloc(sizeof(char *)*rows);
	for (int index = 0; index < rows; index++)
		puzzle[index] = (char *)malloc((cols + 1)*sizeof(char));

	for (int index = 0; index < rows; index++){
		fflush(stdin);
		gets_s(puzzle[index], cols + 1);
	}

	find_words_and_occurances(word, puzzle, rows, cols);
	system("pause");
	return 0;
}