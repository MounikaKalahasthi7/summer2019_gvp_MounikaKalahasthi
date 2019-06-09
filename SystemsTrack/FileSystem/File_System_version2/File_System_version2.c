#include <stdio.h>
#include <string.h>
#include "Disk_functions.h"
int main()
{
	char string[50];
	char command[20];
	char source[50];
	char destination[50];

	check_hardDisk();

	while (1)
	{
		int cindx = 0, source_indx = 0, dest_indx = 0, i = 0;
		printf(">");
		fflush(stdin); gets(string);
		if (string[i] != '\0' && string[i] != '\n')
		{
			while (string[i] != ' ' && string[i] != '\0')
				command[cindx++] = string[i++];
			command[cindx++] = '\0';

			if (string[i] != '\0')
			{
				i++;
				while (string[i] != ' ' && string[i] != '\0')
					source[source_indx++] = string[i++];
				source[source_indx] = '\0';

				i++;
				while (string[i] != '\0')
					destination[dest_indx++] = string[i++];
				destination[dest_indx] = '\0';
			}
		}
		if (strcmp(command, "format") == 0)
			INIT();
		else if (strcmp(command, "ls") == 0)
			list_all_filenames();
		else if (strcmp(command, "copytodisk") == 0)
			copy_to_disk(source, destination);
		else if (strcmp(command, "copyfromdisk") == 0)
			copy_from_disk(source, destination);
		else if (strcmp(command, "delete") == 0)
			delete_file_from_disk(source);
		else if (strcmp(command, "exit") == 0)
			break;
		else
			printf("invalid command");
		printf("\n");
	}
}