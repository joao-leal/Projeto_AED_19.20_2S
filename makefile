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
	rm -f *.o *.~ *.gch