#   Compiler, Compiler Flags
CC = gcc
CFLAGS = -g -Wall -ansi -pedantic # !! -std=c99 -O3 !!

#   Sources
SOURCES = wordz.c graph.c

#   Objects  ('Make' automatically compiles .c to .o)
OBJECTS_A = wordz.o graph.o 

wordz: $(OBJECTS_A)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS_A)

wordz.o: wordz.c defs.h graph.h

#list.o: list.c wordz.h #list.h 

clean:
	rm -f *.o *.~ *.gch *.wordz0

FILES = $(shell ls ./primeiro/*.graph0)
OUTPUT = $(shell ls ./primeiro/*.wordz)
TEST = $(shell ls ./primeiro/*.wordz)


t:
	for F in ${FILES}; do ./wordz curto.dict $${F} ; done;

t2:
	for F in $(OUTPUT); do diff $${F} $${F} ; done;