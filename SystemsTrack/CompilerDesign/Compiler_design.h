#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stack{
	int data[30];
	int top;
};

struct const_table_record{
	char const_name[10];
	unsigned int value;
};

struct const_table{
	struct const_table_record record[10];
	unsigned int table_size;
};

struct symbol_table_record{
	char operand[5];
	unsigned int reference;
	unsigned int size;
};

struct symbol_table{
	struct symbol_table_record record[20];
	int table_size;
};

struct label_table_record{
	char label_name[10];
	unsigned int line_num;
};

struct label_table{
	struct label_table_record table[10];
	unsigned int table_size;
};

struct icode_table_record{
	unsigned int line_num;
	unsigned int opcode;
	unsigned int operands[5];
};

struct icode_table{
	struct icode_table_record record[30];
	unsigned int table_size;
};

unsigned int get_number_of_operands(unsigned int opcode);

void create_record(unsigned int line_num, unsigned int opcode, unsigned int *operands);

unsigned int search_record(unsigned int line_num);

void create_label_record(char *label_name, unsigned line_num);

unsigned int search_label_record(char *label_name);

void create_symbol_record(char *operand, int size);

unsigned int search_symbol_record(char *operand);

void create_const_record(char *const_name, unsigned int value);

unsigned search_const_record(char *const_name);

void push_into_stack(unsigned int line_num);

unsigned int pop_from_stack();

void Initialise_tables();

void print_const_table();

void print_symbol_table();

void print_icode_table();

int get_opcode(char *token);

unsigned int get_index_of_register(char *regd);

unsigned int load_data_from_file(char *file_name);

void load_code(char *file_name, unsigned int offset);

void write_to_output_file();

void generate_address_file(char *inp_file_name);

void print_file(char *file_name);
