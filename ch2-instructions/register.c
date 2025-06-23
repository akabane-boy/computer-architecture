/*
 * Check the used register for arithmetic operations in assembly.
 */
#include <stdio.h>

int main(void)
{
	int f, g, h, i, j;

	g = 1;
	h = 2;
	i = 3;
	j = 4;

	f = (g + h) - (i + j);

	printf("%d\n", f);

	return 0;
}
