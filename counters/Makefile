# Makefile for 'bag' module
#
# David Kotz, April 2016, 2017, 2019, 2021
# updated by Xia Zhou, July 2016, 2018, January 2019

OBJS = counters_test.o counters.o ../lib/file.o ../lib/mem.o 
LIBS =

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

counters_test: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

counters_test.o: counters.h ../lib/file.h
counters.o: counters.h
../lib/file.o: ../lib/file.h

.PHONY: test valgrind clean

# expects a file `test.names` to exist; it can contain any text.
test: counters_test test.names
	./counters_test < test.names

# expects a file `test.names` to exist; it can contain any text.
valgrind: counters_test test.names
	$(VALGRIND) ./counters_test < test.names

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f counters_test

