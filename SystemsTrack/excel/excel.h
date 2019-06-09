#pragma once
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10

typedef struct command {
	int val;
	int type;
	char *cell;
	char *expression;
	char *file_name;
}Command;

typedef struct cell {
	int data;
	char *string_data;
	char *expression;
}Cell;

int precedence(char op);

int apply_operator(int a, int b, char op);

int is_digit(char c);

int is_number(const char *str);

int is_operator(char c);

int str_length(const char *str);

int str_to_number(const char *str);

int digit_count(int num);

char *number_to_str(int num);

void str_upper(char *token);

int str_compare(const char *str1, const char *str2);

int evaluate_infix(char *tokens);

int evaluate(char *expression, Cell **sheet);
