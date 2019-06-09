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

struct node *add(struct node *head_list_1, struct node * head_list_2, int *carry){
	if (head_list_1){
		struct node *result = (struct node *)malloc(sizeof(struct node));
		result->next = add(head_list_1->next, head_list_2->next, carry);
		int sum = head_list_1->data + head_list_2->data + *carry;
		result->data = sum % 10;
		*carry = sum / 10;
		return result;
	}
	return NULL;
}

struct node *add_carry_to_remaining(struct node *result, struct node *start_point, struct node *list, int *carry){
	if (list->next != start_point)
		result = add_carry_to_remaining(result, start_point, list->next, carry);	
	int sum = list->data + *carry;
	struct node *new_node = create_node();
	new_node->data = sum % 10;
	*carry = sum / 10;
	new_node->next = result;
	return new_node;
}

struct node *add_lists(struct node *head_list_1, int size_list_1, struct node *head_list_2, int size_list_2){
	if (head_list_1 == NULL)
		return head_list_2;
	if (head_list_2 == NULL)
		return head_list_1;

	struct node *result = NULL;
	int carry=0;
	if (size_list_1 == size_list_2){
		result = add(head_list_1, head_list_2, &carry);
		if (carry){
			struct node *new_node = (struct node *)malloc(sizeof(struct node));
			new_node->data = carry;
			new_node->next = result;
			result = new_node;
		}
	}
	else{
		int diff = size_list_1 - size_list_2;
		struct node *temp;
		if (diff < 0){
			temp = head_list_1;
			head_list_1 = head_list_2;
			head_list_2 = temp;
			diff *= -1;
		}
		temp = head_list_1;
		for (int i = 0; i < diff; i++)
			temp = temp->next;

		result = add(temp, head_list_2, &carry);
		result = add_carry_to_remaining(result, temp, head_list_1, &carry);
		if (carry){
			struct node *new_node = create_node();
			new_node->data = 1;
			new_node->next = result;
			result = new_node;
		}
	}
	return result;
}



int list_length(struct node *head){
	struct node *temp = head;
	int count = 0;

	while (temp != NULL){
		count++;
		temp = temp->next;
	}

	return count;
}

void display(struct node *head){
	struct node *temp = head;
	while (temp != NULL){
		printf("%d ", temp->data);
		temp = temp->next;
	}
}

int main(){

	printf("********** LIST 1 **********\n");
	struct node *head_list_1 = create_list();
	int size_list_1 = list_length(head_list_1);

	printf("********** LIST 2 **********\n");
	struct node *head_list_2 = create_list();
	int size_list_2 = list_length(head_list_2);

	struct node *head_result = add_lists(head_list_1, size_list_1, head_list_2, size_list_2);
	display(head_result);

	system("pause");
	return 0;
}