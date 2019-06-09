#ifndef _FILESYSTEM_LEVEL_H
#define _FILESYSTEM_LEVEL_H

#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 1024
#define HARD_DISK "hardDisk.hdd"

#include <stdio.h>

int findSize(char*);

int canFit(char*, char*);

void copyToDisk(char*, char*);

void format();

void listallfilenames();

void reading_metadata(char *filename, int *offset, int *length);

FILE* f_open(char *filename, char *mode);

void write_to_file(char *destination_file, unsigned int offset, unsigned int length);

void copy_from_disk(char *source_file, char *destination_file);

#endif _FILESYSTEM_LEVEL_H
