#ifndef MATRIX_H
#define MATRIX_H

// Macro to access a specific row and column. (m: Matrix, c: coloumn, r: row)
#define MATRIX_AT(m, c, r) (m)._data[(r) * (m)._cols + (c)]

#include <stdlib.h>
#include <assert.h>

// Definition of our matrix
typedef struct 
{
	size_t _cols;
	size_t _rows;
	double* _data;
} Matrix;

// Create a matrix
static inline Matrix matrix_alloc(const size_t* cols, const size_t* rows)
{
	Matrix m;
	m._cols = *cols;
	m._rows = *rows;
	m._data = (double*)malloc(sizeof(*m._data) * *rows * *cols);
	assert(m._data != NULL);
	return m;
}

// Fill in our matrix with a specific value
static inline void matrix_fill(Matrix* m, const double val)
{
	for (size_t r = 0; r < m->_rows; ++r)
		for (size_t c = 0; c < m->_cols; ++c)
			MATRIX_AT(*m, c, r) = val;
}

static inline void matrix_free(Matrix m) { free(m._data); }

// Matrix logic
static inline void matrix_dot(Matrix* result, const Matrix* a, const Matrix* b)
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

static inline void matrix_add(Matrix* result, const Matrix* a, const Matrix* b)
{
	assert(a->_cols == b->_cols && a->_rows == b->_rows);
	assert(result->_cols == a->_cols && result->_rows == a->_rows);

	size_t total_size = result->_cols * result->_rows;
	for (size_t i = 0; i < total_size; ++i)
		result->_data[i] = a->_data[i] + b->_data[i];
}

static void matrix_print(const Matrix* matrix)
{
	
}

#endif // !MATRIX_H
