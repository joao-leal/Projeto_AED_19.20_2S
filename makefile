#   Compiler, Compiler Flags
CC = gcc
CFLAGS = -g -Wall -ansi -pedantic # !! -std=c99 -O3 !!

#   Sources
SOURCES = wordz.c list.c

#   Objects  ('Make' automatically compiles .c to .o)
OBJECTS_A = wordz.o list.o 

campista: $(OBJECTS_A)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS_A)

campista.o: wordz.c defs.h #list.h

list.o: list.c wordz.h #list.h 

clean:
	rm -f *.o *.~ *.gch