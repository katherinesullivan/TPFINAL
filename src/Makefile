IDIR =../libs/
CFLAGS=-I$(IDIR) -Wall -Wextra

objects = conjunto.o interprete.o operaciones.o tablahash.o

.PHONY : all
all: interprete clean

interprete: $(objects)
	$(CC) -o main main2.c $(objects) $(CFLAGS)


operaciones.o: $(IDIR)operaciones.c $(IDIR)operaciones.h conjunto.o
	$(CC) -c $(IDIR)operaciones.c $(IDIR)conjunto.h
interprete.o: $(IDIR)operaciones.c $(IDIR)operaciones.h conjunto.o tablahash.o
	$(CC) -c $(IDIR)interprete.c $(IDIR)conjunto.h $(IDIR)tablahash.h
conjunto.o: $(IDIR)conjunto.c $(IDIR)conjunto.h
	$(CC) -c $(IDIR)conjunto.c
tablahash.o: $(IDIR)tablahash.c $(IDIR)tablahash.h
	$(CC) -c $(IDIR)tablahash.c

.PHONY : clean
clean:
	rm *.o