#include "filesystem_level.h"

void listallfilenames()
{
	int count = 0;
	FILE *fileptr;
	char flag;
	char file_name[20];
	fileptr = f_open(HARD_DISK, "rb");
	fseek(fileptr, 4, 1);
	if (fileptr != NULL){
		while (ftell(fileptr) < size)
		{
			fread(&flag, 1, 1, fileptr);
			if (flag == 0)
				fseek(fileptr, 24, 1);
			else
			{
				fread(&file_name, 16, 1, fileptr);
				printf("%s\n", file_name);
				fseek(fileptr, 8, 1);
			}
		}
	}
	fclose(fileptr);
}

