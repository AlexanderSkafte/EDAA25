#include <stdio.h>
#include <stdlib.h>

int main()
{
	short	c, i, j, max, n = 0;
	char*	input = NULL;

	while (((input = realloc(input, ++n))[n - 1] = getchar()) != EOF) ;
	input[n - 1] = 0;

	for (i = j = max = c = 0; i < n - 1; ++i) {
		if (input[i] != ' ' && input[i] != '\n') {
			c++;
		} else {
			if (c > max) {
				j = i - c;
				max = c;
			}
			c = 0;
		}
	}

	input[j + max] = 0;
	printf("%d characters in longest word: %s\n", max, &input[j]);

	free(input);
}

