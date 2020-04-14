#ifndef _ARRAY_H_
#define _ARRAY_H_

#ifndef ARRAY_DEFAULT_SIZE
#define ARRAY_DEFAULT_SIZE 64
#endif

/**
 * struct to hold array information
 */
typedef struct {
	void **buffer;
	int refs;
	unsigned int buffer_size;
	unsigned int length;
} array;

/**
 * Create a new array with ARRAY_DEFAULT_SIZE buffer size
 *
 * @return array* The created array
 */
array* array_init ();

/**
 * Create a new array with a specific buffer size
 *
 * @param size The size of the array buffer
 *
 * @return array* The created array
 */
array* array_init_with_size (unsigned int size);

/**
 * Add an element to the end of the array
 *
 * @param self The array
 * @param data The element to be added to the end of the array
 */
void array_push (array* self, void* data);

/*
 * Add an element to the start of the array
 *
 * @param self The array
 * @param data The element to be added to the start of the array
 */
void array_unshift (array* self, void* data);

/**
 * Add an element to the array in a specific position. If there is any element in that position, it
 * and the following are moved one position forward
 *
 * @param self The array
 * @param index The position where the element will be added
 * @param data The element to be added to the end of the array
 */
void array_insert (array* self, unsigned int index, void* data);

/**
 * Retrieve an element from the array
 *
 * @param self The array
 * @param index|NULL The position of the element to be retrieved in the array or NULL if in that
 * position there is no element
 */
void *array_get (array* self, unsigned int index);

/**
 * Retrieve the first element from the array
 *
 * @param self The array
 */
void* array_first (array* self);

/**
 * Retrieve the last element from the array
 *
 * @param self The array
 */
void* array_last (array* self);


/**
 * Add an element to the array in a specific position. If there is any element in that position, it
 * is overwritten
 */
void array_put (array* self, unsigned int index, void* data);

/**
 * Check the position where an element is in the array
 *
 * @param self The array
 * @param data The element to be checked
 *
 * @return unsigned int The index of the element in the array or -1 if it does not exists
 */
int array_indexof (array* self, void* data);

/**
 * Check whether an element is in the array
 *
 * @param self The array
 * @param data The element to be checked
 *
 * @return int Whether the array contains an element (1) or not (0)
 */
int array_contains (array* self, void* data);

/**
 * Remove an element from array in a specific index
 *
 * @param self The array
 * @param index The index of the element in the array
 *
 * @return void*|NULL The removed element or NULL if no element found in that position
 */
void* array_remove (array* self, unsigned int index);

/**
 * Remove an element from array
 *
 * @param self The array
 * @param data The element to be removed from the array
 *
 * @return void*|NULL The removed element or NULL if it does not exist in the array
 */
void* array_remove_item(array* self, void* data);

/**
 * Remove the first element from the array
 *
 * @param self The array
 *
 * @return void*|NULL The removed element or NULL if no element found in first position
 */
void* array_shift (array* self);

/**
 * Remove the last element from the array
 *
 * @param self The array
 *
 * @return void*|NULL The removed element or NULLL if no element found in last position
 */
void* array_pop (array* self);

/**
 * Increase array references
 *
 * @param self The array
 *
 * @return array* The array
 */
array* array_incref (array* self);

/**
 * Decrease array references. If references go down to 0, the array buffer is flushed
 */
array* array_decref (array* self);

/**
 * Sort elements of the array
 *
 * @param array The array
 * @param sort Function passed to sort the array
 *
 * @return The array
 */
array* array_sort (array* self, int (*sort)(const void*, const void*));

/**
 * Applies the function to the elements of the array
 *
 * @param self The array
 * @param map Function to apply to the elements of the array
 *
 * @return The array
 */
array* array_map(array* self, void (*map)(int index, void* element));

#define array_length(self) self->length

#endif