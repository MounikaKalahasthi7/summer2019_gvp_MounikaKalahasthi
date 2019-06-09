#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"Compiler_design.h"

struct stack Stack;
struct const_table Const_table;
struct symbol_table Symbol_table;
struct label_table Label_table;
struct icode_table Icode_table;

unsigned int get_number_of_operands(unsigned int opcode){
	switch (opcode){
	case 1:
	case 2: return 2;
	case 3:
	case 4:
	case 5: return 3;
	case 6: return 1;
	case 7: return 4;
	case 8:
	case 9:
	case 10:
	case 11:
	case 12: return 2;
	case 13:
	case 14:return 1;
	}
	return -1;
}

void create_record(unsigned int line_num, unsigned int opcode, unsigned int *operands){
	Icode_table.record[Icode_table.table_size].line_num = line_num;
	Icode_table.record[Icode_table.table_size].opcode = opcode;
	unsigned int num_of_operands = get_number_of_operands(opcode);
	for (unsigned int index = 0; index < num_of_operands; index++)
		Icode_table.record[Icode_table.table_size].operands[index] = operands[index];

	Icode_table.table_size++;
}

unsigned int search_record(unsigned int line_num){
	for (unsigned int index = 0; index < Icode_table.table_size; index++)
		if (Icode_table.record[index].line_num == line_num)
			return index;
	return -1;
}

void create_label_record(char *label_name, unsigned line_num){
	strcpy(Label_table.table[Label_table.table_size].label_name, label_name);
	Label_table.table[Label_table.table_size].line_num = line_num;
	Label_table.table_size++;
}

unsigned int search_label_record(char *label_name){
	for (unsigned int index = 0; index < Label_table.table_size; index++)
		if (strcmp(Label_table.table[Label_table.table_size].label_name, label_name) == 0)
			return Label_table.table[index].line_num;
	return -1;
}

void create_symbol_record(char *operand, int size){
	unsigned int address = 0;
	for (int index = 0; index < Symbol_table.table_size; index++)
		address += Symbol_table.record[index].size;

	Symbol_table.record[Symbol_table.table_size].size = size;
	Symbol_table.record[Symbol_table.table_size].reference = address;
	strcpy(Symbol_table.record[Symbol_table.table_size].operand, operand);
	Symbol_table.table_size += 1;
}

unsigned int search_symbol_record(char *operand){
	char *token = strtok(operand, "[\n");
	if (strcmp(operand, token) == 0)
		for (int index = 0; index < Symbol_table.table_size; index++){
			if (strcmp(operand, Symbol_table.record[index].operand) == 0)
				return Symbol_table.record[index].reference;
		}
	else{
		char *index = strtok(NULL, "]");
		unsigned int result = atoi(index);
		for (int index = 0; index < Symbol_table.table_size; index++){
			if (strcmp(token, Symbol_table.record[index].operand) == 0)
				result += Symbol_table.record[index].reference;
		}
	}
	return -1;
}

void create_const_record(char *const_name, unsigned int value){
	strcpy(Const_table.record[Const_table.table_size].const_name, const_name);
	Const_table.record[Const_table.table_size].value = value;
	Const_table.table_size++;
}

unsigned search_const_record(char *const_name){
	for (unsigned int index = 0; index < Const_table.table_size; index++)
		if (strcmp(Const_table.record[index].const_name, const_name) == 0)
			return Const_table.record[index].value;
	return 0;
}

void push_into_stack(unsigned int line_num){
	Stack.data[++Stack.top] = line_num;
}

unsigned int pop_from_stack(){
	return Stack.data[Stack.top--];
}

void Initialise_tables(){
	Icode_table.table_size = 0;
	Label_table.table_size = 0;
	Symbol_table.table_size = 0;
	Const_table.table_size = 0;
	Stack.top = -1;
}

void print_const_table(){
	printf("const table..\n");
	for (unsigned int index = 0; index < Const_table.table_size; index++)
		printf("%s %d\n", Const_table.record[index].const_name, Const_table.record[index].value);
}

void print_symbol_table(){
	printf("symbol table..\n");
	for (int index = 0; index < Symbol_table.table_size; index++)
		printf("%s %d %d\n", Symbol_table.record[index].operand, Symbol_table.record[index].reference, Symbol_table.record[index].size);
}

void print_icode_table(){
	printf("icode table..\n");
	for (unsigned int index = 0; index < Icode_table.table_size; index++){
		printf("%d %d ", Icode_table.record[index].line_num, Icode_table.record[index].opcode);
		unsigned int num_of_ops = get_number_of_operands(Icode_table.record[index].opcode);
		for (unsigned int arg_index = 0; arg_index < num_of_ops; arg_index++)
			printf("%d ", Icode_table.record[index].operands[arg_index]);
		printf("\n");
	}
}

int get_opcode(char *token){
	_strlwr(token);
	if (strcmp(token, "mov") == 0)
		return 1;
	if (strcmp(token, "add") == 0)
		return 3;
	if (strcmp(token, "sub") == 0)
		return 4;
	if (strcmp(token, "mul") == 0)
		return 5;
	if (strcmp(token, "jmp") == 0 || strcmp(token, "else") == 0)
		return 6;
	if (strcmp(token, "if") == 0)
		return 7;
	if (strcmp(token, "eq") == 0)
		return 8;
	if (strcmp(token, "lt") == 0)
		return 9;
	if (strcmp(token, "gt") == 0)
		return 10;
	if (strcmp(token, "lteq") == 0)
		return 11;
	if (strcmp(token, "gteq") == 0)
		return 12;
	if (strcmp(token, "print") == 0)
		return 13;
	if (strcmp(token, "read") == 0)
		return 14;
	return -1;
}

