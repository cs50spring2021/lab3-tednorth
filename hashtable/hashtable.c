/*
 *
 * Ted Northup, CS50, 21S
 * Implements a hashtable and certain functionality
 * See hashtable.h for more information
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hashtable.h"
#include "mem.h"
#include "../set/set.h"
#include "hash.h"


/************* Global Types **************/
typedef struct hashtable {
    
    struct set **entries;

} hashtable_t;

/************* hashtable_new() ***********/

hashtable_t* hashtable_new(const int num_slots) {

    hashtable_t* hashtable = mem_malloc(sizeof(hashtable));   
    if (hashtable == NULL) {
        return NULL;
    } else {
        hashtable->entries = mem_calloc(num_slots,sizeof(set_t*));
        for (int i = 0; i < num_slots; i++) {
            hashtable->entries[i] = set_new();
        }
        return hashtable;
    }
}

/************** hashtable_insert() ************/

bool hashtable_insert(hashtable_t* ht, const char* key, void* item){
    
    if (ht == NULL || key == NULL || item == NULL) {
        return false;
    } else {
        int index;
        char* placeholder = mem_malloc(sizeof(key));
        strcpy(placeholder, key);
        
        int count = 0;
        int i = 0;
        
        while (ht->entries[i] != NULL) {
            count++;
            i++;    
        }

        index = hash_jenkins(key, count);
        return (set_insert(ht->entries[index], placeholder, item));

    }

}

/************ hashtable_find() ****************/

void* hashtable_find(hashtable_t* ht, const char* key){

    if (ht == NULL || key == NULL) {
        return NULL;
    } else {
        int index;
        char* placeholder = mem_malloc(sizeof(key));
        strcpy(placeholder, key);

        int count = 0;
        int i = 0;

        while (ht->entries != NULL) {
            count++;
            i++;
        }

        index = hash_jenkins(key,count); 
        return (set_find(ht->entries[index], placeholder));

    }

}


/************* hashtable_print() ***************/

void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item)){

    if (fp != NULL) {
        if (ht != NULL) {
            int count = 0;
            int i = 0;
            while (ht->entries[i] != NULL) {
                count++;
                i++;
            }
            printf("count is: %d",count);
            for (int j = 0; j < count; j++) {
                if (itemprint == NULL) {
                    fputs("Slot could not print\n",fp);
                } else {
                    fprintf(fp,"Slot %d ", j);
                    set_print(ht->entries[j], fp, (*itemprint));
                    fputs("\n", fp);
                }    
            }
        fputs("(null)",fp);
        }   
    }

}

/************ hashtable_iterate() **************/

void hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item)){

    if (ht != NULL && itemfunc != NULL) {  
        
        int count = 0;
        int i = 0;
        while (ht->entries[i] != NULL) {
            count++;
            i++;
        }

        for (int j = 0; j < count; j++) {
            set_iterate(ht->entries[j], arg, (*itemfunc));
        }
    }
}

/************* hashtable_delete() ****************/

void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) ) {

    if (ht != NULL) {
        
        int count = 0;
        int i = 0;
        while (ht->entries[i] != NULL) {
            count++;
            i++;
        }

        for (int j = 0; j < count; j++) {
            if (ht->entries[j] != NULL) {
                set_delete(ht->entries[j],(*itemdelete));
            }
        }
        mem_free(ht->entries);
    }
    mem_free(ht);
}








