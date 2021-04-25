/*
 *
 * Ted Northup, set_test.c
 * CS50, 21S
 * Program is a testing program to see if all the functionality of 
 * a set module runs
 * Credits: test based off test run by Professor Kotz in the provider
 * bag module
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"
#include "file.h"
#include "mem.h"

static void countFunc (void* arg, const char* key, void* item);
void printFunc (FILE *fp, const char* key, void* item);
void deleteFunc (void* item);

int main (void) {

    set_t* set1 = NULL;           // one set
    char* name = NULL;            // a name in the set
    int namecount = 0;            // number of names put in the set
    int setcount = 0;             // number of names found in a set

    printf("Create first set...\n");
    set1 = set_new();
    if (set1 == NULL) {
        fprintf(stderr, "set_new failed for set1\n");
            return 1;
    }
    
    printf("\nTest with null set, good item...\n");
    set_insert(NULL, "key1", "Dartmouth");
    printf("test with null item...\n");
    set_insert(set1, "key2", NULL);
    printf("test with null bag, null item...\n");
    set_insert(NULL, "key3", NULL);

    printf("\nCount (should be zero): ");
    setcount = 0;
    set_iterate(set1, &setcount, countFunc);
    printf("%d\n", setcount);

    printf("\nTesting set_insert...\n");
    
    namecount = 0;
    const char* my_key = "key4"; 
    printf("namecount = 0\n");
    
    // read lines from stdin
    while (!feof(stdin)) {
        
        name = file_readLine(stdin);
        if (name != NULL) {
            
            set_insert(set1, my_key, name);
            namecount++;
              
        }     
    }
    
    printf("\nCount (should be %d): ", namecount);
    setcount = 0;
    set_iterate(set1, &setcount, countFunc);
    printf("%d\n", setcount);
    
    printf("\nThe set:\n");
    set_print(set1, stdout, printFunc);
    printf("\n");
    
    printf("\nMove items to a new set...\n");
    
    printf("\nThe old set:\n");
    printf("Count (should be zero): ");
    setcount = 0;
    set_iterate(set1, &setcount, countFunc);
    printf("%d\n", setcount);
    set_print(set1, stdout, printFunc);
    printf("\n");
        
    printf("\ndelete the sets...\n");
    set_delete(set1, deleteFunc);

    return 0;
}

// count the number of items in the set  
static void countFunc (void* arg, const char* key, void* item) {
    int* nitems = arg;
    if (nitems != NULL && item != NULL) {
        (*nitems)++;
    }
}

// print the item associated with a key
void printFunc (FILE *fp, const char* key, void* item) {
    
    char* term = item;
    if (term == NULL) {
        fprintf(fp,"%s,(null)", key);
    } else {
        fprintf(fp,"%s,%s", key, term);
    }

}

// free the memory associated with a key
void deleteFunc (void* item) {
    //printf("Got into the delete func\n");
    if (item != NULL) {
        //printf("the item is not equal to null\n");
        mem_free(item);
        //printf("item has been freed\n");
    }
}



