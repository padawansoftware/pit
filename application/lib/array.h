#ifndef ARRAY_LIST
#define ARRAY_LIST

#ifndef ARRAY_DEFAULT_SIZE
#define ARRAY_DEFAULT_SIZE 64
#endif

typedef struct {
	void **buffer;
	int refs;
	unsigned int buffer_size;
	unsigned int length;
} array;

array *array_init ();
array *array_init_with_size (unsigned int size);

void array_push (array *self, void *data);
void array_unshift (array *self, void *data);
void array_insert (array *self, unsigned int index, void *data);

void *array_get (array *self, unsigned int index);
void array_put (array *self, unsigned int index, void *data);

unsigned int array_indexof (array *self, void *data);
int array_contains (array *self, void *data);

void *array_remove (array *self, unsigned int index);
void *array_remove_item(array *self, void *data);
void *array_shift (array *self);
void *array_pop (array *self);

void *array_incref (array *self);
void array_decref (array *self);

void array_sort (array *self, int (*sort)(const void *, const void*));

#define array_length(self) self->length

#endif