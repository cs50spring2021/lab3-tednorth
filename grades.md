# Student name
## Lab 3 grader notes

Recall the [Assignment](https://www.cs.dartmouth.edu/~cs50/Labs/lab2).

**Total: 80/100 points**

### set

26/28 points:

-2 : no comments incode
* 

### counters

27/30 points:

-1: counters_print should be formatted as "key=value"

-2 : no comments in code

* 

### hashtable

20/34 points:

-12 : Unfortunately your implementation of hashtable is not correct.
entries should be  hashed according to the total size of the hashtable, not
the total number of non-empty slots. Therefore your "count" variable is  superfluous, if not erroneous. To add insult to injuries, your hashtable_find should use ht->entries[i] in the while loop. Your current code results in an infinite loop.

-2: no comments in code

* 

### overall

7/8 points:


-1  : no top level readme

