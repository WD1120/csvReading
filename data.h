/*----------------------------------------------------
..Project: dict1 dict2
  data.h :
         = the interface of module data of the project
----------------------------------------------------*/

#ifndef _DATA_H_
#define _DATA_H_

// constant definitions
#define MAX_STR_LEN 128
#define MAX_LINE_LEN 512

// list definitions
typedef struct data {
    int footpath_id;
    char *address;
    char *clue_sa;
    char *asset_type;
    double deltaz;
    double distance;
    double grade1in;
    int mcc_id;
    int mccid_int;
    double rlmax;
    double rlmin;
    char *segside;
    int statusid;
    int streetid;
    int street_group;
    double start_lat;
    double start_lon;
    double end_lat;
    double end_lon;
} data_t;

// Function prototypes
int read_record (FILE *f, data_t *d);

void* read_string(FILE *f, char* str);

void print_record(FILE *f, data_t *d);

int city_cmp_grade1in(data_t *A, data_t *B);

void *string_free(void *s);

#endif