#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "poly.h"

#define	VAR	'x'

typedef signed int TYPE;

typedef struct {
	TYPE	coefficient;
	TYPE	exponent;
} term_t;

struct poly_t {
	size_t	size;
	term_t	terms[];	/* Using "The Struct Hack", see this:	*/
				/* http://c2.com/cgi/wiki?StructHack	*/
};

static void* xmalloc(size_t size);
static void* xcalloc(size_t size);

/* Read how many terms there are in the polynomial */
static size_t get_n_terms(const char* str)
{
	size_t	n_terms = 0;

	for (unsigned long i = 0; i < strlen(str); ++i) {
		if (*str == VAR) {
			n_terms++;
		}
	}

	/* TODO:
	 * 	I guess it's obvious what to do.
	 */
	return strlen(str);
}

#if 0
static bool is_single(const char* str)
{
	return strlen(str) == 1;
}

/* Replaces all occurences of `s` in `src` with `d` in `src` */
static char* replaced(const char* s, const char* d, const char* src)
{
	size_t		i;
	size_t		j;
	unsigned long	slen	= strlen(s);
	unsigned long	dlen	= strlen(d);
	size_t		srclen	= strlen(src);
	size_t		dstlen	= srclen - slen + dlen + 1;
	char*		dst	= xcalloc(dstlen);

	for (i = 0; i < dstlen; ++i) {
		if (!strncmp(src, s, slen)) {
			for (j = 0; j < dlen; ++j) {
				dst[i + j] = d[j];
			}
			i += j;
		}
		dst[i] = src[i - j];

		printf("src = %s\ndst = %s\n\n", src, dst);
	}

	return dst;
}
#endif

poly_t* new_poly_from_string(const char* str)
{
//	char* tmp = replaced("-", "+-", str); /* TODO: Free! */
//
//	printf("Converted:\n\t%s   -->    %s\n", str, tmp);

//	size_t	n_terms = get_n_terms(str);
//	poly_t*	poly	= xmalloc(sizeof(*poly) + n_terms * sizeof(term_t));
//	char	delims[] = "( )";
//	char*	token;
//
//	strcpy(token, str);
//	token = strtok(token, delims);
//
//	while (token != NULL) {
//		if (is_single(str)) {
//			
//		}
//		token = strtok(NULL, delims);
//	}
//
//	return poly;

	/* Third try*/

	for (int i = 0; i < strlen(str); ++i) {

		int	sign;
		TYPE	coefficient;

		char c = str[i];

		if (c == '-') sign = -1;
		if (c == '+') sign = +1;

			
	}

	return NULL;	/* TODO */
}

int next_number(const char* p)
{
	int n;

	scanf(, p, n)



	int i 
	char buffer[1000];
	while (isdigit(p)) {
		buffer[
		++p;
	}
}

void free_poly(poly_t* p)
{

}

poly_t* mul(poly_t* p, poly_t* q)
{
	return NULL;
}

void print_poly(poly_t* p)
{

}

static void* xmalloc(size_t size)
{
	void* p = malloc(size);
	if (p == NULL) {
		fprintf(stderr, "[!] malloc failed (returned NULL).\n");
		exit(1);
	}
	return p;
}

static void* xcalloc(size_t size)
{
	void* p = calloc(1, size);
	if (p == NULL) {
		fprintf(stderr, "[!] calloc failed (returned NULL).\n");
		exit(1);
	}
	return p;
}

