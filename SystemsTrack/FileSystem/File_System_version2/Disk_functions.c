#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define HARD_DISK_SIZE 13107200
#define META_DATA 6579200
#define HARD_DISK_FILE "hardDisk.hdd"
#define BLOCK_FREE_FLAG 1
#define BLOCK_SIZE 16384
#define NUM_OF_DATABLOCKS 600

struct table_record{
	char file_name[20];
	unsigned int start_block;
	unsigned int blocks_occupied;
	unsigned int file_size;
};

struct MetaData{
	unsigned int secret_key;
	unsigned int available_free_size;
	unsigned int num_of_records;
	char block_status[600];
	struct table_record table[32];
};

void read_block(unsigned int block_num, char *buffer){
	FILE *disk_ptr = fopen(HARD_DISK_FILE, "r");
	if (disk_ptr != NULL){
		unsigned int offset = block_num*BLOCK_SIZE;
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

struct MetaData *load_metadata(){
	struct MetaData *data = (struct MetaData *)malloc(sizeof(struct MetaData));
	char buffer[BLOCK_SIZE+1];
	read_block(0, buffer);
	memcpy(data, buffer, sizeof(struct MetaData));
	return data;
}

void write_metadata(struct MetaData *data){
	char buffer[BLOCK_SIZE+1];
	memcpy(buffer, data, sizeof(struct MetaData));
	write_block(0, buffer);
}

void INIT(){
	struct MetaData data;
	data.secret_key = 0x444E524D;
	data.available_free_size = HARD_DISK_SIZE - META_DATA;
	data.num_of_records = 0;
	memset(data.block_status, BLOCK_FREE_FLAG, 600);
	write_metadata(&data);
}

void check_hardDisk(){
	struct MetaData *data = load_metadata();
	if (data->secret_key != 0x444E524D){
		printf("format(y/n): ");
		char answer = fgetc(stdin);
		if (answer == 'y')
			INIT();
		else
			exit(0);
	}
	free(data);
}

void debug(){
	struct MetaData *data = load_metadata();
	int num_of_records = data->num_of_records;
	printf("Filename   | Start Block | Num of Blocks | file size  \n");
	for (int record_num = 0; record_num < num_of_records; record_num++)
		printf("%s | %u | %u | %u |\n", data->table[record_num].file_name, data->table[record_num].start_block, data->table[record_num].blocks_occupied, data->table[record_num].file_size);
	free(data);
}

void delete_file_from_disk(char *filename){
	struct MetaData *data = load_metadata();
	int num_of_files = data->num_of_records;
	for (int record_num = 0; record_num < num_of_files; record_num++){
		if (!strcmp(filename, data->table[record_num].file_name)){
			 //update available_free_size
			data->available_free_size -= data->table[record_num].file_size;

			 //update block_status
			int start_block = data->table[record_num].start_block;
			int blocks_occupied = data->table[record_num].blocks_occupied;
			for (int count = 0; count < blocks_occupied; count++)
				data->block_status[start_block++] = BLOCK_FREE_FLAG;

			 //update row with last row 
			strcpy(data->table[record_num].file_name, data->table[num_of_files - 1].file_name);
			data->table[record_num].blocks_occupied = data->table[num_of_files - 1].blocks_occupied;
			data->table[record_num].file_size = data->table[num_of_files - 1].file_size;
			data->table[record_num].start_block = data->table[num_of_files - 1].start_block;

			 //decrement the num_of_records
			data->num_of_records -= 1;
			break;
		}
	}
	write_metadata(data);
	free(data);
}

void list_all_filenames(){
	struct MetaData *data = load_metadata();
	int num_of_files = data->num_of_records;
	for (int record_num = 0; record_num < num_of_files; record_num++)
		printf("%s\n", data->table[record_num].file_name);
	printf("%d files..\n", num_of_files);
	free(data);
}

unsigned int get_offset_to_write_file(unsigned int data_size){
	unsigned int blocks_needed = data_size / BLOCK_SIZE;
	if (data_size%BLOCK_SIZE != 0)
		blocks_needed++;

	struct MetaData *data = load_metadata();
	unsigned int offset = 0, index = 0, count = 0;
	while (index < 600){
		if (data->block_status[index] == BLOCK_FREE_FLAG)
			count++;
		else
			count = 0;
		if (count == blocks_needed)
			break;
		index++;
	}
	offset = index - count + 1;
	return offset + 4;
}

void write_data(char *file_name, unsigned int block_num, unsigned int blocks_required, unsigned int data_size){
	FILE *file_ptr = fopen(file_name, "r");
	if (file_ptr != NULL){
		unsigned int data_written = 0;
		char buffer[BLOCK_SIZE + 1];
		while (data_size > BLOCK_SIZE)
		{
			fread(buffer, BLOCK_SIZE, 1, file_ptr);
			write_block(block_num, buffer);
			data_size -= BLOCK_SIZE;
			block_num++;
		}
		fread(buffer, data_size, 1, file_ptr);
		write_block(block_num, buffer);

		fclose(file_ptr);
	}
}

unsigned int get_file_size(char *file_name){
	FILE *fp = fopen(file_name,"r");
	if (fp != NULL){
		fseek(fp, 0, SEEK_END);
		unsigned int count = ftell(fp);
		return count;
		fclose(fp);
	}
	return 0;
}

void copy_to_disk(char *src_filename, char *dest_filename){
	struct MetaData *data = load_metadata();
	unsigned int data_size = get_file_size(src_filename);
	unsigned int available_free_size = data->available_free_size;
	if (data_size > available_free_size)
		printf("insufficient memory\n");
	else{
		unsigned int block_num = get_offset_to_write_file(data_size);
		if (block_num != 0){
			unsigned int blocks_needed = data_size / BLOCK_SIZE;
			if (data_size%BLOCK_SIZE != 0)
				blocks_needed++;

			// update metadata
			data->available_free_size -= data_size;
			data->num_of_records += 1;
			memset(&(data->block_status[block_num]), 0, blocks_needed);
			strcpy(data->table[data->num_of_records -1].file_name, dest_filename);
			data->table[data->num_of_records - 1].blocks_occupied = blocks_needed;
			data->table[data->num_of_records - 1].file_size = data_size;
			data->table[data->num_of_records - 1].start_block = block_num;
			write_data(src_filename, block_num, blocks_needed, data_size);

			write_metadata(data);
		}
		else
			printf("insufficient memory\n");
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
	while (data_size > BLOCK_SIZE)
	{
		read_block(block_num, buffer);
		fwrite(buffer, BLOCK_SIZE, 1, fp);
		data_size -= BLOCK_SIZE;
		block_num++;
	}
	read_block(block_num, buffer);
	fwrite(buffer, data_size, 1, fp);

	fclose(fp);
}

void copy_from_disk(char *src_filename, char *dest_filename){
	unsigned int start_block;
	unsigned int num_of_blocks;
	unsigned int data_size;
	get_attributes_of_file(src_filename, &start_block, &num_of_blocks, &data_size);
	read_data_to(dest_filename, start_block, num_of_blocks, data_size);
}
