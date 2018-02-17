#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "array_1d.h"


// Integers are stored via int pointers stored as void pointers.
// Convert the given pointer and print the dereferenced value.
static void print_ints(const void *data)
{
	printf("%d", *(int*)data);
}

// Struct with month value and number of key.
struct pair {
	void *key;
	char *value;
};

// Months are stored via void pointers. Convert the given pointer and
// print the dereferenced values.
static void print_months(const void *data)
{
	// Convert void pointer to pointer to month.
	const struct month *m=data;
	printf("(%s, %d)", m->value, m->key);
}

// Function to free both month structure and char * with value.
static void free_month(void *data)
{
	// Convert void pointer to pointer to month.
	struct month *m=data;
	free(m->value);
	free(m);
}

int main(void)
{
	const char * months[12] = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};
	int month_key[12] = {
		31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31
	};

	// Create an array with 6 positions.
	array_1d *a = array_1d_create(free,1,6);

	for (int i=array_1d_low(a); i<=array_1d_high(a); i++) {
		// Allocate memory for an integer.
		int *v=malloc(sizeof(*v));
		// Set value to square of index. for reasons unknown.
		*v=i*i;
		array_1d_set_value(a,v,i);
		array_1d_print(a, print_ints);
	}
	array_1d_print(a, print_ints);

	array_1d_kill(a);

	// Create another array with 12 positions.
	a = array_1d_create(free_month,1,12);

	for (int i=array_1d_low(a); i<=array_1d_high(a); i++) {
		// Allocate memory for a month structure.
		struct month *m=malloc(sizeof(*m));
		// Allocate memory for month value.
		m->value=calloc(strlen(months[i-1])+1,sizeof(char));
		// Copy string.
		strcpy(m->value, months[i-1]);
		// Set key.
		m->key=month_key[i-1];
		// Set value in array.
		array_1d_set_value(a,m,i);
	}
	array_1d_print(a, print_months);

	array_1d_kill(a);

	return 0;
}
