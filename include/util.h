#ifndef __UTIL_H
#define __UTIL_H

/*
 * Utility function types for e.g. deallocating and printing values.
 */

// Type definition for de-allocator function, e.g. free().
typedef void (*free_function)(void *);

// Type definition for read-only callback for single-value containers,
// used by e.g. print functions.
typedef void (*inspect_callback)(const void *);

// Ditto for dual-value containers.
typedef void (*inspect_callback_pair)(const void *, const void *);

// Type definition for comparison function, used by e.g. table.
typedef int compare_function(const void *,const void *);

#endif
