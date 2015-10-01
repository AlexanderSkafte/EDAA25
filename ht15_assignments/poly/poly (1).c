#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "poly.h"

#define MAX(A,B) ((A) > (B) ? (A) : (B))

struct poly_t {
	size_t	size;
	int*	coeffs;
};

int isplus	(char c) { return c == '+'; }
int isminus	(char c) { return c == '-'; }
int isvar	(char c) { return c == 'x'; }

int read_num(const char* str)
{
	int num;
	sscanf(str, "%d", &num);
	return num;
}

/*
 *	x^3
 *	2x^2
 *	2x
 *	x
 *	2
 *
 */
void make_term(const char** str_p, poly_t* p)
{
	printf("Entering make_term...\n");

	signed char	sign;
	int		exp;
	int		coeff	= 1;
	const char*	str	= *str_p;

	sign = isminus(*str)
		? -1
		: +1;

	while (isspace(*str)) {
		str++;
	}

	if (isdigit(*str)) {
		coeff = sign * read_num(str);
	}

	if (isvar(*str)) {
		if (*(str + 1) == '^') {
			str++;
			str++;
		} else {
			str++;
		}
	}

	exp = read_num(str);

	*str_p = ++str;

	if (exp + 1 > p->size) {
		int old_size = p->size;
		p->size	= exp + 1;
		// TODO Check return value.
		int* new_coeffs = calloc(p->size, sizeof(int));
		memcpy(new_coeffs, p->coeffs, old_size * sizeof(int));
		free(p->coeffs);
		p->coeffs = new_coeffs;
	}

	p->coeffs[exp] = coeff;

	printf("    term: coeff = %d, exp = %d\n", coeff, exp);
}

poly_t* new_poly_from_string(const char* str)
{
	char	c;
	poly_t*	p = malloc(sizeof *p);
	{
		p->size		= 0;
		p->coeffs	= NULL;
	}

	while ((c = *str) != '\0') {

		if (isspace(c)) {
			str++;
			continue;
		}

		if (isplus(c) || isminus(c) || isdigit(c) || isvar(c)) {
			make_term(&str, p);
		}
	}

	printf("%zu\ncoeffs:", p->size);

	for (int i = 0; i < p->size; ++i)
		printf("%d ", p->coeffs[i]);
	putchar('\n');

//	printf("ALEXANDER\n");
//	print_poly(p);
//	printf("SLUT\n");
//	putchar('\n');
	return p;
}

void free_poly(poly_t* p)
{
	if (p != NULL) {
		free(p->coeffs);
		free(p);
	}
}

poly_t* mul(poly_t* p, poly_t* q)
{
	poly_t* r = malloc(sizeof *r);
	{
		r->size		= p->size + q->size - 1;
		r->coeffs	= calloc(r->size, sizeof(int));
	}

	for (int i = 0; i < p->size; ++i) {
		for (int j = 0; j < q->size; ++j) {
			r->coeffs[i + j] = p->coeffs[i] * q->coeffs[j];
		}
	}

	return r;
}

void print_poly(poly_t* p)
{
	for (int i = p->size - 1; i >= 0; --i) {
		if (p->coeffs[i] == 0) {
			continue;
		}

		if (p->coeffs[i] != 1) {
			printf("%d", p->coeffs[i]);
		}

		if (i == 0) {
			printf("%d", p->coeffs[i]);
			continue;
		} else {
			printf("x^%d ", i);
		}
	}
//	putchar('\n');
}

