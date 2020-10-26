#/*
# * Archivo: Makefile
# * Autor: Sebastian Mancipe <sebastian.mancipe@correo.usa.edu.co>
# * Última Modificación: Octubre 13, 2020
# * ----------------------------------------------------------------
# * Este archivo automatiza el proceso de compilación del módulo e interfaz utilsMM
# * módulos personalizados.
# */

CC = gcc-10
CFLAGS = -Wall -g -fopenmp

PROGRAMS = algorithm_1 algorithm_2 algorithm_3
all = algorithm_1 algorithm_2 algorithm_3

start: algorithm_1 algorithm_2 algorithm_3 clean

algorithm_1: algorithm_1.o utilsMM.o
	$(CC) $(CFLAGS) -o algorithm_1 algorithm_1.o utilsMM.o

algorithm_1.o: algorithm_1.c utilsMM.h
	$(CC) $(CFLAGS) -c algorithm_1.c

algorithm_2: algorithm_2.o utilsMM.o
	$(CC) $(CFLAGS) -o algorithm_2 algorithm_2.o utilsMM.o

algorithm_2.o: algorithm_2.c utilsMM.h
	$(CC) $(CFLAGS) -c algorithm_2.c

algorithm_3: algorithm_3.o utilsMM.o
	$(CC) $(CFLAGS) -o algorithm_3 algorithm_3.o utilsMM.o

algorithm_3.o: algorithm_3.c utilsMM.h
	$(CC) $(CFLAGS) -c algorithm_3.c

utilsMM.o: utilsMM.c utilsMM.h
	$(CC) $(CFLAGS) -c utilsMM.c

clean:
	$(RM) *.o
