#include <stdio.h>
#include <stdlib.h>

#include "list.h"

/*
 * Verify that a newly created list is empty. Otherwise, prints an
 * error message to stderr and exits via exit() with an error signal.
 */
void empty_list_test()
{
	// Create empty list.
	list *l=list_empty(NULL);

	// Verify that list is empty.
	if (!list_is_empty(l)) {
		// Write error message to stderr.
		fprintf(stderr, "FAIL. New list is not empty!\n");
		// Try to clean up (may crash).
		list_kill(l);
		// Exit with error message.
		exit(EXIT_FAILURE);
	}

	// Everything OK, clean up after the test. No memory leaks
	// allowed for passed tests.
	list_kill(l);
}

/*
 * Verify that a list with one element is not empty. Otherwise, prints an error
 * message to stderr and exits via exit() with an error signal.
 */
void one_element_test()
{
	// Create empty list.
	list *l=list_empty(free);

	// Create one element.
	int *v=malloc(sizeof(*v));
	*v=4;

	// Insert element first in list.
	list_insert(l, v, list_first(l));

	// Verify that list is NOT empty
	if (list_is_empty(l)) {
		// Write error message to stderr.
		fprintf(stderr, "FAIL. List with one element is empty!\n");
		// Try to clean up (may crash).
		list_kill(l);
		// Exit with error message.
		exit(EXIT_FAILURE);
	}

	// Everything OK, clean up after the test. No memory leaks
	// allowed for passed tests.
	list_kill(l);
}

/*
 * Verify that the value inserted at the end of a list can be
 * retrieved via inspect(first()). Otherwise, prints an error message to
 * stderr and exits via exit() with an error signal.
 */
void element_value_test()
{
	// Create empty list.
	list *l=list_empty(free);

	// Create element with value 4.
	int *v=malloc(sizeof(*v));
	*v=4;
	// Insert element, should return position of new elemeent.
	list_pos p=list_insert(l, v, list_end(l));

	// Verify that value 4 is at the head of the list.
	int *inspected_val=list_inspect(l, list_first(l));
	if (*inspected_val!=4) {
		// Write error message to stderr.
		fprintf(stderr, "FAIL. Expected %d first in list, got %d!\n",
			4,*inspected_val);
		// Try to clean up (may crash).
		list_kill(l);
		// Exit with error message.
		exit(EXIT_FAILURE);
	}

	// Everything OK, clean up after the test. No memory leaks
	// allowed for passed tests.
	list_kill(l);
}

int main (void)
{
	fprintf(stderr,"Running TEST1: empty_list_test(): ");
	empty_list_test();
	fprintf(stderr,"OK.\n");
	fprintf(stderr,"Running TEST2: one_element_test(): ");
	one_element_test();
	fprintf(stderr,"OK.\n");
	fprintf(stderr,"Running TEST3: element_value_test(): ");
	element_value_test();
	fprintf(stderr,"OK.\n");

	// More tests...

	fprintf(stderr,"All tests completed OK.\n");
	return 0;
}
