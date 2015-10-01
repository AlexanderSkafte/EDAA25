#include <stdio.h>
#include <stdlib.h>

int main()
{
	int	c, i, j, max, n = 0;
	char*	input = NULL;

	while ((c = getchar()) != EOF) {
		input = realloc(input, ++n);
		input[n - 1] = c;
	}
	input[n - 1] = 0;

	for (i = j = max = c = 0; i < n - 1; ++i) {
		if (input[i] == ' ' || input[i] == '\n') {
			if (c > max) {
				j = i - c;
				max = c;
			}
			c = 0;
		} else {
			c++;
		}
	}

	input[j + max] = 0;
	printf("%d characters in longest word: %s\n", max, &input[j]);

	free(input);

	return EXIT_SUCCESS;
}

