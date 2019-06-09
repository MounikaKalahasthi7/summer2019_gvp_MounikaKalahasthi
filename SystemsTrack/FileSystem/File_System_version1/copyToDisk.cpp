#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"filesystem_level.h"

// returns the size of the file in bytes
int findSize(char* sourcefile) {
	FILE* source = f_open(sourcefile, "rb"); 
	rewind(source);
	char ch; 
	while (fread(&ch, 1, 1, source) != 0); 
	int ssize = ftell(source); 
	fclose(source); 
	return ssize; 
}

// function to check whether we can fit the file in the harddisk
int canFit(char* diskfile, char* sourcefile) {
	unsigned int start; 
	int ssize = findSize(sourcefile); 
	FILE* disk = f_open(diskfile, "r"); 
	fread(&start, sizeof(start), 1, disk);
	fclose(disk);
	if ((start + ssize) < 104857600)
		return 0;
	else
		return 1;
}

void copyToDisk(char* source, char* destination) {
	if (canFit(HARD_DISK, source) != 0) {
		printf("No available space\n");
		return;
	}

	FILE* disk = f_open(HARD_DISK, "r+");
	FILE* sourceptr = f_open(source, "r");
	unsigned int offset;
	unsigned int len_of_source_file = findSize(source); 

	// position of file pointer to start writing
	fread(&offset, sizeof(offset), 1, disk);
	if (offset == 0)
		offset = 1026; 
	
	// find the position to write in the metadata
	char flag; 
	fread(&flag , 1, 1, disk);
	while (flag != 0) {
		fseek(disk, 24, SEEK_CUR); 
		fread(&flag, 1, 1, disk); 
	}

	// write metadata for the file
	flag = 1;
	fwrite(&flag, 1, 1, disk);
	char name[16]; 
	strcpy(name, destination); 
	fwrite(name, 1, 16, disk); 
	printf("%s name written successfully\n");
	fwrite(&offset, sizeof(offset), 1, disk); 
	fwrite(&len_of_source_file, sizeof(len_of_source_file), 1, disk); 
	fseek(disk, offset, SEEK_SET); 

	// read a character from the source and write it to the disk
	char character;
	while (fread(&character, 1, 1, sourceptr) != 0) {
		fwrite(&character, 1, 1, disk); 
	}
	fclose(sourceptr); 
	offset = ftell(disk); 
	rewind(disk); 
	fwrite(&offset, sizeof(offset), 1, disk); 
	fclose(disk); 
}