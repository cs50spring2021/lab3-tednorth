/*
 * Name:        set.c
 * Author:      Ted Northup, 4/20/2021, 21S
 * Description: This program implements the set module functionality 
 * Notes:       see set.h for more information
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"
#include "mem.h"


/************* Local Types *************/

typedef struct setnode {
    
    char* key;
    void* item;
    struct setnode *next;

} setnode_t;


/************* Global Types ***********/

typedef struct set {

    struct setnode *head;

} set_t;


/************ Global Functions *************/

/************ Local Functions *************/

static setnode_t* setnode_new(const char* key, void* item);

/************ set_new() *****************/

set_t* set_new(void) {
    
    set_t* temp_set = mem_malloc(sizeof(set_t));
    if (temp_set == NULL) {
        return NULL;
    } else {
        temp_set->head = NULL;
        return temp_set;
    }


}

/*********** setnode_new() ************/

setnode_t* setnode_new(const char* key, void* item) {

    setnode_t* node = mem_malloc(sizeof(setnode_t));
    char* placeholder = mem_malloc(sizeof(key));
    strcpy(placeholder,key);

    if (node == NULL) {
        return NULL;
    } else {
        node->key = placeholder;
        node->item = item;
        node->next = NULL;
        return node;
    }
}

/************* set_insert() ***************/

bool set_insert(set_t* set, const char* key, void* item) {
    if (set == NULL || item == NULL || key == NULL) {
        return false;
    } else {
        if (set_find(set, key) != NULL) {        // set iterate function to check if a key is equal to the key encountered
            return false;
        } else {
            setnode_t* new = setnode_new(key, item);
            new->next = set->head;
            set->head = new;
            return true;     
        }
    }
}

/************** set_find() *************/

void* set_find(set_t* set, const char* key) {

    if (set == NULL || key == NULL) {
        return NULL;
    } else {
        for (setnode_t* node = set->head; node != NULL; node = node->next) {
            if (strcmp(node->key,key) == 0) {
                printf("Equal keys!\n");
                return(node->item);
            }
        }
        return NULL;
    }
    return NULL;        // should never reach
}

/************** set_print() **************/

void set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item)) {

    if (fp != NULL) {
        if (set != NULL) {
            fputc('{', fp);
            for (setnode_t* node = set->head; node != NULL; node = node->next) {
                fputc('(', fp);
                if (itemprint != NULL) {
                    (*itemprint)(fp, node->key, node->item);
                }
                fputs("),", fp);
            }
            fputc('}', fp);
        } else {
            fputs("(null)", fp);
        }
    }
}

/************ set_iterate() *************/

void set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) ) {

    if (set != NULL && itemfunc != NULL) {
        for (setnode_t* node = set->head; node != NULL; node = node->next){
            (*itemfunc)(arg, node->key, node->item);
        }
    }   
}

/*********** set_delete() *************/

void set_delete(set_t* set, void (*itemdelete)(void* item)) {

    if (set != NULL) {
        for (setnode_t* node = set->head; node != NULL; ){
            if (itemdelete != NULL) {
                (*itemdelete)(node->item);
            }
            mem_free(node->key);
            setnode_t* next = node->next;
            mem_free(node);           
            node = next;
            
        }
    }
    mem_free(set);
}






























