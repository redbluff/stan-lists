# Basic makefile to handle our compilation and ousekeeping
#
CC = gcc
CFLAGS = -Wall -std=c99 -g 
OBJECTS = lists.o uteTest.o
EXE = ./testList
VALGRIND = valgrind --dsymutil=yes

testList : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXE)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(EXE) $(OBJECTS) *.dSYM


# Some valgrind, short and long versions

vals:
	$(VALGRIND) $(EXE)

vall:
	$(VALGRIND) --tool=memcheck --leak-check=yes --show-reachable=yes $(EXE) 

# Purge and recompile all, and then run the short valgrind

test: clean testList vals



