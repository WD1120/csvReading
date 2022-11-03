/*----------------------------------------------------
..Project: dict2
  array.c :
         = the implementation of module array of the project

These functions are  modified based on the Workshop3
materials of COMP20003
----------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "array.h"
#include "data.h"
#include "list.h"

/* Structure definition */
struct array {
	node_t *A;         // use as array of student_t *, ie. student_t *A[]
	int size;           // current array size
	int n;              // current number of elements
};


/* Creates an empty array */
array_t *arrayCreate() {
	array_t *arr = malloc(sizeof(*arr));
	assert(arr);
	int size = INIT_SIZE;      // "size" used for convenience
	arr->size = size;
	arr->A = malloc(size * sizeof(*(arr->A)));
	assert(arr->A);
	arr->n = 0;
	return arr;
}


/* makes sure that array's size exceeds its number of elements */
void arrayEnsureSize(array_t *arr) {
	if (arr->n == arr->size) {
		arr->size <<= 1;       // same as arr->size *= 2;
		arr->A = realloc(arr->A, arr->size * sizeof(*(arr->A)));
		assert(arr->A);
	}
}


/* Inseart an element into an array, while maintain the array to be sorted */
void sortedArrayInsert(array_t *arr, node_t *s) {
	arrayEnsureSize(arr);
	int n = arr->n;
	int i;
	for (i=n-1; i>=0 && city_cmp_grade1in(&arr->A[i].data, &s->data) >= 0; i--) {
		arr->A[i+1] = arr->A[i];
	}
	arr->A[i+1] = *s;
	arr->n += 1;
}

/* Get the number of elements in the array */
int get_num(array_t *arr) {
    return arr->n;
}

/* Frees the array */
void free_arr(array_t *arr) {
    free(arr->A);
    free(arr);
}

/* Gets the grade1in value from the array */
double get_grade1in(array_t *arr, int i) {
    return arr->A[i].data.grade1in;
}

/* Gets the address of the data structure by specifying an index */
data_t *get_data(array_t *arr, int i){
    return &arr->A[i].data;
}


/* shrinks the array, to reduce array size to the same as the number 
of element used */
void arrayShrink(array_t *arr) {
	if (arr->size != arr->n) {
		// the new size should be at least INIT_SIZE
		arr->size = (arr->n > INIT_SIZE) ? arr->n : INIT_SIZE;
		arr->A = realloc(arr->A, arr->size * sizeof(*(arr->A)));
		assert(arr->A);
	}
}
