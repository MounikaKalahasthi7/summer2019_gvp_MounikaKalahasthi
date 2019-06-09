#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "disk_io.h"

struct table_record{
	char file_name[20];
	unsigned int file_size;
	unsigned int blocks_occupied;
	unsigned int start_block;
};

struct MetaData{
	unsigned int secret_key;
	unsigned int block_size;
	unsigned total_blocks;
	unsigned int available_free_blocks;
	unsigned int num_of_records;
	char block_status[600];
	struct table_record table[32];
};

struct MetaData *load_metadata(){
	struct MetaData *data = (struct MetaData *)malloc(sizeof(struct MetaData));
	char buffer[BLOCK_SIZE + 1];
	read_block(0, buffer);
	memcpy(data, buffer, sizeof(struct MetaData));
	return data;
}

void write_metadata(struct MetaData *data){
	char buffer[BLOCK_SIZE + 1];
	memcpy(buffer, data, sizeof(struct MetaData));
	write_block(0, buffer);
}

void INIT(){
	struct MetaData data;
	data.secret_key = 0x444E524D;
	data.available_free_blocks = 6000;
	data.num_of_records = 0;
	memset(data.block_status, BLOCK_FREE_FLAG, 600);
	write_metadata(&data);
}

unsigned int get_file_size(char *file_name){
	FILE *fp = fopen(file_name, "r");
	if (fp != NULL){
		fseek(fp, 0, SEEK_END);
		unsigned int count = ftell(fp);
		fclose(fp);
		return count - 2;
	}
	return 0;
}

void write_data(char *file_name, unsigned int *block_num, unsigned int blocks_required, unsigned int data_size){
	FILE *file_ptr = fopen(file_name, "r");
	if (file_ptr != NULL){
		char buffer[BLOCK_SIZE];
		if (blocks_required == 1){
			fread(buffer, data_size, 1, file_ptr);
			write_block(block_num[0], buffer);
		}
		else{
			memcpy(buffer, &block_num[1], (blocks_required-1)*sizeof(unsigned int));
			write_block(block_num[0], buffer);
			for (unsigned int index = 1; index < blocks_required - 1; index++){
				fread(buffer, BLOCK_SIZE, 1, file_ptr);
				write_block(block_num[index], buffer);
				data_size -= BLOCK_SIZE;
			}
			fread(buffer, data_size, 1, file_ptr);
			write_block(block_num[0], buffer);
		}
		fclose(file_ptr);
	}
}

void get_available_blocks(unsigned int *destination, char *blocks_status, unsigned int blocks_needed){
	int count = 0;
	for (int index = 4; index < 600; index++){
		if (blocks_status[index] == BLOCK_FREE_FLAG)
			destination[count++] = index;
		if (count == blocks_needed)
			break;
	}
}

void copy_to_disk(char *src_filename, char *dest_filename){
	struct MetaData *data = load_metadata();
	unsigned int data_size = get_file_size(src_filename);
	unsigned int available_free_blocks = data->available_free_blocks;
	if (data_size > available_free_blocks*BLOCK_SIZE)
		printf("insufficient memory\n");
	else{
		unsigned int blocks_needed = data_size / BLOCK_SIZE;
		if (data_size%BLOCK_SIZE != 0)
			blocks_needed++;

		unsigned int available_blocks[600];
		if (blocks_needed > 1)
			blocks_needed += 1;
		get_available_blocks(available_blocks, data->block_status, blocks_needed);

		// update metadata
		data->available_free_blocks -= blocks_needed;
		data->num_of_records += 1;
		strcpy(data->table[data->num_of_records - 1].file_name, dest_filename);
		data->table[data->num_of_records - 1].blocks_occupied = blocks_needed;
		data->table[data->num_of_records - 1].file_size = data_size;
		data->table[data->num_of_records - 1].start_block = available_blocks[0];
		for (unsigned int index = 0; index < blocks_needed; index++)
			data->block_status[available_blocks[index]] = 0;
		write_data(src_filename, available_blocks, blocks_needed, data_size);

		write_metadata(data);
	}

}

void get_attributes_of_file(char *src_filename, unsigned int *start_block, unsigned int *num_of_blocks, unsigned int *data_size){
	struct MetaData *data = load_metadata();
	int num_of_files = data->num_of_records;
	for (int record_num = 0; record_num < num_of_files; record_num++)
		if (strcmp(src_filename, data->table[record_num].file_name) == 0){
			*start_block = data->table[record_num].start_block;
			*num_of_blocks = data->table[record_num].blocks_occupied;
			*data_size = data->table[record_num].file_size;
			break;
		}
	free(data);
}

void read_data_to(char *file_name, unsigned int block_num, unsigned int blocks_required, unsigned int data_size){
	FILE *fp = fopen(file_name, "w");
	unsigned int data_written = 0;
	char buffer[BLOCK_SIZE + 1];
	if (blocks_required == 1){
		read_block(block_num, buffer);
		fwrite(buffer, data_size, 1, fp);
	}
	else{
		unsigned int blocks_list[BLOCK_SIZE];
		read_block(block_num, buffer);
		memcpy(blocks_list, buffer, (blocks_required-1)*sizeof(unsigned int));
		for (unsigned int index = 0; index < blocks_required - 1; index++){
			read_block(blocks_list[index], buffer);
			fwrite(buffer, BLOCK_SIZE, 1, fp);
			data_size -= BLOCK_SIZE;
		}
		read_block(block_num, buffer);
		fwrite(buffer, data_size, 1, fp);
	}

	fclose(fp);
}

void copy_from_disk(char *src_filename, char *dest_filename){
	unsigned int start_block;
	unsigned int num_of_blocks;
	unsigned int data_size;
	get_attributes_of_file(src_filename, &start_block, &num_of_blocks, &data_size);
	read_data_to(dest_filename, start_block, num_of_blocks, data_size);
}
