#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <math.h>
#include "matrix.h"

static inline matrix* sigmoid(matrix* m)
{
	size_t total_size = m->_cols * m->_rows;
	for (size_t i = 0; i < total_size; ++i)
		m->_data[i] = 1.0f / (1.0f + exp(-m->_data[i]));
	return m;
}

static inline matrix* softmax(matrix* m)
{
	size_t total_size = m->_cols * m->_rows;

	// Prevent huge values and breaking due to inf by subtracting every number by the maximum number to keep the result the same but the number smaller.
	double max = m->_data[0];
	for (size_t i = 1; i < total_size; ++i)
		if (m->_data[i] > max)
			max = m->_data[i];

	double sum = 0.0f;
	for (size_t i = 0; i < total_size; ++i)
	{
		m->_data[i] = exp(m->_data[i] - max);
		sum += m->_data[i];
	}
	for (size_t i = 0; i < total_size; ++i)
		m->_data[i] /= sum;

	return m;
}

#endif // !ACTIVATION_H