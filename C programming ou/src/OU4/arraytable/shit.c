














void table_remove(table *t, const void *key)
{
	// Iterate over the list. Remove any entries with matching keys.

	dlist_pos pos = dlist_first(t->entries);

	while (!dlist_is_end(t->entries, pos)) {
		// Inspect the table entry
		struct table_entry *entry = dlist_inspect(t->entries, pos);

		// Compare the supplied key with the key of this entry.
		if (t->key_cmp_func(entry->key, key) == 0) {
			// If we have a match, call free on the key
			// and/or value if given the responsiblity
			if (t->key_free_func != NULL) {
				t->key_free_func(entry->key);
			}
			if (t->value_free_func != NULL) {
				t->value_free_func(entry->value);
			}
			// Remove the list element itself.
			pos = dlist_remove(t->entries, pos);
		} else {
			// No match, move on to next element in the list.
			pos = dlist_next(t->entries, pos);
		}
	}
return NULL;
