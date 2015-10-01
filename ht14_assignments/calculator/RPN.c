/*
 * RPN.c - an RPN calculator 
 * Assignment 1 - EDAA25 (C programming)
 * Author: Alexander Skafte
 * Personal identity number: <omitted>
 * email: <omitted>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 	(100)
#define	MAX_NBR_LEN	(9)

void throw_error(int error_code);

/* Stack data fields */
int	stack[MAX_SIZE];
size_t 	pos = 0;
int	top;

/* Pushes @param value onto the stack */
void push(int value)
{
	if (pos >= MAX_SIZE)
		throw_error(2);
	stack[pos++] = value;
}

/*
 * Pops the topmost element of the stack and returns its value
 * @return the value contained in the top element of the stack
 */
int pop()
{
	if (pos <= 0)
		throw_error(3);
	top = stack[--pos];
	stack[pos] = 0;
	return top;
}

/*
 * Reads the input and returns the calculated result
 * @return the result of the calculation
 */
int rpn()
{
	/* To store the type of the last non-whitespace character read */
	typedef enum {
		NUMBER,
		OPERATOR
	} encounter;
	encounter last_encounter;

	/*
	 * This array stores the number entered as a string, and converts it
	 * to an integer when whitespace is encountered.
	 */
	char 	nbr[MAX_NBR_LEN] = "";
	size_t 	nbr_len = 0;

	/* Read string and do calculation */
	char 	c;
	while ((c = getchar()) != '\n') {
		if (isdigit(c)) {
			nbr[nbr_len++] = c;
			last_encounter = NUMBER;
		} else if (isspace(c)) {
			if (last_encounter == NUMBER) {
				char fmt_str[4];
				sprintf(fmt_str, "%%%zud", nbr_len);
				sscanf(nbr, fmt_str, &stack[pos++]);
				nbr_len = 0;
			}
		} else if (c == '+' || c == '-' || c == '*' || c == '/') {
			int tmp;
			switch (c) {
			case '+':
				push(pop() + pop());
				break;
			case '-':
				tmp = pop();
				push(pop() - tmp);
				break;
			case '*':
				push(pop() * pop());
				break;
			case '/':
				if ((tmp = pop()) == 0)
					throw_error(4);
				push(pop() / tmp);
				break;
			}
			last_encounter = OPERATOR;
		} else if (c == EOF) {
			printf("[Requested termination...]\n");
			printf("Thank you for using the calculator. Bye!\n\n");
			exit(0);
		} else {
			throw_error(5);
		}
	}

	if (last_encounter == NUMBER)
		throw_error(6);
	return pop();
}

int main(void)
{
	printf("\n#---------------------------------------------------#\n");
	printf("| Program: Reverse Polish Notation (RPN) calculator |\n");
	printf("| Author: Alexander Skafte                          |\n");
	printf("|                                                   |\n");
	printf("| Enter numbers separated by spaces in RPN style.   |\n");
	printf("| For example:                                      |\n");
	printf("|          2 3 + 10 *                               |\n");
	printf("| Execute by pressing Return/Enter.                 |\n");
	printf("| Exit by pressing Ctrl+D.                          |\n");
	printf("#---------------------------------------------------#\n");
	while (1) {
		printf("\nInput> ");
		printf("> %d\n", rpn());
	}
	return 0;
}

/* Prints an error depending on the value passed, and exits with status 1 */
void throw_error(int error_code)
{
	char message[80] = "";
	switch (error_code) {
	case 2:
		strcpy(message, "Stack overflow.");
		break;
	case 3:
		strcpy(message, "Invalid syntax, or tried to pop empty stack.");
		break;
	case 4:
		strcpy(message, "Division by 0");
		break;
	case 5:
		strcpy(message, "Invalid character was entered.");
		break;
	case 6:
		strcpy(message, "Last character can't be a number.");
		break;
	}

	fprintf(stderr, "> ERROR: %s\n\n", message);
	exit(1);
}
