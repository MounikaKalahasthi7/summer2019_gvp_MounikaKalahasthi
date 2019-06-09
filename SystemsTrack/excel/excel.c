#include "excel.h"

int GET(char *cell, Cell **sheet);

int precedence(char op){
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/' || op == '%')
		return 2;
	return 0;
}

int apply_operator(int a, int b, char op){
	switch (op){
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;
	case '%': return a % b;
	}
}

int is_digit(char c) {
	if (c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}

int is_number(const char *str) {
	for (int i = 0; str[i]; i++) {
		if (!is_digit(str[i]))
			return 0;
	}
	return 1;
}

int is_operator(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '(' || c == ')')
		return 1;
	else
		return 0;
}

int str_length(const char *str) {
	int len = 0;
	for (; str[len] != '\0'; len++);
	return len;
}

int str_to_number(const char *str) {
	int num = 0, index = 0;

	while (str[index]) {
		num *= 10;
		num += (int)(str[index] - '0');
		index++;
	}
	return num;
}

int digit_count(int num) {
	if (num == 0)
		return 1;

	int count = 0;
	while (num > 0) {
		count++;
		num /= 10;
	}

	return count;
}

char *number_to_str(int num) {
	int len = digit_count(num);
	char *result = (char *)malloc(sizeof(char) * (len + 1));

	result[len] = '\0';
	len--;
	while (len >= 0) {
		result[len] = (char)((num % 10) + '0');
		num /= 10;
		len--;
	}
	return result;
}

void str_upper(char *token) {
	for (int i = 0; token[i]; i++) {
		if (token[i] >= 'a' && token[i] <= 'z')
			token[i] = token[i] - 'a' + 'A';
	}
}

int str_compare(const char *str1, const char *str2) {
	int index = 0;

	for (; str1[index] && str2[index]; index++) {
		if (str1[index] != str2[index])
			return 0;
	}

	if (!str1[index] && !str2[index])
		return 1;
	return 0;
}

int evaluate_infix(char *tokens) {
	int values[20], values_top = -1, ops_top = -1;
	char ops[20];

	int len = str_length(tokens);
	int i, val1, val2;
	for (i = 0; i < len; i++) {
		if (tokens[i] == '(')
			ops[++ops_top] = tokens[i];
		else if (is_digit(tokens[i])) {
			int val = 0;

			while (i < len && is_digit(tokens[i])) {
				val *= 10;
				val += (int)(tokens[i] - '0');
				i++;
			}
			i--;
			values[++values_top] = val;
		}
		else if (tokens[i] == ')') {
			while (ops_top != -1 && ops[ops_top] != '(') {
				char op = ops[ops_top--];
				val1 = values[values_top--];
				val2 = values[values_top--];
				values[++values_top] = apply_operator(val1, val2, op);
			}
			ops_top--;
		}
		else {
			if (tokens[i] == '-' && ops[ops_top] == '(')
				values[++values_top] = 0;

			while (ops_top != -1 && precedence(ops[ops_top]) >= precedence(tokens[i])) {
				char op = ops[ops_top--];
				val1 = values[values_top--];
				val2 = values_top == -1 ? 0 : values[values_top--];
				values[++values_top] = apply_operator(val1, val2, op);
			}
			ops[++ops_top] = tokens[i];
		}
	}

	while (ops_top != -1) {
		char op = ops[ops_top--];
		val1 = values[values_top--];
		val2 = values_top == -1 ? 0 : values[values_top--];
		values[++values_top] = apply_operator(val1, val2, op);
	}

	return values[values_top];
}

int evaluate(char *expression, Cell **sheet) {
	char *infix = (char *)malloc(sizeof(char) * 20);
	char cell[10];
	int index = 0;

	while (*expression) {
		while (is_operator(*expression))
			infix[index++] = *expression++;

		if (!*expression)
			break;

		int cell_index = 0;
		while (!is_operator(*expression) && *expression)
			cell[cell_index++] = *expression++;

		cell[cell_index] = '\0';

		char *append = !is_number(cell) ? number_to_str(GET(cell, sheet)) : cell;

		while (*append)
			infix[index++] = *append++;
	}
	infix[index] = '\0';

	return evaluate_infix(infix);
}
