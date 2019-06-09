#include "excel.h"
#include "excel_operations.h"

int type(char *token) {
	str_upper(token);
	if (str_compare(token, "GET"))
		return 1;
	if (str_compare(token, "SET"))
		return 2;
	if (str_compare(token, "PRINT"))
		return 3;
	if (str_compare(token, "IMPORT"))
		return 4;
	if (str_compare(token, "EXPORT"))
		return 5;
	if (str_compare(token, "SAVE"))
		return 6;
	if (str_compare(token, "AVG"))
		return 7;
	if (str_compare(token, "TOTAL"))
		return 8;
	if (str_compare(token, "TOPPER"))
		return 9;
	if (str_compare(token, "EXIT"))
		return 0;
	return -1;
}

Command *create_command() {
	Command *command = (Command *)malloc(sizeof(command));

	command->cell = (char *)malloc(sizeof(char) * 10);
	command->file_name = (char *)malloc(sizeof(char) * 30);
	command->expression = NULL;

	return command;
}

Command *parse_command(char *input) {
	Command *command = create_command();

	char *token = (char *)malloc(sizeof(char) * 10);

	int index = 0;
	while (*input) {
		if (*input == ' ' || *input == '\t')
			break;
		token[index++] = *input++;
	}
	token[index] = '\0';

	command->type = type(token);

	// exit, no_command, save
	if (command->type == 0 || command->type == -1 || command->type == 6)
		return command;
	if (!*input)
		return command;

	while (*input == ' ' || *input == '\t')
		input++;

	// get, set
	if (command->type == 1 || command->type == 2) {
		index = 0;
		command->cell[index++] = *input++;
		command->cell[index++] = *input++;

		if (is_digit(*input))
			command->cell[index++] = *input++;

		command->cell[index] = '\0';

		if (command->type == 2) {
			if (*input == '=')
				input++;

			if (is_number(input))
				command->val = str_to_number(input);
			else
				command->expression = input;
		}
	}
	else if (command->type == 4 || command->type == 5) {
		//import,export
		index = 0;
		int extension = 0;
		while (*input) {
			if (*input == '.')
				extension = 1;
			command->file_name[index++] = *input++;
		}
		if (!extension) {
			command->file_name[index++] = '.';
			command->file_name[index++] = 'c';
			command->file_name[index++] = 's';
			command->file_name[index++] = 'v';
		}
		command->file_name[index] = '\0';
	}
	else if (command->type == 7 || command->type == 8 || command->type == 9) {
		// Avg, Total, Topper
		index = 0;
		while (*input)
			command->cell[index++] = *input++;
		command->cell[index] = '\0';
	}
	return command;
}

int main() {
	Cell **sheet = create_sheet();
	char *prev_used_file = NULL;

	while (1) {
		printf(">");
		char *input = (char *)malloc(sizeof(char) * 20);
		gets(input);

		Command *command = parse_command(input);

		if (command->type == 0)
			break;
		else if (command->type == 1)
			printf("%d\n", GET(command->cell, sheet));
		else if (command->type == 2)
			SET(command, sheet);
		else if (command->type == 3)
			PRINT(sheet);
		else if (command->type == 4) {
			IMPORT(command, sheet);
			prev_used_file = command->file_name;
		}
		else if (command->type == 5) {
			EXPORT(command->file_name, sheet);
			prev_used_file = command->file_name;
		}
		else if (command->type == 6) {
			if (prev_used_file != NULL)
				EXPORT(prev_used_file, sheet);
			else
				printf("No file to save\n");
		}
		else if (command->type == 7) {
			int avg = AVG(command->cell, sheet);
			if (avg == -1)
				printf("Column not found\n");
			else
				printf("%d\n", avg);
		}
		else if (command->type == 8) {
			int total = TOTAL(command->cell, sheet);
			if (total == -1)
				printf("Name not found\n");
			else
				printf("%d\n", total);
		}
		else if (command->type == 9) {
			char *name = TOPPER(command->cell, sheet);
			if (name == NULL)
				printf("Name not found\n");
			else
				printf("%s\n", name);
		}
		else
			printf("Invalid command\n");
	}

	return 0;
}