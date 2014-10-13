#-----------------------
# IMPORTANTE: Los valores de los parametros de los ejercicio?_test deben ajustarse.
# Se asume que los ficheros fuente se llaman ejercicio1.c, ejercicio2.c,...,ordenar.h
#-----------------------

CC = gcc -ansi -pedantic -g -lm
CFLAGS = -Wall
EXE = ejercicio1 ejercicio2 ejercicio2_1 ejercicio2_2

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o ordenar.o tiempos.o busqueda.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o ordenar.o tiempos.o busqueda.o

%.o : %.c ordenar.h tiempos.h busqueda.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

ejercicio1_test:
	@echo Ejecutando ejercicio1
	@./ejercicio1 -limInf 1 -limSup 5 -numN 10

ejercicio2_test:
	@echo Ejecutando ejercicio2
	@./ejercicio2 -tamanio 1 -numP 5

ejercicio3_test:
	@echo Ejecutando ejercicio3
	@./ejercicio3 -tamanio 1 -numP 5

ejercicio4_test:
	@echo Ejecutando ejercicio4
	@./ejercicio4 -tamanio 1

ejercicio5_test:
	@echo Ejecutando ejercicio5
	@./ejercicio5 -num_min 10000 -num_max 100000 -incr 1000 -numP 10 -fichSalida salida.dat -retardo 10
 
