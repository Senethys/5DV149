#include <stdio.h>
#include <stdlib.h>

#include "array_1d.h"


struct array_1d {
	int low; // Low index limit.
	int high; // High index limit.
	int array_size; // Number of array elements.
	void **key_value_pairs; // Pointer to where the actual values are stored.
	free_function free_func;
};

array_1d *array_1d_create(free_function free_func, int lo, int hi)
{
	// Allocate array structure.
	array_1d *a=calloc(1, sizeof(*a));
	// Store index limit.
	a->low=lo;
	a->high=hi;

	// Number of elements.
	a->array_size = hi-lo+1;

	// Store free function.
	a->free_func=free_func;

	a->values=calloc(a->array_size, sizeof(void *));

	// Check whether the allocation succeeded.
	if (a->values == NULL) {
		free(a);
		a=NULL;
	}
	return a;
}


int array_1d_low(const array_1d *a)
{
	return a->low;
}


int array_1d_high(const array_1d *a)
{
	return a->high;
}


void *array_1d_inspect_value(const array_1d *a, int i)
{
	int offset=i-array_1d_low(a);
	// Return the value.
	return a->values[offset];
}


bool array_1d_has_value(const array_1d *a, int i)
{
	int offset=i-array_1d_low(a);
	// Return true if the value is not NULL.
	return a->values[offset] != NULL;
}

void array_1d_set_value(array_1d *a, void *v, int i)
{
	int offset=i-array_1d_low(a);
	// Call free_func if specified and old element value was non-NULL.
	if (a->free_func != NULL && a->values[offset] != NULL) {
		a->free_func( a->values[offset] );
	}
	// Set value.
	a->values[offset]=v;
}

void array_1d_kill(array_1d *a)
{
	if (a->free_func) {
		// Return user-allocated memory for each non-NULL element.
		for (int i=0; i<a->array_size; i++) {
			if (a->values[i] != NULL) {
				a->free_func(a->values[i]);
			}
		}
	}
	// Free actual storage.
	free(a->values);
	// Free array structure.
	free(a);
}


void array_1d_print(const array_1d *a, inspect_callback print_func)
{
	printf("[ ");
	for (int i=array_1d_low(a); i<=array_1d_high(a); i++) {
		if (array_1d_has_value(a,i)) {
			printf("[");
			print_func(array_1d_inspect_value(a,i));
			printf("]");
		} else {
			printf(" []");
		}
		if (i<array_1d_high(a)) {
			printf(", ");
		}
	}
	printf(" ]\n");
}
