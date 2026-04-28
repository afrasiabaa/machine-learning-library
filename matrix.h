#ifndef MATRIX_H
#define MATRIX_H

// Macro to access a specific row and column. (m: Matrix, c: coloumn, r: row)
#define MATRIX_AT(m, c, r) (m)._data[(r) * (m)._cols + (c)]

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

// Do not create a Matrix struct with the constructor. Use the matrix_alloc() function instead.
typedef struct
{
	size_t _cols;
	size_t _rows;
	double* _data;
} matrix;

// Create a matrix
static inline matrix matrix_alloc(const int cols, const int rows)
{
	matrix m = {0, 0, NULL};

	if (cols <= 0 || rows <= 0)
		return m;

	size_t check_cols = (size_t)cols;
	size_t check_rows = (size_t)rows;

	if (check_cols != 0 && check_rows > SIZE_MAX / check_cols)
		return m;

	const size_t total_matrix_size = (size_t)check_cols * (size_t)check_rows;

	if (total_matrix_size > SIZE_MAX / sizeof(*m._data))
		return m;

	m._cols = check_cols;
	m._rows = check_rows;
	m._data = (double*)malloc(sizeof(*m._data) * total_matrix_size);
	assert(m._data != NULL);

	for (size_t i = 0; i < total_matrix_size; ++i)
		m._data[i] = 0;

	return m;
}

// Fill in our matrix with a specific value
static inline void matrix_fill(matrix* m, const double val)
{
	for (size_t r = 0; r < m->_rows; ++r)
		for (size_t c = 0; c < m->_cols; ++c)
			MATRIX_AT(*m, c, r) = val;
}

static inline void matrix_free(matrix m) { free(m._data); }

// Matrix logic
static inline void matrix_dot(matrix* result, const matrix* a, const matrix* b)
{
	// Check to ensure that dot product will work
	assert(a->_cols == b->_rows);

	// Check to ensure that the result can be fed into
	assert(result->_cols == b->_cols);
	assert(result->_rows == a->_rows);

	for (size_t r = 0; r < a->_rows; ++r)
		for (size_t c = 0; c < b->_cols; ++c)
		{
			double sum = 0;
			for (size_t sum_ptr = 0; sum_ptr < a->_cols; ++sum_ptr)
				sum += MATRIX_AT(*a, sum_ptr, r) * MATRIX_AT(*b, c, sum_ptr);
			MATRIX_AT(*result, c, r) = sum;
		}
}

static inline void matrix_add(matrix* result, const matrix* a, const matrix* b)
{
	assert(a->_cols == b->_cols && a->_rows == b->_rows);
	assert(result->_cols == a->_cols && result->_rows == a->_rows);

	size_t total_size = result->_cols * result->_rows;
	for (size_t i = 0; i < total_size; ++i)
		result->_data[i] = a->_data[i] + b->_data[i];
}

static inline void matrix_add_bias(matrix* result, const matrix* bias)
{
	assert(result->_cols == bias->_cols);
	assert(bias->_rows == 1); // each column will be a neurons bias for one row.

	for (size_t r = 0; r < result->_rows; ++r)
		for (size_t c = 0; c < result->_cols; ++c)
			MATRIX_AT(*result, c, r) += MATRIX_AT(*bias, c, 0);
}

static void matrix_rand(matrix* m) 
{
	size_t total_size = m->_cols * m->_rows;
	for (size_t i = 0; i < total_size; ++i)
	{
		double random_value = (double)rand() / (double)RAND_MAX;
		m->_data[i] = random_value;
	}
}

static matrix matrix_copy(matrix* m)
{
	size_t total_size = m->_cols * m->_rows;
	matrix new_matrix = matrix_alloc((const int)m->_cols, (const int)m->_rows);

	for (size_t i = 0; i < total_size; ++i)
		new_matrix._data[i] = m->_data[i];

	return new_matrix;
}

static void matrix_print(const matrix* m, const bool whole_number)
{
	const size_t total_matrix_size = m->_rows * m->_cols;
	size_t counter = 0;

	for (size_t i = 0; i < total_matrix_size; ++i)
	{
		whole_number == true ? printf("%.lf ", m->_data[i]) : printf("%.2lf ", m->_data[i]);

		++counter;
		if (counter >= m->_cols)
		{
			counter = 0;
			printf("\n");
		}
	}
}

static inline void matrix_convolution(matrix* result, const matrix* image, const matrix* kernel)
{
	assert(result->_cols == (image->_cols - kernel->_cols + 1));
	assert(result->_rows == (image->_rows - kernel->_rows + 1));

	for (size_t y = 0; y < result->_rows; ++y)
		for (size_t x = 0; x < result->_cols; ++x)
		{
			double sum = 0.0f;
			for (size_t ky = 0; ky < kernel->_rows; ++ky)
			{
				for (size_t kx = 0; kx < kernel->_cols; ++kx)
					sum += MATRIX_AT(*image, x + kx, y + ky) * MATRIX_AT(*kernel, kx, ky);
			}
					
			MATRIX_AT(*result, x, y) = sum;
		}
}

#endif // !MATRIX_H
