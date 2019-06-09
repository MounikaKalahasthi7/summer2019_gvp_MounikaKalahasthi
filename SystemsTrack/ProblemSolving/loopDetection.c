#include<stdio.h>
#include<stdlib.h>

struct node{
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
	struct node *head = NULL;
	int n;
	printf("no. of elements: ");
	scanf_s("%d", &n);

	if (n > 0){
		struct node *temp =create_node();
		struct node *new_node;
		int data;
		printf("data:");
		scanf_s("%d", &data);
		temp->data = data;
		head = temp;
		for (int i = 1; i < n; i++){
			new_node = create_node();
			scanf_s("%d", &data);
			new_node->data = data;
			temp->next = new_node;
			temp = new_node;
		}
	}

	return head;
}

struct node *loop_the_list(struct node *head){
	int random_number;
	printf("random node: ");
	scanf_s("%d",&random_number);
	struct node *tail = head;
	while (tail->next != NULL)
		tail = tail->next;

	struct node *temp = head;
	for (int i = 0; i < random_number; i++)
		temp = temp->next;
	if (random_number >= 0)
	tail->next = temp;
	return head;
}

struct node *detect_loop(struct node *head){
	struct node *fast_ptr = head;
	struct node *slow_ptr = head;
	
	do{
		slow_ptr = slow_ptr->next;
		if (fast_ptr->next)
			fast_ptr = fast_ptr->next->next;
	} while (fast_ptr != NULL && slow_ptr != fast_ptr);

	if (fast_ptr == NULL){
		printf("no loop\n");
		return NULL;
	}
	else{
		printf("loop detected\n");
		return slow_ptr;
	}
}

void detect_start_of_loop(struct node *head, struct node *meet){
	while (head != meet){
		head = head->next;
		meet = meet->next;
	}
	printf("\nmeet at: %d\n", head->data);
}

int main()
{
	struct node *head = create_list();

	head = loop_the_list(head);

	struct node *meet_point = detect_loop(head);
	if (meet_point)
		detect_start_of_loop(head, meet_point);

	system("pause");
	return 0;
}