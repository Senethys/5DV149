#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table.h"

/*
 * Minimum working example for table.c.
 *
 * Authors: Niclas Borlin (niclas@cs.umu.se)
 *	    Adam Dahlgren Lindstrom (dali@cs.umu.se)
 *
 * Version information:
 *   2018-02-06: v1.0, first public version.
 */

static char* make_string_copy(const char *str)
{
	char *copy = calloc(strlen(str) + 1, sizeof(char));
	strcpy(copy, str);
	return copy;
}

static void print_int_string_pair(const void *key, const void *value)
{
	const int *k=key;
	const char *s=value;
	printf("[%d, %s]\n", *k, s);
}

static int compare_ints(const void *k1, const void *k2)
{
	int key1 = *(int *)k1;
	int key2 = *(int *)k2;

	if ( key1 == key2 )
		return 0;
	if ( key1 < key2 )
		return -1;
	return 1;
}

int main(void)
{
	table *t = table_empty(compare_ints, free, free);

	int *key;
	char *value;
	
	key = malloc(sizeof(int));
	*key = 90187;
	value = make_string_copy("Umea");
	table_insert(t, key, value);

	key = malloc(sizeof(int));
	*key = 90184;
	value = make_string_copy("Umea");
	table_insert(t, key, value);

	key = malloc(sizeof(int));
	*key = 98185;
	value = make_string_copy("Kiruna");
	table_insert(t, key, value);

	printf("Table after inserting 3 pairs:\n");
	table_print(t, print_int_string_pair);

	int v=90187;
	char *s=table_lookup(t,&v);
	printf("Lookup of postal code %d: %s.\n",v,s);
	
	printf("Table after lookup:\n");
	table_print(t, print_int_string_pair);
	
	key = malloc(sizeof(int));
	*key = 90187;
	value = make_string_copy("Umea (Universitet)");
	table_insert(t, key, value);

	printf("Table after adding a duplicate:\n");
	table_print(t, print_int_string_pair);

	v=90187;
	s=table_lookup(t,&v);
	printf("Lookup of postal code %d: %s.\n",v,s);

	table_kill(t);
}
