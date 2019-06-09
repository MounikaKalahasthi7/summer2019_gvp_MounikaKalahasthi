#include <stdio.h>
#include <string.h>
#include "disk_operations.h"

void parse_command(char *input){
	char command[20];
	char source[50];
	char destination[50];
	int command_index = 0, source_index = 0, dest_index = 0, input_index = 0;
	if (input[input_index] != '\0' && input[input_index] != '\n')
	{
		while (input[input_index] != ' ' && input[input_index] != '\0')
			command[command_index++] = input[input_index++];
		command[command_index++] = '\0';

		if (input[input_index] != '\0')
		{
			input_index++;
			while (input[input_index] != ' ' && input[input_index] != '\0')
				source[source_index++] = input[input_index++];
			source[source_index] = '\0';

			input_index++;
			while (input[input_index] != '\0')
				destination[dest_index++] = input[input_index++];
			destination[dest_index] = '\0';
		}
	}
	_strlwr(command);

	if (strcmp(command, "format") == 0){
		INIT();
	}
	else if (strcmp(command, "ls") == 0){
//		list_all_filenames();
	}
	else if (strcmp(command, "debug") == 0){
//		debug();
	}
	else if (strcmp(command, "copytodisk") == 0){
		copy_to_disk(source, destination);
	}
	else if (strcmp(command, "copyfromdisk") == 0){
		copy_from_disk(source, destination);
	}
	else if (strcmp(command, "delete") == 0){
//		delete_file_from_disk(source);
	}
	else if (strcmp(command, "exit") == 0)
		exit(0);
	else
		printf("invalid command");
	printf("\n");

}

int main()
{
	char input[50];

	while (1)
	{
		printf(">");
		fflush(stdin); gets(input);
		parse_command(input);
	}
}