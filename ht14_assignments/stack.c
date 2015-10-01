void* xmalloc(size_t size)
{
	void*	ptr = malloc(size);

	if (ptr == NULL) {
		fprintf(stderr, "Out of memory\n");
		exit(1);
	}
	return ptr;
}

typedef struct stack_t stack_t;

struct stack_t {
	stack_t*	next;
	void*		data;
};

stack_t* new_stack(void)
{
	stack_t*	stack;

	stack = xmalloc(sizeof(stack_t));
	stack->next 	= NULL;
	stack->data	= NULL;

	return stack;
}

void* pop(stack_t* stack)
{
	void*		data;
	stack_t*	p;

	p = stack->next;
	stack->next = p->next;
	data = p->data;
	free(p);
	return data;
}

void free_stack(stack_t** stack)
{
	stack_t*	p = *stack;
	stack_t*	q;

	*stack = NULL;

	while (p != NULL) {
		q = p->next;
		free(p);
		p = q;
	}
}

void* top(stack_t* stack)
{
	return stack->next->data;
}

void push(stack_t* stack, void* data)
{
	stack_t*	p;

	p = xmalloc(sizeof(stack_t));
	p->next = stack->next;
	p->data = data;
	stack->next = p;
}
