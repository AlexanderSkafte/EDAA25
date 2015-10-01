#ifndef poly_h
#define poly_h


/*
 * A struct with data that can represent a polynomial term.
 */
typedef struct term_t term_t;


/*
 * A struct with data that can represent a polynomial expression.
 */
typedef struct poly_t poly_t;


/*
 * Creates a new polynomial from a string, e.g. "x^30 - 42x + 5".
 */
poly_t* new_poly_from_string(const char*);


/*
 * Prints the entire polynomial as a string.
 * Returns nothing.
 */
void print_poly(poly_t*);


/*
 * Multiplicates two poly_t structs and returns the result as a poly_t pointer.
 */
poly_t* mul(poly_t*, poly_t*);


/*
 * Frees memory allocated for poly_t.
 */
void free_poly(poly_t*);


#endif
