/*----------------------------------------------------
..Project: dict2
  array.h :
         = the interface of module array of the project
----------------------------------------------------*/


#ifndef _ARRAY_H_
#define _ARRAY_H_
#include "data.h"
#include "list.h"

#define INIT_SIZE 2     // initial size of arrays 
 
typedef struct array array_t;

array_t *arrayCreate();

// inserts/appends data "s" to the end of array "arr" 
void arrayAppend(array_t *arr, data_t *s);

// inserts data "s" into array "arr", ensuring "arr" is sorted 
void sortedArrayInsert(array_t *arr, node_t *s);

void arrayEnsureSize(array_t *arr);

int get_num(array_t *arr);

void free_arr(array_t *arr);

double get_grade1in(array_t *arr, int i);

data_t *get_data(array_t *arr, int i);

void arrayShrink(array_t *arr);

#endif