#include <stdio.h>
#include <stdbool.h>
#include "matrix.h"

int main()
{
	matrix m1 = matrix_alloc(5, 5);

	matrix_rand(&m1);
	matrix_print(&m1, true);

	printf("\n");

	matrix m2 = matrix_copy(&m1);
	matrix_print(&m2, true);

	matrix_free(m1);

	return 0;
}