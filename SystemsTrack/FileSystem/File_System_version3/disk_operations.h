#include "disk_io.h"

struct MetaData *load_metadata();
void INIT();
void write_metadata(struct MetaData *data);
unsigned int get_file_size(char *file_name);
void write_data(char *file_name, unsigned int *block_num, unsigned int blocks_required, unsigned int data_size);
void get_available_blocks(unsigned int *destination, char *blocks_status, unsigned int blocks_needed);
void copy_to_disk(char *src_filename, char *dest_filename);
void get_attributes_of_file(char *src_filename, unsigned int *start_block, unsigned int *num_of_blocks, unsigned int *data_size);
void read_data_to(char *file_name, unsigned int block_num, unsigned int blocks_required, unsigned int data_size);
void copy_from_disk(char *src_filename, char *dest_filename);