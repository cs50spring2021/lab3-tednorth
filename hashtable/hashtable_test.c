/*
 * Ted Northup, CS50, 21S
 * This is a program that tests out the functionality of the hashtable module 
 * implemented in hashtable.c
 * 
 *
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../set/set.h"
#include "mem.h"
#include "file.h"
#include "hash.h"
#include "hashtable.h"

void printFunc (FILE *fp, const char* key, void* item);
static void countFunc (void* arg, const char* key, void* item);
void deleteFunc (void* item);

int main (void) {

    hashtable_t* ht1 = NULL;  
    char* name = "Professor Kotz";
    char* name2 = "Hunter";
    const char* key1 = "first_key";
    const char* key2 = "second_key";
   
    int keycount = 0;

    printf("Create the first hashtable...\n");
    ht1 = hashtable_new(12);
    printf("we've created the 1st ht\n");
    if (ht1 == NULL) {
        fprintf(stderr, "hashtable_new() failed for ht1\n");
        return 1;
    }
    
    printf("\nTest with null key, good item...\n");
    hashtable_insert(ht1, NULL, name);
    printf("test with good key, null item...\n");
    hashtable_insert(ht1, key1, NULL);
    printf("test with null key, null item...\n");
    hashtable_insert(ht1, NULL, NULL);

    printf("\nThe hashtable:\n");
    hashtable_print(ht1, stdout, printFunc); 
    
    hashtable_insert(ht1,key1,name);
    printf("Insert successful\n");
    hashtable_insert(ht1,key2,name2);
    printf("Insert succesful\n");
    
    hashtable_iterate(ht1, &keycount, countFunc);

    printf("\nThe hashtable:\n");
    hashtable_print(ht1, stdout, printFunc);

    char* find_result = hashtable_find(ht1,key1);
    printf("\nResult of find is: %s\n",find_result);

    hashtable_delete(ht1, deleteFunc);
    return 0;
}

// count the number of items in the set  
static void countFunc (void* arg, const char* key, void* item) {
    int* nitems = arg;
    if (nitems != NULL && item != NULL) {
        (*nitems)++;
    }
}

// print the item associated with a given key
void printFunc (FILE *fp, const char* key, void* item) {
    
    char* term = item;
    if (term == NULL) {
        fprintf(fp,"%s,(null)", key);
    } else {
        fprintf(fp,"%s,%s", key, term);
    }

}

// free the memory associated with a key's item
void deleteFunc (void* item) {
    if (item != NULL) {
        free(item);
    }
}