unsigned int get_index_of_register(char *regd){
	if (strcmp(regd, "AX") == 0)
		return 0;
	if (strcmp(regd, "BX") == 0)
		return 1;
	if (strcmp(regd, "CX") == 0)
		return 2;
	if (strcmp(regd, "DX") == 0)
		return 3;
	if (strcmp(regd, "EX") == 0)
		return 4;
	if (strcmp(regd, "FX") == 0)
		return 5;
	if (strcmp(regd, "GX") == 0)
		return 6;
	if (strcmp(regd, "HX") == 0)
		return 7;
	return -1;
}

unsigned int load_data_from_file(char *file_name){
	FILE *inp_file_ptr = fopen(file_name, "r");
	if (inp_file_ptr == NULL)
		return 0;
	char line[30];
	while (fgets(line, 30, inp_file_ptr)){
		char *token = strtok(line, " \n");
		if (strcmp(token, "START:") == 0)
			break;
		if (strcmp(token, "CONST") == 0){
			token = strtok(NULL, " =");
			char *temp = strtok(NULL, " =\n");
			unsigned int value = atoi(temp);
			create_const_record(token, value);
			create_symbol_record(token, 0);
		}
		else{
			token = strtok(NULL, "[\n");
			unsigned int size = 1;
			char *temp = strtok(NULL, "\n");
			if (temp != NULL)
				size = atoi(temp);
			create_symbol_record(token, size);
		}
	}
	unsigned int offset = ftell(inp_file_ptr);
	fclose(inp_file_ptr);
	print_const_table();
	print_symbol_table();
	return offset;
}

int islabel(char *token){
	char *temp = strrchr(token, ':');
	if (temp[0] == ':')
		return 1;
	return 0;
}

void load_code(char *file_name, unsigned int offset){
	FILE *inp_file_ptr = fopen(file_name, "r");
	if (inp_file_ptr == NULL)
		return;
	fseek(inp_file_ptr, offset, SEEK_CUR);
	char line[30];
	unsigned int line_num = 1;
	while (fgets(line, 30, inp_file_ptr) != NULL){
		char temp[30];
		strcpy(temp, line);
		char *operation = strtok(temp, " ");
		if (strcmp(operation, "END\n") == 0)
			break;
		if (isLabel(operation))
			create_label_record(operation, line_num);
		else{
			unsigned int opcode = get_opcode(operation);
			char *argument = strtok(NULL, " ,\n");
			if (strcmp(operation, "mov") == 0 && argument[1] == 'X')
				opcode = 2;

			unsigned int num_operands = get_number_of_operands(opcode);
			unsigned int operands[5];
			if (strcmp(operation, "if")==0){
				unsigned int index;
				for (index = 0; index < num_operands - 1; index++){
					if (argument != NULL){
						if (argument[1] == 'X')
							operands[index] = get_index_of_register(argument);
						else
							operands[index] = search_symbol_record(argument);
					}
					argument = strtok(NULL, " ,\n");
				}
				create_record(line_num, opcode, operands);
			}
			else if (strcmp(operation, "else")==0){
				unsigned int prev_addrs = pop_from_stack();
				unsigned int prev_index = search_record(prev_addrs);
				unsigned num_operands = get_number_of_operands(Icode_table.record[prev_index].opcode);
				Icode_table.record[prev_index].operands[num_operands - 1] = line_num;
				create_record(line_num, opcode, operands);
			}
			else if (strcmp(operation, "endif")==0){
				unsigned int prev_addrs = pop_from_stack();
				unsigned int prev_index = search_record(prev_addrs);
				unsigned num_operands = get_number_of_operands(Icode_table.record[prev_index].opcode);
				Icode_table.record[prev_index].operands[num_operands - 1] = line_num;
			}
			else if (strcmp(operation, "jmp")==0){
				char *label = strtok(NULL, " \n");
				unsigned int block_ddress = search_label_record(label);
				operands[0] = block_ddress;
				create_record(line_num, opcode, operands);
			}
			else{
				unsigned int index;
				for (index = 0; index < num_operands - 1; index++){
					if (argument != NULL){
						if (argument[1] == 'X')
							operands[index] = get_index_of_register(argument);
						else
							operands[index] = search_symbol_record(argument);
					}
					argument = strtok(NULL, " ,\n");
				}
				if (num_operands > 0){
					char *last_arg = strrchr(line, ' ');
					last_arg += 1;
					last_arg[2] = '\0';
					if (last_arg[1] == 'X')
						operands[index] = get_index_of_register(last_arg);
					else
						operands[index] = search_symbol_record(last_arg);
				}
				create_record(line_num, opcode, operands);
			}
		}
		line_num++;
	}
	fclose(inp_file_ptr);
	print_icode_table();
}

void write_to_output_file(){
	FILE *fp = fopen("output.txt", "w");
	for (unsigned int index = 0; index < Icode_table.table_size; index++){
		unsigned int args = get_number_of_operands(Icode_table.record[index].opcode);
		fprintf(fp, "%d %d ",Icode_table.record[index].line_num, Icode_table.record[index].opcode);
		for (unsigned int op_index = 0; op_index < args; op_index++)
			fprintf(fp, "%d ", Icode_table.record[index].operands[op_index]);
		fprintf(fp, "\n");
	}
	fclose(fp);
}

void generate_address_file(char *inp_file_name){
	Initialise_tables();
	unsigned int offset = load_data_from_file(inp_file_name);
	load_code(inp_file_name, offset);
	write_to_output_file();
}

void print_file(char *file_name){
	FILE *file_ptr = fopen(file_name, "r");
	if (file_ptr != NULL){
		char string[30];
		while (fgets(string, 30, file_ptr) != NULL){
			printf("%s", string);
		}
		fclose(file_ptr);
	}
}
