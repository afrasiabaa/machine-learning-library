#ifndef LAYER_H
#define LAYER_H

#include "matrix.h"
#include "activation.h"
#include "error_functions.h"

typedef enum {
	SIGMOID,
	SOFTMAX,
} activationType;

typedef struct {
	matrix weights;
	matrix biases;
	activationType activation;
} layer;

static layer layer_alloc(size_t num_inputs, size_t num_neurons, activationType a)
{
	layer l;
	l.activation = a;

	l.weights = matrix_alloc(num_neurons, num_inputs);
	l.biases = matrix_alloc(num_neurons, 1);

	matrix_rand(&l.weights);
	matrix_fill(&l.biases, 0.01);

	return l;
}

static void forward_prop(layer* l, matrix* input, matrix* output)
{
	matrix_dot(output, input, &l->weights);
	matrix_add(output, output, &l->biases);

	if (l->activation == SIGMOID)
		sigmoid(output);
	else if (l->activation == SOFTMAX)
		softmax(output);
}

static void backward_prop();

#endif // !LAYER_H
