#pragma once
void read_block(unsigned int block_num, char *buffer);
void write_block(unsigned int block_num, char *buffer);
struct MetaData *load_metadata();
void write_metadata(struct MetaData *data);
void INIT();
void check_hardDisk();
void debug();
void delete_file_from_disk(char *filename);
void list_all_filenames();
unsigned int get_offset_to_write_file(unsigned int data_size);
void write_data(char *file_name, unsigned int block_num, unsigned int blocks_required, unsigned int data_size);
unsigned int get_file_size(char *file_name);
void copy_to_disk(char *src_filename, char *dest_filename);
void get_attributes_of_file(char *src_filename, unsigned int *start_block, unsigned int *num_of_blocks, unsigned int *data_size);
void read_data_to(char *file_name, unsigned int block_num, unsigned int blocks_required, unsigned int data_size);
void copy_from_disk(char *src_filename, char *dest_filename);