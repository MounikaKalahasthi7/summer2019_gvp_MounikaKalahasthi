#include<stdio.h>
#include<stdlib.h>


/*
complete mergesort()
*/
struct node{
	int data;
	struct node *previous;
	struct node *next;
};

struct node *create_node(){
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	new_node->data = 0;
	new_node->previous = NULL;
	new_node->next = NULL;

	return new_node;
}

struct node *create_list(){
	struct node *head = NULL;
	int size;
	printf("no. of elements: ");
	scanf_s("%d", &size);
	if (size > 0){
		printf("elements: ");
		struct node *tail = create_node();
		scanf_s("%d", &(tail->data));
		head = tail;
		struct node *new_node;
		for (int i = 1; i < size; i++){
			new_node = create_node();
			scanf_s("%d", &(new_node->data));
			new_node->previous = tail;
			tail->next = new_node;
			tail = new_node;
		}
	}

	return head;
}

void insert_node_after(struct node *previous_node, struct node *current_node){
	if (previous_node->next == current_node)
		return;
	if (current_node->next)
	current_node->next->previous = NULL;
	current_node->next = previous_node->next;
	if (previous_node->next)
		previous_node->next->previous = current_node;

	previous_node->next = current_node;
	current_node->previous = previous_node;
}

void swap(struct node *node_1, struct node *node_2){
	node_1->previous->next = node_2;
	node_1->next->previous = node_2;

	node_2->previous->next = node_1;
	node_2->next->previous = node_1;

	struct node *temp = node_1;
	node_1->next = node_2->next;
	node_1->previous = node_2->previous;

	node_2->next = temp->next;
	node_2->previous = temp->previous;
}

void display(struct node *head){
	while (head != NULL){
		printf("%d ", head->data);
		head = head->next;
	}
}

struct node *find_tail(struct node *head){
	while (head->next != NULL)
		head = head->next;
	return head;
}

void *find_partition(struct node *head, struct node *tail){
	struct node *forward = head;
	struct node *backward = tail;
	while (forward != backward && forward->next != backward)
	{
		forward = forward->next;
		backward = backward->previous;
	}

	return forward;
}

struct node *merge(struct node *list_1, struct node *list_2){
	struct node *result;
	if (list_1->data < list_2->data){
		result = list_1;
		list_1 = list_1->next;
	}
	else{
		result = list_2;
		list_2 = list_2->next;
	}
	struct node *result_head = result;

	while (list_1 != NULL && list_2 != NULL){
		if (list_1->data < list_2->data){
			if (list_1->next){
				list_1 = list_1->next;
				insert_node_after(result, list_1->previous);
			}
			else{
				insert_node_after(result, list_1);
				list_1 = NULL;
			}
		}
		else{
			if (list_2->next)
			{
				list_2 = list_2->next;
				insert_node_after(result, list_2->previous);
			}
			else{
				insert_node_after(result, list_2);
				list_2 = NULL;
			}
		}
		result = result->next;
	}

	while (list_1){
		if (list_1->next){
			list_1 = list_1->next;
			insert_node_after(result, list_1->previous);
		}
		else{
			insert_node_after(result, list_1);
			list_1 = list_1->next;
		}
		result = result->next;
	}

	while (list_2){
		if (list_2->next)
		{
			list_2 = list_2->next;
			insert_node_after(result, list_2->previous);
		}
		else{
			insert_node_after(result, list_2);
			list_2 = list_2->next;
		}
		result = result->next;
	}

	return result_head;
}

struct node *merge_sort(struct node *head, struct node *tail){
	if (head->next){
		struct node *mid = find_partition(head, tail);
		struct node *mid_next = mid->next;
		mid->next->previous = NULL;
		mid->next = NULL;
		struct node *left_sorted = merge_sort(head, mid);
		struct node *right_sorted = merge_sort(mid_next, tail);
		return merge(left_sorted, right_sorted);
	}
	return head;
}

int main(){

	struct node *head = create_list();
	struct node *tail = find_tail(head);
	head = merge_sort(head,tail);
	display(head);
	system("pause");
	return 0;
}