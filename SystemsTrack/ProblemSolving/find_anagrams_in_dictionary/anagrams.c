#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define LEAFSIZE 26

typedef struct ListNode {
	char *word;
	struct ListNode *next;
} ListNode;

typedef struct TrieNode {
	struct TrieNode *children[LEAFSIZE];
	bool word_end;
	struct ListNode *words;
} Node;

int strlen_(const char *str) {
	int len = 0;
	for (; str[len] != '\0' && str[len] != '\n'; len++);
	return  len;
}

void str_lower(char *str) {
	int index = 0;
	while (str[index] != '\n' && str[index]) {
		if (str[index] >= 'A' && str[index] <= 'Z')
			str[index] = (str[index] - 'A') + 'a';
		index++;
	}
}

void sort(char *string) {
	char temp;

	int ptr, index;
	int n = strlen_(string);

	for (ptr = 0; ptr < n - 1; ptr++) {
		for (index = ptr + 1; index < n; index++) {
			if (string[ptr] > string[index]) {
				temp = string[ptr];
				string[ptr] = string[index];
				string[index] = temp;
			}
		}
	}
}

Node *get_new_node() {
	Node *new_node = (Node *)malloc(sizeof(Node));

	new_node->word_end = false;
	new_node->words = NULL;
	for (int i = 0; i < LEAFSIZE; i++)
		new_node->children[i] = NULL;

	return new_node;
}

ListNode *get_new_word(char *word) {
	ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));

	new_node->word = (char *)malloc(sizeof(char) * 50);
	int index = 0;
	while (*word != '\n' && *word) {
		new_node->word[index++] = *word++;
	}
	new_node->word[index] = '\0';

	new_node->next = NULL;
	return new_node;
}

void insert_word(Node *root, char *word, char *actual) {
	Node *ptr = root;
	int len = strlen_(word);

	for (int i = 0; i < len; i++) {
		int index = word[i] - 'a';

		if (!ptr->children[index])
			ptr->children[index] = get_new_node();

		ptr = ptr->children[index];
	}

	ptr->word_end = true;

	ListNode *new_word = get_new_word(actual);
	if (ptr->words == NULL)
		ptr->words = new_word;
	else {
		ListNode *temp = ptr->words;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_word;
	}
}

ListNode *get_anagrams(Node *root, char *word) {
	Node *ptr = root;
	int index;

	for (int i = 0; word[i]; i++) {
		index = (int)(word[i] - 'a');
		if (!ptr->children[index])
			return NULL;
		ptr = ptr->children[index];
	}
	return ptr->word_end ? ptr->words : NULL;
}


int main() {
	Node *dict_root = get_new_node();

	FILE *input = fopen("words.txt", "r");

	char line[256], actual_word[256];

	while (fgets(line, 256, input)) {

		str_lower(line);
		int index = 0;
		while (line[index] != '\n' && line[index]) {
			actual_word[index] = line[index];
			index++;
		}

		actual_word[index] = '\0';

		sort(line);
		insert_word(dict_root, line, actual_word);
	}

	char word[50];
	printf("word: ");
	scanf("%s", word);

	sort(word);

	ListNode *anagrams = get_anagrams(dict_root, word);

	if (anagrams == NULL)
		printf("NOT Found\n");
	else {
		while (anagrams != NULL) {
			printf("%s ", anagrams->word);
			anagrams = anagrams->next;
		}
	}

	return 0;
}