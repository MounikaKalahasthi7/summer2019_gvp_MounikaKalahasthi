#include "excel_operations.h"

Cell **create_sheet() {
	Cell **sheet = (Cell **)malloc(sizeof(Cell *) * MAXSIZE);
	for (int row_index = 0; row_index < MAXSIZE; row_index++)
		sheet[row_index] = (Cell *)malloc(sizeof(Cell) * MAXSIZE);

	for (int row_index = 0; row_index < MAXSIZE; row_index++) {
		for (int col_index = 0; col_index < MAXSIZE; col_index++) {
			sheet[row_index][col_index].data = 0;
			sheet[row_index][col_index].string_data = NULL;
			sheet[row_index][col_index].expression = NULL;
		}
	}

	return sheet;
}

int GET(char *cell, Cell **sheet) {
	int col = *cell - 'A';
	cell++;
	int row = str_to_number(cell) - 1;

	if (sheet[row][col].expression == NULL)
		return sheet[row][col].data;
	else
		return evaluate(sheet[row][col].expression, sheet);
}

void SET(Command *command, Cell **sheet) {
	char *cell = command->cell;
	int col = *cell - 'A';
	cell++;
	int row = str_to_number(cell) - 1;

	if (command->expression == NULL)
		sheet[row][col].data = command->val;
	else {
		if (detect_cycle(command->expression, sheet, row, col))
			printf("Given expression forms cycle\n");
		else
			sheet[row][col].expression = command->expression;
	}
}

void PRINT(Cell **sheet) {
	for (int row_index = 0; row_index < MAXSIZE; row_index++) {
		for (int col_index = 0; col_index < MAXSIZE; col_index++) {
			if (sheet[row_index][col_index].string_data == NULL) {
				if (sheet[row_index][col_index].expression == NULL)
					printf("%d ", sheet[row_index][col_index].data);
				else
					printf("%d ", evaluate(sheet[row_index][col_index].expression, sheet));
			}
			else
				printf("%s ", sheet[row_index][col_index].string_data);
		}

		printf("\n");
	}
}

void IMPORT(Command *command, Cell **sheet) {
	FILE *fp = fopen(command->file_name, "r");
	char line[256];
	int row = 0, col, index;
	while (fgets(line, 256, fp)) {
		col = 0;
		for (int line_index = 0; line[line_index]; line_index++) {
			char value[30];
			index = 0;
			while (line[line_index] != ':' && line[line_index] != ',' && line[line_index] != '\n')
				value[index++] = line[line_index++];
			value[index] = '\0';

			if (is_number(value))
				sheet[row][col].data = str_to_number(value);
			else {
				sheet[row][col].string_data = (char *)malloc(sizeof(char) * 30);
				index = 0;
				for (; value[index]; index++)
					sheet[row][col].string_data[index] = value[index];

				sheet[row][col].string_data[index] = '\0';
			}


			if (line[line_index] == '\n')
				break;
			if (line[line_index] == ',') {
				col++;
				continue;
			}
			line_index++;

			char *expression = (char *)malloc(sizeof(char) * 10);
			index = 0;
			while (line[line_index] != ',' && line[line_index] != '\n') {
				expression[index++] = line[line_index++];
			}
			expression[index] = '\0';
			sheet[row][col].expression = expression;
			col++;
		}
		row++;
	}
	fclose(fp);
}

void EXPORT(char *file_name, Cell **sheet) {
	FILE *fp = fopen(file_name, "w");

	for (int row_index = 0; row_index < MAXSIZE; row_index++) {
		for (int col_index = 0; col_index < MAXSIZE; col_index++) {
			fprintf(fp, "%d", sheet[row_index][col_index].data);
			if (sheet[row_index][col_index].expression != NULL) {
				fprintf(fp, "%c", ':');
				fprintf(fp, "%s", sheet[row_index][col_index].expression);
			}
			if (col_index != MAXSIZE - 1)
				fprintf(fp, "%c", ',');
		}
		fprintf(fp, "%c", '\n');
	}

	fclose(fp);
}

int detect_cycle(char *expression, Cell **sheet, int actual_row, int actual_col) {
	char visited[10][10], cell[10];
	int top = -1, index = 0;

	do {
		if (top != -1) {
			int col = visited[top][0] - 'A';

			int row;
			if (is_digit(visited[top][2]))
				row = 9;
			else
				row = (visited[top][1] - '0') - 1;

			if (row == actual_row && col == actual_col)
				return 1;

			top--;

			if (sheet[row][col].expression == NULL)
				continue;
			expression = sheet[row][col].expression;
		}

		while (!is_operator(*expression) && *expression) {
			cell[index++] = *expression;
			expression++;
		}

		cell[index] = '\0';
		if (!is_number(cell)) {
			top++;

			index = 0;
			for (; cell[index]; index++)
				visited[top][index] = cell[index];
			visited[top][index] = '\0';

		}

		if (*expression) {
			expression++;
			index = 0;
			while (!is_operator(*expression) && *expression) {
				cell[index++] = *expression;
				expression++;
			}

			cell[index] = '\0';
			if (!is_number(cell)) {
				top++;

				index = 0;
				for (; cell[index]; index++)
					visited[top][index] = cell[index];
				visited[top][index] = '\0';

			}
		}

	} while (top != -1);

	return 0;

}

int AVG(char *col, Cell **sheet) {
	int col_index = 1;
	while (col_index < 10) {
		if (str_compare(sheet[0][col_index].string_data, col))
			break;
		col_index++;
	}

	if (col_index == 10)
		return -1;

	int sum = 0;
	for (int row_index = 1; row_index < 10; row_index++) 
		sum += sheet[row_index][col_index].data;
	return sum / 9;
}

int TOTAL(char *row, Cell **sheet) {
	int row_index = 1;
	for (; row_index < 10; row_index++) {
		if (str_compare(sheet[row_index][0].string_data, row))
			break;
	}

	if (row_index == 10)
		return -1;

	int sum = 0;
	for (int col_index = 1; col_index < 10; col_index++)
		sum += sheet[row_index][col_index].data;

	return sum;
}

char *TOPPER(char *sub, Cell **sheet) {
	if (sub == NULL)
		return NULL;

	int col_index = 1;
	while (col_index < 10) {
		if (str_compare(sheet[0][col_index].string_data, sub))
			break;
		col_index++;
	}

	if (col_index == 10)
		return NULL;

	int max = -1;
	char* result = NULL;
	for (int row_index = 1; row_index < 10; row_index++) {
		if (max < sheet[row_index][col_index].data) {
			max = sheet[row_index][col_index].data;
			result = sheet[row_index][0].string_data;
		}
	}

	return result;
}
