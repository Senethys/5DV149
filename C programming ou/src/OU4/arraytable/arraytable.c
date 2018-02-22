#include <stdlib.h>
#include <stdio.h>
#include "array_1d.h"
#include "table.h"
#include <string.h>



/*
 * Implementation of a generic table for the "Datastructures and
 * algorithms" courses at the Department of Computing Science, Umea
 * University.
 *
 * Duplicates are handled by inspect and remove.
 *
 * Authors: Niclas Borlin (niclas@cs.umu.se)
 *	    Adam Dahlgren Lindstrom (dali@cs.umu.se)
 *
 * Based on earlier code by: Johan Eliasson (johane@cs.umu.se).
 *
 * Version information:
 *   2018-02-06: v1.0, first public version.
 */

// ===========INTERNAL DATA TYPES============

struct table {
	array_1d *entries;
	compare_function *key_cmp_func;
	free_function key_free_func;
	free_function value_free_func;
};

struct table_entry {
	void *key;
	void *value;
};

#define LOW 1
#define HIGH 1000

// ===========INTERNAL FUNCTION IMPLEMENTATIONS============

/**
 * table_empty() - Create an empty table.
 * @key_cmp_func: A pointer to a function to be used to compare keys.
 * @key_free_func: A pointer to a function (or NULL) to be called to
 *		   de-allocate memory for keys on remove/kill.
 * @value_free_func: A pointer to a function (or NULL) to be called to
 *		     de-allocate memory for values on remove/kill.
 *
 * Return: Pointer to a new table.
 */
table *table_empty(compare_function *key_cmp_func,
		   free_function key_free_func,
		   free_function value_free_func)
{
	table *t = calloc(sizeof(table), 1);
	// Allocate space.
	t->entries = array_1d_create(free,LOW,HIGH);
	// Create the list to hold the table_entry-ies.
	t->key_cmp_func = key_cmp_func;
	t->key_free_func = key_free_func;
	t->value_free_func = value_free_func;

	return t;
}

/**
 * table_is_empty() - Check if a table is empty.
 * @table: Table to check.
 *
 * Return: True if table contains no key/value pairs, false otherwise.
 */
bool table_is_empty(const table *t)
{
	bool flag = true;
	for (int i=array_1d_low(t->entries); i<=array_1d_high(t->entries); i++) {
		bool has_val = array_1d_has_value(t->entries, i);
		if(has_val) {
			flag = false;
			break;
		}
	}
	return flag;
}

/**
 * table_insert() - Add a key/value pair to a table.
 * @table: Table to manipulate.
 * @key: A pointer to the key value.
 * @value: A pointer to the value value.
 *
 * Insert the key/value pair into the table. No test is performed to
 * check if key is a duplicate. table_lookup() will return the latest
 * added value for a duplicate key. table_remove() will remove all
 * duplicates for a given key.
 *
 * Returns: Nothing.
 */
void table_insert(table *t, void *key, void *value)
{
	// Allocate the key/value structure.
	struct table_entry *entry = malloc(sizeof(struct table_entry));

	entry->key = key;
	entry->value = value;

	//whilte low to high is not null
	for (int i=array_1d_low(t->entries); i<=array_1d_high(t->entries); i++) {
		bool has_val = array_1d_has_value(t->entries, i);
		if(!has_val) {
			array_1d_set_value(t->entries, entry, i);
			break;
		}
	}
}

/**
 * table_lookup() - Look up a given key in a table.
 * @table: Table to inspect.
 * @key: Key to look up.
 *
 * Return: The value corresponding to a given key, or NULL if the key
 * is not found in the table. If the table contains duplicate keys,
 * the value that was latest inserted will be returned.
 */
void *table_lookup(const table *t, const void *key)
{
	int i=array_1d_low(t->entries);
	void *result = NULL;
	//Iterate over the list. Return first match.
	while (i <= array_1d_high(t->entries)) {

		struct table_entry *entry = array_1d_inspect_value(t->entries, i);
		bool array_check = array_1d_has_value(t->entries, i);

			if(array_check == true){
				int key_cmp_check = t->key_cmp_func(entry->key, key);
				if (key_cmp_check == 0) {
					result = entry->value;
					return result;
				}
			}
		i++;
	}
	return result;
}

/**
 * table_remove() - Remove a key/value pair in the table.
 * @table: Table to manipulate.
 * @key: Key for which to remove pair.
 *
 * Any matching duplicates will be removed. Will call any free
 * functions set for keys/values. Does nothing if key is not found in
 * the table.
 *
 * Returns: Nothing.
 */
void table_remove(table *t, const void *key)
{
	// Iterate over the list. Remove any entries with matching keys.

// 	dlist_pos pos = dlist_first(t->entries);
//
// 	while (!dlist_is_end(t->entries, pos)) {
// 		// Inspect the table entry
// 		struct table_entry *entry = dlist_inspect(t->entries, pos);
//
// 		// Compare the supplied key with the key of this entry.
// 		if (t->key_cmp_func(entry->key, key) == 0) {
// 			// If we have a match, call free on the key
// 			// and/or value if given the responsiblity
// 			if (t->key_free_func != NULL) {
// 				t->key_free_func(entry->key);
// 			}
// 			if (t->value_free_func != NULL) {
// 				t->value_free_func(entry->value);
// 			}
// 			// Remove the list element itself.
// 			pos = dlist_remove(t->entries, pos);
// 		} else {
// 			// No match, move on to next element in the list.
// 			pos = dlist_next(t->entries, pos);
// 		}
// 	}
return NULL;
}

/*
 * table_kill() - Destroy a table.
 * @table: Table to destroy.
 *
 * Return all dynamic memory used by the table and its elements. If a
 * free_func was registered for keys and/or values at table creation,
 * it is called each element to free any user-allocated memory
 * occupied by the element values.
 *
 * Returns: Nothing.
 */
void table_kill(table *t)
{
	array_1d_kill(t->entries);
	free(t);
}


void table_print(const table *t, inspect_callback print_func)
 {

	 array_1d_print(t->entries ,print_func);
}
