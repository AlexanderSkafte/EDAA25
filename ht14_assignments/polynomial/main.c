#include <stdbool.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "poly.h"

char*	progname;

static void poly_test(const char* a, const char* b)
{
	poly_t*		p;	/* Polynomial made from A. */
	poly_t*		q;	/* Polynomial made from B. */
	poly_t*		r;	/* Product of P and Q. */

	printf("\n-------------------------------------------------\n");
	printf("[M] Beginning polynomial test of (%s) * (%s)\n", a, b);

	printf("\n[M] Creating poly p:\n");
	p = new_poly_from_string(a);
	printf("\n[M] Creating poly q:\n");
	q = new_poly_from_string(b);

	printf("\n[M] Printing poly p:\n");
	print_poly(p);
	printf("\n[M] Printing poly q:\n");
	print_poly(q);

	printf("\n[M] Multiplying p and q:\n");
	r = mul(p, q);

	printf("\n[M] Printing poly r: ");
	print_poly(r);

	printf("\n[M] Freeing poly p, q, r:\n");
	free_poly(p);
	free_poly(q);
	free_poly(r);

	printf("\n[M] Ending polynomial test of (%s) * (%s)\n", a, b);
	printf("-------------------------------------------------\n\n");
}

int main(int argc, char** argv)
{
	progname = argv[0];

	poly_test("-3x^2 - 7x + 1", "3x + 2");
/*	poly_test("x^10000000 + 2", "2x^2 + 3x + 4");
*/
	return 0;
}
