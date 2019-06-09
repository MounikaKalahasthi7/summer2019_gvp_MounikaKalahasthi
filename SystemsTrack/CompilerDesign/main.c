#include <stdio.h>
#include "Compiler_design.h"

int main(){
	char file_name[20];
	printf("input file: ");
	gets(file_name);
	generate_address_file(file_name);
	print_file("output.txt");
	system("pause");
	return 0;
}