/*
 *
 * Ted Northup, CS50, 21S
 * This program tests out the functionality of the counters 
 * module implemented for Lab 3
 * Credits: the tests were based partially off Professor Kotz's
 * tests for the bag module
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "counters.h"
#include "file.h"
#include "mem.h"

static void countFunc (void* arg, const char* key, void* item);

int main (void) {

    counters_t* counter1 = NULL;
    int count1 = 8;
    int keycount = 0;
    int key_input1 = 3;
    int key_input2 = 5;

    printf("Create first counter set...\n");
    counter1 = counters_new();
    if (counter1 == NULL) {
       fprintf(stderr, "counters_new failed for counter1\n");
       return 1;
    }

    printf("\nTest with null counter set, good key...\n");
    counters_add(NULL,key_input1);
    printf("Test with negative key...\n");
    counters_add(counter1,-2);
    printf("Test with null counter set, negative key...\n");
    counters_add(NULL,-2);

    printf("\nKey count (should be zero): ");
    counters_iterate(counter1,&keycount,countFunc);
    printf("%d\n", keycount);
    
    printf("\nThe counter set:\n");
    counters_print(counter1,stdout);

    printf("\nTesting counters_add...\n");
    counters_add(counter1, key_input1);
    keycount++;

    printf("\nKey count (should be 1): ");
    counters_iterate(counter1, &keycount, countFunc);
    printf("%d\n", keycount);

    printf("\nThe counter set:\n");
    counters_print(counter1,stdout);
     
    counters_add(counter1, key_input2);
    keycount++;

    printf("\nThe counter set:\n");
    counters_print(counter1,stdout);

    counters_add(counter1, key_input2);
    printf("\nThe counter set:\n");
    counters_print(counter1,stdout);

    printf("\nRetrieve from counter1...\n");
    int curr_count;
    curr_count = counters_get(counter1, key_input1);
    printf("The count associated with key %d is %d\n", key_input1, curr_count);
    curr_count = counters_get(counter1, key_input2);
    printf("The count associated with key %d is %d\n", key_input2, curr_count);

    printf("\nTesting counters_set(), by altering key %d...\n", key_input1);
    counters_set(counter1, key_input1, count1);
    
    printf("\nThe counter set:\n");
    counters_print(counter1,stdout);

    counters_delete(counter1);

    return 0;
}

// count the number of items in the set  
static void countFunc (void* arg, const char* key, void* item) {
    int* nitems = arg;
    if (nitems != NULL && item != NULL) {
        (*nitems)++;
    }
}



