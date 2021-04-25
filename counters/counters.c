/*
 *
 * Ted Northup, CS50, 21S
 * This program implements the functionality of a counters module
 *
 *
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "counters.h"
#include "mem.h"

/************* Local Types ************/

typedef struct countersnode {
    
    int key;
    int counter;
    struct countersnode *next;

} countersnode_t;

/************* Global Types *************/

typedef struct counters {

    struct countersnode *head;

} counters_t;

/************* Global Functions ************/

/************ Local Functions ************/

static countersnode_t* countersnode_new(const int key);


/************ counters_new() ************/

counters_t* counters_new(void) {

    counters_t* counters = mem_malloc(sizeof(counters_t));

    if (counters == NULL) {
        return NULL;
    } else {
        counters->head = NULL;
        return counters;
    }
}

/*************** countersnode_new() *************/

countersnode_t* countersnode_new(const int key) {
    
    countersnode_t* node = mem_malloc(sizeof(countersnode_t));

    if (node == NULL) {
        return NULL;
    } else {
        node->key = key;
        node->counter = 0;
        node->next = NULL;
        return node;
    }
    

}


/************ counters_add() ************/
int counters_add(counters_t* ctrs, const int key) {

    if (ctrs == NULL || key < 0) {
        return 0;
    } else {
        for (countersnode_t* node = ctrs->head; node != NULL; node = node->next) {
            if (node->key == key) {
                (node->counter)++;
                return((node->counter));    
            }
        }

        countersnode_t* new = countersnode_new(key);
        new->next = ctrs->head;
        ctrs->head = new;
        return((new->counter));   

    }
}


/************ counters_get() ************/

int counters_get(counters_t* ctrs, const int key) {
    
    if (ctrs == NULL || key < 0) {
        return 0;
    } else {
        for (countersnode_t* node = ctrs->head; node != NULL; node = node->next) {
            if (node->key == key) {
                return((node->counter));
            }
        } 
        return 0;                       // if the key has not been found, return 0
    }
}

/************* counters_set() ***********/

bool counters_set(counters_t* ctrs, const int key, const int count) {

    if (ctrs == NULL || key < 0 || count < 0) {
        return false;
    } else {
        for (countersnode_t* node = ctrs->head; node != NULL; node = node->next) {
            if (node->key == key) {
                (node->counter) = count;
                return true;
            }
        }
        countersnode_t* new = countersnode_new(key);
        new->next = ctrs->head;
        (new->counter) = count;
        ctrs->head = new;
        return true;

    }

 }

/************* counters_print() **********/

void counters_print(counters_t* ctrs, FILE* fp) {
    
    if (fp != NULL) {
        if (ctrs != NULL) {
            fputc('{',fp);
            for (countersnode_t* node = ctrs->head; node != NULL; node = node->next) {
                fputc('(',fp);
                fprintf(fp,"%d,%d", node->key, node->counter);
                fputc(')',fp);
            }   
            fputc('}',fp);
        } else {
            fputs("(null",fp);
        }
    }

}

/************ counters_iterate() ***********/
void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count)) {

    if (ctrs != NULL && itemfunc != NULL) {
        for (countersnode_t* node = ctrs->head; node != NULL; node = node->next) {
            (*itemfunc)(arg, node->key, node->counter);
        }
    }
}


/************ counters_delete() ***********/
void counters_delete(counters_t* ctrs) {
    
    if (ctrs != NULL) {
        mem_free(ctrs);
    }

}







