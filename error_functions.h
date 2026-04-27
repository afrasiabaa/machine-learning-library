#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H

#include "matrix.h"
#include "activation.h"
#include <math.h>

static inline matrix* MSE(matrix* a, matrix* b)
{

}

static inline matrix* MAE(matrix* a, matrix* b)
{

}

static inline double categorical_crossentropy_loss(matrix* a, matrix* b)
{
	// a = predictions after softmax
	// b = truth labels 
	// ccl = -sum(b * log(a))
	double total_loss = 0.0f;

	double epsilion = 1e-15;
	size_t matrix_a_size = a->_cols * a->_rows;
	for (size_t i = 0; i < matrix_a_size; ++i);

	
	return total_loss;
}

#endif // !ERROR_FUNCTIONS_H
