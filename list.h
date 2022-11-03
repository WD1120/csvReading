/*----------------------------------------------------
..Project: dict1 dict2 dict3 dict4
  list.h :
         = the interface of module list of the project
----------------------------------------------------*/

#ifndef _LIST_H_
#define _LIST_H_
#include "data.h"

/* Structure definitions */
typedef struct {
    data_t data;
    node_t *next;
} node_t;

typedef struct list list_t;

/* Function prototypes */
/*==========================================================================*/


/* Create an empty list */
list_t *make_empty_list(void);

/* Checks if the list is empty */
int is_empty_list(list_t *list);

/* Frees the list */
void free_list(list_t *list, void (*dataFreeFunc)(void *));

/* Inseart an element into the beginning of the list */
list_t *insert_at_head(list_t *list, data_t value);

/* Inseart an element at the end of the list */
list_t *insert_at_foot(list_t *list, data_t value);

/* Get the head node of the list */
node_t *get_head(list_t *list);

/* Get the tail node of the list */
list_t *get_tail(list_t *list);

#endif