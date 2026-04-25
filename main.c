#include <stdio.h>
#include "matrix.h"

int main()
{
	Matrix m1 = matrix_alloc(5, 9);
	Matrix m2 = matrix_alloc(2, 5);

	matrix_fill(&m1, 2);
	matrix_fill(&m2, 4);

	//////////////////////////////////////

	matrix_print(&m1);
	printf("\n\0");
	matrix_print(&m2);

	//////////////////////////////////////

	/*
	Matrix added = matrix_alloc(5, 5);
	matrix_add(&added, &m1, &m2);
	printf("\n\0");
	matrix_print(&added);
	matrix_free(added);
	*/

	//////////////////////////////////////

	
	Matrix dot = matrix_alloc(2, 9);
	matrix_dot(&dot, &m1, &m2);
	printf("\n\0");
	matrix_print(&dot);
	matrix_free(dot);
	

	//////////////////////////////////////

	matrix_free(m1);
	matrix_free(m2);

	return 0;
}