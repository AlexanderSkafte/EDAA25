#include <stdio.h>
#include <stdlib.h>

void* xmalloc(size_t size)
{
	void*	ptr = malloc(size);

	if (ptr == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(1);
	}
	return ptr;
}

/*
 * Linked list
 */

typedef struct list_t list_t;
typedef struct node_t node_t;

struct list_t {
	node_t*		first;
	node_t*		last;
};

struct node_t {
	node_t* 	next;
	void*		data;
};

list_t* new_list(void)
{
	list_t*		head;

	head 		= xmalloc(sizeof(list_t));
	head->first	= NULL;
	head->last	= NULL;
	return head;
}

static node_t* new_node(void* data)
{
	node_t*		node;

	node 		= xmalloc(sizeof(node_t));
	node->next 	= NULL;
	node->data 	= data;
	return node;
}

node_t* get_node(list_t* head, unsigned int index)
{
	node_t*		node = head->first;
	unsigned int	i;

	for (i = 0; node != NULL; node = node->next, ++i)
		if (i == index)
			return node;
	return NULL;
}

void* get_data(list_t* head, unsigned int index)
{
	return get_node(head, index)->data;
}

void set(list_t* head, unsigned int index, void* data)
{
	node_t*		node = head->first;

	unsigned int i;
	for (i = 0; i < index; ++i) {
		node = node->next;
	}

	node->data = data;
}

void insert_first(list_t* head, void* data)
{
	node_t*		node;

	node = new_node(data);
	if (head->last == NULL)
		head->last = node;
	else
		node->next = head->first;
	head->first = node;
}

void insert_last(list_t* head, void* data)
{
	node_t*		node;

	node = new_node(data);
	if (head->first == NULL)
		head->first = node;
	else
		head->last->next = node;
	head->last = node;
}

void free_list(list_t* head)
{
	node_t*		p;
	node_t*		q;

	p = head->first;
	free(head);

	while (p != NULL) {
		q = p->next;
		free(p);
		p = q;
	}
}
