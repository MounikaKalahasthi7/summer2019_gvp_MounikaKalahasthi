#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void print_file(FILE *fp){
	char *num = (char *)malloc(10);
	num = fgets(num, 9, fp);
	while (num){
		printf("%s", num);
		num = fgets(num, 9, fp);
	}
}

void file_copy(char *file_1, char *file_2){
	FILE *source; fopen_s(&source, file_1, "r");
	FILE *dest; fopen_s(&dest, file_2, "w");
	char ch = fgetc(source);
	while (ch != EOF){
		fputc(ch, dest);
		ch = fgetc(source);
	}
	fclose(source);
	fclose(dest);
}

void insert(char *number, char *file_1, char *file_2){
	FILE *output; fopen_s(&output, file_1, "w");
	FILE *temp; fopen_s(&temp, file_2, "r");

	char *read_number = (char *)malloc(10);
	read_number = fgets(read_number, 10, temp);
	while (read_number!=NULL && strcmp(read_number, number) < 0){
		fputs(read_number, output);
		read_number = fgets(read_number, 10, temp);
	}
	fputs(number, output);
	while (read_number){
		fputs(read_number, output);
		read_number = fgets(read_number, 10, temp);
	}

	fclose(output);
	fclose(temp);
}

void sort_same_size(FILE *inp_file){
	char *number = (char *)malloc(10);
	number = fgets(number, 9, inp_file);
	while (number != NULL){
		file_copy("dummy_1.txt", "dummy_2.txt");
		insert(number, "dummy_1.txt", "dummy_2.txt");
		number = fgets(number, 9, inp_file);
	}
}

void split_into_digit_files(char *file_name){
	FILE *inp_file; fopen_s(&inp_file, file_name, "r" );
	char *number = (char *)malloc(10);
	number = fgets(number, 10, inp_file);

	while (number != NULL){
		int length = strlen(number)-1;
		switch (length){
		case 1: file_copy("digit_1.txt", "temp.txt");
				insert(number, "digit_1.txt", "temp.txt"); break;
		case 2: file_copy("digit_2.txt", "temp.txt");
				insert(number, "digit_2.txt", "temp.txt"); break;
		case 3:	file_copy("digit_3.txt", "temp.txt");
				insert(number, "digit_3.txt", "temp.txt"); break;
		case 4:	file_copy("digit_4.txt", "temp.txt");
				insert(number, "digit_4.txt", "temp.txt"); break;
		case 5:	file_copy("digit_5.txt", "temp.txt");
				insert(number, "digit_5.txt", "temp.txt"); break;
		case 6:	file_copy("digit_6.txt", "temp.txt");
				insert(number, "digit_6.txt", "temp.txt"); break;
		case 7:	file_copy("digit_7.txt", "temp.txt");
				insert(number, "digit_7.txt", "temp.txt"); break;
		}
		number = fgets(number, 10, inp_file);
	}

	fclose(inp_file);

}

void append_files(char *source, char *dest){
	FILE *dest_ptr;
	fopen_s(&dest_ptr, dest, "r");
	FILE *source_ptr;
	fopen_s(&source_ptr, source, "a");
	char ch;

	if (source_ptr != NULL){
		ch = fgetc(source_ptr);
		while (ch != EOF){
			fputc(ch, dest_ptr);
			ch = fgetc(source_ptr);
		}
		fclose(source_ptr);
	}
	fclose(dest_ptr);
}

void append_all_digit_files(){
	append_files("digit_1.txt", "output.txt");
	append_files("digit_2.txt", "output.txt");
	append_files("digit_3.txt", "output.txt");
	append_files("digit_4.txt", "output.txt");
	append_files("digit_5.txt", "output.txt");
	append_files("digit_6.txt", "output.txt");
	append_files("digit_7.txt", "output.txt");
}

void sort_file(char *inp_file){
	FILE *temp;

	// create empty files
	fopen_s(&temp, "digit_1.txt", "w"); fclose(temp);
	fopen_s(&temp, "digit_2.txt", "w"); fclose(temp);
	fopen_s(&temp, "digit_3.txt", "w"); fclose(temp);
	fopen_s(&temp, "digit_4.txt", "w"); fclose(temp);
	fopen_s(&temp, "digit_5.txt", "w"); fclose(temp);
	fopen_s(&temp, "digit_6.txt", "w"); fclose(temp);
	fopen_s(&temp, "digit_7.txt", "w"); fclose(temp);

	split_into_digit_files(inp_file);
	append_all_digit_files();
}

int main(){
	sort_file("num_inp.txt");
	FILE *output;	fopen_s(&output, "output.txt", "r");
	print_file(output);
	_fcloseall();
	system("pause");
	return 0;
}