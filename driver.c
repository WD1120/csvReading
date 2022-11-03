/*----------------------------------------------------
..Project: dict1 dict2
  driver.c :
         = the implementation of the project

----------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

#include "list.h"
#include "data.h"
#include "array.h"

/* Constant definitions */
#define STAGE_1 1
#define STAGE_2 2
#define INITIAL_SIZE 1

/* Function prototypes */
int create_list (FILE *infile, list_t *cities);
void search_addr (FILE *outfile, list_t *cities);
void sort_grade1in (array_t *arr, list_t *cities, FILE *outfile);


/*==========================================================================
Main Function
==========================================================================*/
int main(int argc, char *argv[]) {
    int stage = atoi(argv[1]);
    FILE *infile;
    infile = fopen(argv[2], "r");
    assert(infile);
    FILE *outfile;
    outfile = fopen(argv[3], "w");
    assert(outfile);

    list_t *cities = make_empty_list();
    create_list(infile, cities);

    if (stage == STAGE_1) {
        search_addr(outfile, cities);
    }
    if (stage == STAGE_2) {
        array_t *sorted_arr = arrayCreate();
        sort_grade1in(sorted_arr, cities, outfile);
    }

    free_list(cities, string_free);
    fclose(infile);
    fclose(outfile);

    return 0;
}

/*==========================================================================
Funciton Definitions
==========================================================================*/

/* Reads the input file and creates a linked list */
int create_list (FILE *infile, list_t *lst) {
    
    int n = 0;
    int flag = 1;
    char header[MAX_LINE_LEN];
    fscanf(infile, " %[^\n]", header);

    data_t *d = malloc(sizeof(*d));
    assert(d);
    while (flag) {
        flag = read_record(infile, d);
        if (flag) {
            insert_at_foot(lst, *d);
            n++;
        } else {
            break;
        }
    }
    free(d);
    return n;
}

/* Search for the address input in stdin, prints out records that match. */
void search_addr (FILE *outfile, list_t *cities) {

    int found;
    int size = INITIAL_SIZE;
    int n = 0;
    char **addr_arr;
    char addr[MAX_STR_LEN+1];
    addr_arr = malloc(size * sizeof(char*));
    assert(addr_arr);
    while (scanf("%[^\n]\n", addr) != EOF) {
        if (n >= size - 1) {
            addr_arr = (char**)realloc(addr_arr, (size*2)*sizeof(char*));
            assert(addr_arr);
            size *= 2;
        }
        addr_arr[n] = strdup(addr);
        assert(addr_arr[n]);
        n++;
    }

    for (int i = 0; i < n; i++) {
        fprintf(outfile, "%s\n", addr_arr[i]);
        found = 0;
        node_t *node = get_head(cities);
        int num_node = 0;
        while (node) {
            if (strcmp(addr_arr[i], node->data.address) == 0) {
                print_record(outfile, &node->data);
                found += 1;
            }
            node = node->next;
            num_node++;
        }
        if (!found) {
            printf("%s --> NOTFOUND\n", addr_arr[i]);
        } else {
            printf("%s --> %d\n", addr_arr[i], found);
        }
    }

    for (int k = 0; k < n; k++) {
        free(addr_arr[k]);
    }
    free(addr_arr);   
}


/* Search for the record that has the closest grade1in value, and prints the 
redord out. */
void sort_grade1in (array_t *arr, list_t *lst, FILE *outfile) {

    node_t *node = get_head(lst);
    while (node) {
        sortedArrayInsert(arr, node);
        arrayShrink(arr);
        node = node->next;
    }

    int size = INITIAL_SIZE;
    int n = 0;
    double *grade1in_arr;
    double grade1in;
    grade1in_arr = malloc(size * sizeof(double));
    assert(grade1in_arr);
    while (scanf("%lf\n", &grade1in) != EOF) {
        if (n >= size - 1) {
            grade1in_arr = (double*)realloc(grade1in_arr, (size*2)*sizeof(double));
            assert(grade1in_arr);
            size *= 2;
        }
        grade1in_arr[n] = grade1in;
        n++;
    }

    for (int i = 0; i < n; i++) {
        double diff = get_grade1in(arr, get_num(arr)-1);
        double diff_temp = diff;
        int index = -1;
        for (int j = 0; j < get_num(arr); j++) {
            diff_temp = fabs(grade1in_arr[i] - get_grade1in(arr, j));
            if (diff_temp < diff && get_grade1in(arr, j) != 0) {
                diff = diff_temp;
                index = j;
            }
        }
        fprintf(outfile, "%g\n", grade1in_arr[i]);
        print_record(outfile, get_data(arr, index));
        printf("%g --> %.1lf\n", grade1in_arr[i], get_grade1in(arr, index));
    }
    free_arr(arr);
    free(grade1in_arr);
}
