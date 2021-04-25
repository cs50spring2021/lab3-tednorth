# Makefile for 'bag' module
#
# David Kotz, April 2016, 2017, 2019, 2021
# updated by Xia Zhou, July 2016, 2018, January 2019

OBJS = set_test.o set.o ../lib/file.o ../lib/mem.o 
LIBS =

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

set_test: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

set_test.o: set.h ../lib/file.h
set.o: set.h
../lib/file.o: ../lib/file.h

.PHONY: test valgrind clean

# expects a file `test.names` to exist; it can contain any text.
test: set_test test.names
	./set_test < test.names

# expects a file `test.names` to exist; it can contain any text.
valgrind: set_test test.names
	$(VALGRIND) ./set_test < test.names

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f set_test

