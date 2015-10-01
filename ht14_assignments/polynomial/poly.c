/*
 * polynomial
 * Assignment 3 - EDAA25 (C programming)
 * Author: Alexander Skafte
 * Personal identity number: <omitted>
 * email: <omitted>
 */

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "poly.h"

#include "list.c"	/* also includes xmalloc */

/*-----------------------------------------------------------------------------*
|	TODO
|		* Fix the loop inside the mul(...) function. That is where
|		  the program fails, for the moment.
*-----------------------------------------------------------------------------*/

/*
 * Called when the program finds a digit, that is not in the exponent.
 * Reads the string until it finds a "power" sign (^), return coefficient.
 */
static int make_coef(const char* term_str);

/*
 * Called after the program finds a '^' character, and then takes the rest of
 * the term and creates an exponent from it. Returns the exponent as an int.
 */
static int make_exp(const char* term_str, int s);

/*
 * I have to add these prototypes for some reason, even though
 * both strdup and strtok_r should be found in string.h...
 */
char* strdup(const char* str);
extern char *strtok_r(char *, const char *, char **);


struct poly_t {
	list_t*		terms;
};

struct term_t {
	signed char	sign;
	int		coef;
	int		exp;
};


poly_t* new_poly_from_string(const char* p_str)
{
	printf("new_poly_from_string(\"%s\") beginning\n", p_str);

	poly_t*		p;		/* The polynomial to be returned      */
	term_t		term;		/* Struct representation of one term  */
	char*		term_str;	/* String representation of one term  */
	char*		saveptr;	/* Used in strtok_r		      */
	int		s;		/* Keeps track of string "location"   */
	bool		should_add_term;

	p 		= xmalloc(sizeof(poly_t));
	p->terms 	= new_list();

	char tmp_str[strlen(p_str) + 1];		/* Create tmp_str.    */
	for (int i = 0; i < strlen(tmp_str) + 1; ++i)	/* Copy p_str	      */
		tmp_str[i] = *p_str++;			/* to tmp_str.	      */

	printf("\ttmp_str = \"%s\"\n", tmp_str);

	term_str = strtok_r(tmp_str, " ", &saveptr);

	while (term_str != NULL) {
		printf("\twhile (term_str != NULL) entered\n");
		printf("\t\tterm_str = \"%s\"\n", term_str);
		term.sign = 1;

		if (isalpha(term_str[0]))
			term.coef = 1;

		if (isdigit(term_str[0]) || term_str[0] == '-')
			term.coef = make_coef(term_str);

		for (s = 0; term_str[s] != '\0'; ++s) {

			if (term_str[s] == '^') {
				term.exp = make_exp(term_str, s + 1);
			}

			if (term_str[s] == '+' && term_str[s + 1] == '\0') {
				term.sign = +1;
				should_add_term = true;
			}

			if (term_str[s] == '-' && term_str[s + 1] == '\0') {
				term.sign = -1;
				should_add_term = true;
			}

		}

		if (should_add_term) {
			insert_last(p->terms, &term);
			should_add_term = false;
			printf("\t\tDid add \"%s\"\n", term_str);
		} else {
			printf("\t\tDid not add \"%s\"\n", term_str);
		}

		term_str = strtok_r(NULL, " ", &saveptr);
	}
	printf("new_poly_from_string(\"%s\") ending\n", p_str);
	return p;
}

void print_poly(poly_t* p)
{
	printf("print_poly BEGINNING\n");
	term_t		p_term;
	signed char	sign;
	int 		coef;
	int		exp;

	for (int t = 0; get_node(p->terms, t) != NULL; ++t) {
		printf("%d", t);

		p_term = *(term_t*)get_data(p->terms, t);

		sign	= p_term.sign;
		coef	= p_term.coef;
		exp	= p_term.exp;

		if (exp == 0)
			printf("%d", coef);
		else if (coef == 1)
			printf("x^%d ", exp);
		else
			printf("%dx^%d ", sign * coef, exp);
	}
	printf("print_poly ENDING");
	printf("\n");
}

poly_t* mul(poly_t* p, poly_t* q)
{
	printf("mul(p, q) beginning\n");
	poly_t* 	r;			/* Resulting polynomial	      */
	term_t		r_term, p_term, q_term;	/* Temps for readability      */
	int 		t;			/* Term count 		      */

	r		= xmalloc(sizeof(poly_t));
	r->terms 	= new_list();
	t		= 0;

	p_term = *(term_t*)get_data(p->terms, t);
	q_term = *(term_t*)get_data(q->terms, t);

	r_term.sign	= p_term.sign * q_term.sign;
	r_term.coef	= p_term.coef * q_term.coef;
	r_term.exp	= p_term.exp  * q_term.exp;

/*	insert_last(r->terms, &r_term);
remove this ^ */

	for (int i = 0; get_node(p->terms, i) != NULL; ++i) {
		for (int j = 0; get_node(q->terms, j) != NULL; ++j) {
			p_term		= *(term_t*)get_data(p->terms, t);
			q_term		= *(term_t*)get_data(q->terms, t);

			r_term.sign	= p_term.sign * q_term.sign;
			r_term.coef	= p_term.coef * q_term.coef;
			r_term.exp	= p_term.exp  * q_term.exp;

			insert_last(r->terms, &r_term);
			++t;
		}
	}
	printf("mul(p, q) ending\n");
	return r;
}

void free_poly(poly_t* p)
{
	free_list(p->terms);
	free(p);
}

static int make_coef(const char* term_str)
{
	printf("\t\t\tmake_coef(%s) ", term_str);
	char		str[40]	= { '$' };
	signed char	sign	= 1;
	int 		i 	= 0;

	while (isdigit(term_str[i]) || term_str[i] == '-') {
		str[i] = term_str[i];
		++i;
	}

	if (str[0] == '-')
		sign = -1;

	strtok(str, "$");

	printf("\treturned %d\n", atoi(str));
	return (sign * atoi(str));
}

static int make_exp(const char* term_str, const int s)
{
	printf("\t\t\tmake_exp(%s, %d) ", term_str, s);
	char		str[40]	= { '$' };
	signed char	sign	= 1;
	int		i	= 0;

	while (isdigit(term_str[s + i])) {
		str[i] = term_str[s + i];
		++i;
	}

	if (str[0] == '-')
		sign = -1;

	strtok(str, "$");

	printf("\treturned %d\n", sign * atoi(str));
	return (sign * atoi(str));
}


/* need not define this, since it is included with string.h. declare it though*/
/*
char* strdup(const char* str)
{
    char* dup = malloc(strlen(str) + 1);
    if (dup)
        strcpy(dup, str);
    return dup;
}*/


/*
	Inside new_poly_from_string

		for (s = 1; term_str[s] != '\0'; ++s) {

			if (term_str[s] == '+' || term_str[s] == '-') {
				if (term_str[s] == '+') {
					term.sign = +1;
					printf("\t\tterm.sign = %d", term.sign);
				} else {
					term.sign = -1;
				}
				should_add_term = false;
			} else {
				should_add_term = true;
			}
		}
*/
