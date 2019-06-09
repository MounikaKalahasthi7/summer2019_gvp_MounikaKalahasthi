#include<stdio.h>
#include<stdlib.h>
#include "disk_io.h"
//static char HARD_DISK_FILE[30];
//static unsigned BLOCK_SIZE;

void read_block(unsigned int block_num, char *buffer){
	FILE *disk_ptr = fopen(HARD_DISK_FILE, "r");
	if (disk_ptr != NULL){
		unsigned int offset = (block_num)*BLOCK_SIZE;
		fseek(disk_ptr, offset, SEEK_CUR);
		fread(buffer, BLOCK_SIZE, 1, disk_ptr);
		fclose(disk_ptr);
	}
	else
		exit(0);
}

void write_block(unsigned int block_num, char *buffer){
	FILE *disk_ptr = fopen(HARD_DISK_FILE, "r+");
	if (disk_ptr != NULL){
		unsigned int offset = block_num*BLOCK_SIZE;
		fseek(disk_ptr, offset, SEEK_CUR);
		fwrite(buffer, BLOCK_SIZE, 1, disk_ptr);
		fclose(disk_ptr);
	}
	else
		exit(0);
}

//unsigned int initialize(unsigned int block_size, char *diskname){
//	int index;
//	for (index = 0; diskname[index] != '\0'; index++)
//		HARD_DISK_FILE[index] = diskname[index];
//	BLOCK_SIZE = block_size;
//}