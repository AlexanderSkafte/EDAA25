/*
 * factorial.c 
 * Assignment 2 - EDAA25 (C programming)
 * Author: Alexander Skafte
 * Personal identity number: 941123-4330
 * email: tfy13ask@student.lu.se
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE	(999999L)

void factorial(unsigned long n)
{
	if (n == 0) {
		printf("\n\t0! = 1\n\n");
		return;
	}

	unsigned long a[SIZE];		/* Array to hold each digit of result */
	unsigned long index = 0;	/* Array index */
	unsigned long tmp = n;		/* For intermediate computations */
	unsigned long digits = 0;	/* Counts number of digits */
	unsigned long carry = 0;	/* Carry value when multiplicating */

	/* Store each digit of n in a[], backwards */
	while (tmp > 0) {
		a[index++] = tmp % 10;
		tmp /= 10;
		digits++;
	}

	/*
	 * Multiply every n and n-1, compute and store the carry so it
	 * can be used in the next iteration.
	 */
	unsigned long m;
	for (m = n; m > 1; --m) {
		for (index = 0; index < digits; ++index) {
			tmp = a[index] * (m - 1) + carry;
			a[index] = tmp % 10;
			carry = tmp / 10;
		}
		while (carry > 0) {
			a[index++] = carry % 10;
			carry /= 10;
			digits++;
		}
	}

	/* Print the result */
	printf("\n\t%lu! = ", n);
	for (index = digits; index > 0; --index)
		printf("%lu", a[index - 1]);
	printf("\n\n");
}

int main(int argc, char* argv[])
{
	unsigned long input = atol(argv[1]);
//	printf("\nEnter a number to factorialize: ");
//	scanf("%lu", &input);
//	while (input < 0 || input > 255) {
//		printf("Please enter an integer 1 <= n <= 255.\nNew number: ");
//		scanf("%d", &input);
//	}
	factorial(input);
	return 0;
}
