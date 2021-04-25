# Makefile for 'bag' module
#
# David Kotz, April 2016, 2017, 2019, 2021
# updated by Xia Zhou, July 2016, 2018, January 2019

OBJS = hashtable_test.o hashtable.o hash.o ../lib/file.o ../lib/mem.o ../set/set.o 
LIBS =

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

hashtable_test: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

hashtable_test.o: hashtable.h ../lib/file.h
hashtable.o: hashtable.h ../set/set.h
../lib/file.o: ../lib/file.h
../set/set.o: ../set/set.h

.PHONY: test valgrind clean

# expects a file `test.names` to exist; it can contain any text.
test: hashtable_test test.names
	./hashtable_test < test.names

# expects a file `test.names` to exist; it can contain any text.
valgrind: hashtable_test test.names
	$(VALGRIND) ./hashtable_test < test.names

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f hashtable.test

