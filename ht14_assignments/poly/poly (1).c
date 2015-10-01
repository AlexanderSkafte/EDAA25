#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "poly.h"

#define	VAR	'x'

typedef int TYPE;

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

static bool is_single(const char* str)
{
	return strlen(str) == 1;
}

/* Replaces all occurences of `s` in `src` with `d` in `dst` */
static char* replaced(const char* s, const char* d, const char* src)
{
	char*		dst;
	unsigned long	slen	= strlen(s);
	unsigned long	dlen	= strlen(d);

	dst = xmalloc(strlen(src) - strlen(s) + strlen(d) + 1);
	memset(dst, 0, strlen(src) - strlen(s) + strlen(d) + 1); /* TODO */


	for (int i = 0; i < strlen(dst); ++i) {
		
	}
}

poly_t* new_poly_from_string(const char* str)
{
	char* buf;
	replace("-", str, "+-", buf);

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

