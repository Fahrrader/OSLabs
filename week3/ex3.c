#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

typedef struct LinkedList {
	Node *head;
	int length;
} LinkedList;

void print_list(LinkedList *list) {
	Node *node = list->head;
	while (node != NULL) {
		printf("%d\n", node->data);
		node = node->next;
	}
}
	
void insert_node(LinkedList *list, int data) {
	Node *temp = malloc(sizeof(Node)), *p, *head = list->head;
	temp->data = data;
	temp->next = NULL;
	//printf("len %i\n", list->length);
	if (list->length == 0) {
		head = temp;
	} else {
		p = head;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = temp;
	}
	list->length++;
}
	
void delete_node(LinkedList *list, int index) {
	Node *node = list->head;
	Node *prev = list->head;
	int i = 0;
	
	while (node->next != NULL && i < index) {
		prev = node;
		node = node->next;
		i++;
	}
	
	if (i < index) {
		printf("Oops! Sorry, no such element exists.\n");
		return;
	}
	
	prev->next = node->next;
	free(node);
	list->length--;
}

int main() {
	LinkedList *ll = malloc(sizeof(LinkedList));
	ll->length = 0;
	scanf("%i");
	
	return 0;
}