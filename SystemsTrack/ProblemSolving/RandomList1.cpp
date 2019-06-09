#include<stdio.h>
#include<stdlib.h>

struct node{
	int data;
	struct node *next;
	struct node *random;
};

struct node *create_node()
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->data = 0;
	temp->next = NULL;
	temp->random = NULL;
	return temp;
}

struct node *clone_list(struct node *head){

	struct node *temp = head;

	// inserting in middle
	while (temp != NULL){
		struct node *temp_clone = create_node();
		temp_clone->next = temp->next;
		temp->next = temp_clone;
		temp = temp->next->next;
	}

	// cloning random pointers
	temp = head;
	while (temp != NULL){
		struct node *parent = temp;
		struct node *child = temp->next;
		temp = temp->next->next;
		if (parent->random != NULL)
			child->random = parent->random->next;
	}

	// separating both parent and childs
	temp = head;
	head = head->next;
	while (temp != NULL){
		struct node *parent = temp;
		struct node *child = temp->next;
		temp = temp->next->next;

		parent->next = child->next;
		child->next = parent->next;
	}

	return head;
}

struct node *create_list()
{
	struct node *head = NULL;
	int n;
	printf("no. of elements: ");
	scanf_s("%d", &n);
	
	if (n > 0){
		struct node *temp = create_node();
		struct node *temp1;
		int data;
		printf("data:");
		scanf_s("%d", &data);
		temp->data = data;
		head = temp;
		for (int i = 1; i < n; i++){
			temp1 = create_node();
			scanf_s("%d", &data);
			temp1->data = data;
			temp->next = temp1;
			temp = temp1;
		}
	}

	return head;
}

void display(struct node *head){
	int count = 1;
	while (head != NULL)
	{
		printf("node_%d ", count++);

		if (head->next)
			printf("next: %d ", head->next->data);
		else
			printf("next: no data ");

		if (head->random)
			printf("random: %d\n", head->random->data);
		else
			printf("random: no data\n");
		head = head->next;
	}
}


void randomize_list(struct node *head){
	head->random = head->next->next;
	head->next->random = head->next->next->next->next;
	head->next->next->random = head->next;
	head->next->next->next->next->random = head->next->next->next->next->next;
	head->next->next->next->next->next->random = head->next->next->next->next;
}

int main()
{
	struct node *head = create_list();

	randomize_list(head);

	struct node *output = clone_list(head);
	display(output);
	system("pause");
	return 0;
}