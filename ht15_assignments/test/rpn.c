#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef DEBUG

#define STACK_MAX (10)
#define INPUT (stdin)

void	rpn		(const char*);
char*	load_input	();
int	read_num	(const char*);

char	stack_overflow		= 0;
char	stack_underflow		= 0;
char	unknown_character	= 0;
char	other_error		= 0;

int	stack		[STACK_MAX];
int	size			= 0;

void push(int n)
{
	stack_overflow = size >= STACK_MAX;
	stack[size++] = n;
//	printf("Pushed number [%d]\n", n);
}

int pop()
{
	stack_underflow = size <= 0;
//	printf("Popped number [%d]\n", stack[size - 1]);
	return stack[--size];
}

void reset()
{
	stack_overflow = 0;
	stack_underflow = 0;
	other_error = 0;
	size = 0;
}

int read_num(const char* str)
{
	int n;
	sscanf(str, "%d", &n);
	return n;
}

void rpn(const char* p)
{
	int	line_num = 1;
	char*	output = "";

	while (*p != '\0' && line_num < 14) {

		if (isdigit(*p)) {
			int num = read_num(p);
//			printf("Got number [%d]\n", num);
			while (isdigit(*p))
				p++;
			push(num);
			if (stack_overflow) {
				goto error;
			}
		}

		switch (*p) {
		case '+':
			if (size >= 2) {
				push(pop() + pop());
			} else {
				output = "error at +";
				other_error = 1;
				goto error;
			}
			break;

		case '-':
			if (size >= 2) {
				int tmp = pop();
				push(pop() - tmp);
			} else {
				output = "error at -";
				other_error = 1;
				goto error;
			}
			break;

		case '*':
			if (size >= 2) {
				push(pop() * pop());
			} else {
				output = "error at *";
				other_error = 1;
				goto error;
			}
			break;

		case '/':
			if (size >= 2) {
				int tmp = pop();
				if (tmp == 0) {
					output = "error at /";
					other_error = 1;
					goto error;
				}
				push(pop() / tmp);
			} else {
				output = "error at /";
				other_error = 1;
				goto error;
			}
			break;

		case ' ':
			break;

		case '\n':
			printf("line %d: ", line_num++);
			if (*(p - 1) == '\n' || size > 1) {
				printf("error at \\n\n");
			} else if (size <= 1) {
				printf("%d\n", pop());
			}
			reset();
			break;

		default:
			unknown_character = *p;
			goto error;
			break;
		}

		p++;

		continue;

error:		while (*p++ != '\n')
			;

		printf("line %d: ", line_num++);

		if (stack_overflow) {
			printf("error at %d", stack[size - 1]);
		} else if (other_error) {
			printf("%s", output);
		} else if (unknown_character) {
			printf("error at %c", unknown_character);
		}

		putchar('\n');
		reset();
		output = "";
	}

}

/* [!] The return value has to be freed by the caller. */
char* load_input(FILE* stream)
{
	int	c;
	int	n	= 0;
	char*	input	= NULL;

	while ((c = getc(stream)) != EOF) {
		input = realloc(input, ++n);
		input[n - 1] = c;
	}
	input = realloc(input, n + 1);
	input[n] = 0;

	return input;
}

int main(void)
{
	char* input = load_input(INPUT);
	rpn(input);
	free(input);
}

