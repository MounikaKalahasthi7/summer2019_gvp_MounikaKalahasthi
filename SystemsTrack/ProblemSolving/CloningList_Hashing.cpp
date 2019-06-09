#include<stdio.h>
#include<stdlib.h>
#include<map>

using namespace std;

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

struct node *create_list()
{
	struct node *head = NULL;
	int n;
	printf("no. of elements: ");
	scanf_s("%d", &n);

	if (n > 0){
		struct node *temp = create_node();
		struct node *temp1;
		printf("elements: ");
		int data;
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

struct node *clone_list(struct node *head){
	struct node *parent = head;
	struct node *child = NULL;
	struct node *child_tail=NULL;
	struct node *new_node;

	std::map<struct node*, struct node*> map_obj;
	//create child list and map them
	while (parent != NULL){
		new_node = create_node();
		new_node->data = parent->data;
		map_obj.insert({parent, new_node});
		if (child_tail == NULL){
			child_tail = new_node;
			child = new_node;
		}
		else{
			child_tail->next = new_node;
			child_tail = new_node;
		}
		parent = parent->next;
	}

	for (auto &val : map_obj){
		if (val.first->random){
			std::map<struct node*, struct node*>::iterator iter;
			iter = map_obj.find(val.first->random);
			val.second->random = iter->second;
		}
	}

	return child;
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

int main()
{
	struct node *head = create_list();

	randomize_list(head);

	struct node *output = clone_list(head);
	display(head);
	system("pause");
	return 0;
}
