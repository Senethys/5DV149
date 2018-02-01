#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dlist.h"

/*
 * Minimum working example for list.c.
 *
 * Authors: Niclas Borlin (niclas@cs.umu.se)
 *	    Lars Karlsson (larsk@cs.umu.se)
 *
 * Version information:
 *   2018-01-28: v1.0, first public version.
 */

// Copy string.
static char *copy_string(char *str)
{
    char *copy = calloc(strlen(str) + 1, sizeof(char));
    strcpy(copy, str);
    return copy;
}

// String print function.
static void print_string(const void *value)
{
    printf("\"%s\"", (char *)value);
}

// Test program.
int main(void)
{
	// Names to insert in the list.
	char *names[] = {"Alfons", "Bengt", "Cia", "David", "Florian", "Gunnar"};

	// Create the list
	dlist *l = dlist_empty(free);
	dlist_pos p = dlist_first(l);
	for (int i = 0; i < sizeof(names) / sizeof(names[0]); i++) {
		// Insert dynamic copies of strings at last position.
		p = dlist_insert(l, copy_string(names[i]), p);
		p = dlist_next(l, p);
	}
	// Print the list.
	dlist_print(l, print_string);
	// Destroy the list.
	dlist_kill(l);
}
