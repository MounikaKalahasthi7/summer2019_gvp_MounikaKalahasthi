#include<stdio.h>
#include<stdlib.h>
#define CRT_SECURE_NO_WARNINGS

struct node
{
	int data;
	struct node *next;
};

struct node *create_node()
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->data = 0;
	temp->next = NULL;

	return temp;
}

struct node *create_list()
{
	int size, data;
	printf("no. of nodes: ");
	scanf_s("%d", &size);

	struct node *head = NULL;
	if (size > 0){
		printf("elements: ");
		struct node *temp = create_node();
		scanf_s("%d", &data);
		temp->data = data;
		head = temp;

		struct node *new_node;
		for (int i = 1; i < size; i++){
			new_node = create_node();
			scanf_s("%d", &data);
			new_node->data = data;
			temp->next = new_node;
			temp = new_node;
		}
	}
	return head;
}

void display(struct node *head){
	while (head){
		printf("%d ", head->data);
		head = head->next;
	}
}

struct node *reverse(struct node *current, struct node *prev, struct node *next){
	if (next){
		current->next = prev;
		return reverse(next, current, next->next);
	}

	current->next = prev;
	return current;
}

int main(){
	struct node *head = create_list();
	printf("original: "); display(head);
	head = reverse(head, NULL, head->next);
	printf("\nreversed: "); display(head);
	system("pause");
	return 0;
}