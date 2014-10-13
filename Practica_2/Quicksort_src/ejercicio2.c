/********************************************************/
/* Programa: ejercicio2   Fecha: 19/09/2012             */
/* Autores: Adrián Lorenzo Mateo			*/
/*	    Ari Handler Gamboa				*/
/*							*/
/* Programa que genera permutaciones                    */
/* aleatorias                                           */
/*                                                      */
/* Entrada: Linea de comandos                           */
/* -tamanio: numero elementos permutacion               */
/* -numP: numero de permutaciones                       */
/* Salida: 0: OK, -1: ERR                               */
/********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ordenar.h"

int main(int argc, char** argv)
{
  int i;
  unsigned int num, tamanio, j, k;
  int* perm = NULL;

  srand(time(NULL));

  if (argc != 5) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -tamanio <int> -numP <int>\n", argv[0]);
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, " -tamanio : numero elementos permutacion.\n");
    fprintf(stderr, " -numP : numero de permutaciones.\n");
    exit(-1);
  }

  printf("Practica numero 1, apartado 2\n");
  printf("Realizada por: Ari Handler Gamboa y Adrián Lorenzo Mateo\n");
  printf("Grupo: 261\n\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-tamanio") == 0) {
        if (strncmp(argv[++i], "-", 1) == 0){
            fprintf(stderr, "Parametro tamanio fuera del rango permitido\n");
            return -1;
        }
      tamanio = atoi(argv[i]);
    } else if (strcmp(argv[i], "-numP") == 0) {
        if (strncmp(argv[++i], "-", 1) == 0){
            fprintf(stderr, "Parametro numP fuera del rango permitido\n");
            return -1;
        }
      num = atoi(argv[i]);	
    } else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
      return -1;
    }
  }
  
  /* comprobamos los parametros de entrada */
  if (tamanio <= 0 || num <= 0){
      fprintf(stderr, "Parametros fuera del rango permitido\n");
      return -1;
  }
  
  /* imprimimos el resultado */
  for(j = 0; j < num; j++) { 
    perm = genera_perm(tamanio);
    if (perm == NULL) { /* error */
      printf("Error: No hay memoria\n");
      exit(-1);
    } else {
      for(k = 0; k < tamanio; k++) { /* imprimimos cada elemento */
        printf("%d ", perm[k]);
      }
      printf("\n");
      free(perm); /* liberamos la permutacion */
    }
  }

  return 0;
}

