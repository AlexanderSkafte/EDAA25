#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "poly.h"

// TODO
//	Check for *alloc return values

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

void make_term(const char** str_p, poly_t* p)
{
	signed char	sign	= 1;
	int		coeff	= 1;
	int		exp;
	const char*	str	= *str_p;

	if (isplus(*str)) {
		sign = 1;
		str++;
	} else if (isminus(*str)) {
		sign = -1;
		str++;
	}

	while (isspace(*str)) {
		str++;
	}

	if (isdigit(*str)) {
		coeff = sign * read_num(str);
		while (isdigit(*str)) {
			str++;
		}
	}

	if (isvar(*str)) {
		if (*(str + 1) == '^') {
			str++;
			str++;
			exp = read_num(str);
			while (isdigit(*str)) {
				str++;
			}
		} else {
			exp = 1;
			str++;
		}
	} else {
		exp = 0;
	}

	*str_p = str;

	if (exp + 1 > p->size) {
		int old_size = p->size;
		p->size	= exp + 1;
		int* new_coeffs = calloc(p->size, sizeof(int));
		memcpy(new_coeffs, p->coeffs, old_size * sizeof(int));
		free(p->coeffs);
		p->coeffs = new_coeffs;
	}

	p->coeffs[exp] = coeff;
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
			r->coeffs[i + j] += p->coeffs[i] * q->coeffs[j];
		}
	}

	return r;
}

void print_poly(poly_t* p)
{
	for (int i = p->size - 1; i >= 0; --i) {

		int c = p->coeffs[i];
		int e = i;

		if (c == 0) {
			continue;
		}
		if (c < 0) {
			c = -c;
			printf(" - ");
		} else if (i != p->size - 1) {
			printf(" + ");
		}
		if (e == 1) {
			printf("%dx", c);
		} else if (e != 0) {
			if (c != 1) {
				printf("%d", c);
			}
			printf("x^%d", e);
		} else {
			printf("%d", c);
		}
	}
	putchar('\n');
}

