#pragma once
#define HARD_DISK_SIZE 13107200
#define META_DATA 6579200
#define HARD_DISK_FILE "hardDisk.hdd"
#define BLOCK_FREE_FLAG 1
#define BLOCK_SIZE 16384
#define NUM_OF_DATABLOCKS 600


void read_block(unsigned int block_num, char *buffer);
void write_block(unsigned int block_num, char *buffer);
void initialize(unsigned int block_size);