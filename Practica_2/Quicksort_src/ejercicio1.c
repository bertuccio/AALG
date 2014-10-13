/***********************************************/
/* Programa: ejercicio1    Fecha: 19/09/2012   */
/* Autores: Adrián Lorenzo Mateo               */
/*	    Ari Handler Gamboa		       */
/*                                             */
/* Programa que genera numeros aleatorios      */
/* entre dos numeros dados                     */
/*                                             */
/* Entrada: Linea de comandos                  */
/* -limInf: limite inferior                    */
/* -limSup: limite superior                    */
/* -numN: cantidad de numeros                  */
/* Salida: 0: OK, -1: ERR                      */
/***********************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ordenar.h"

int main(int argc, char** argv)
{
  int i;
  unsigned int inf, sup, num, j;
  int aleat;

  srand(time(NULL));

  if (argc != 7) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -limInf <int> -limSup <int> -numN <int>\n", argv[0]);
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, " -limInf : Limite inferior.\n");
    fprintf(stderr, " -limSup : Limite superior.\n");
    fprintf(stderr, " -numN : Cantidad de numeros a generar.\n");
    exit(-1);
  }
  printf("Practica numero 1, apartado 1\n");
  printf("Realizada por: Ari Handler Gamboa y Adrián Lorenzo Mateo\n");
  printf("Grupo: 261\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-limInf") == 0) {
      inf = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-limSup") == 0) {
      sup = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numN") == 0) {
    if (strncmp(argv[++i], "-", 1) == 0){
            fprintf(stderr, "Parametro numN fuera del rango permitido\n");
            return -1;
        }
      num = atoi(argv[i]);
    } else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
    }
  }

    /* comprobamos los parametros de entrada */
  if (num <= 0){
      fprintf(stderr, "Parametros fuera del rango permitido\n");
      return -1;
  }
  /* imprimimos los datos */
  for(j = 0; j < num; j++) { 
  if((aleat=aleat_num(inf, sup))<0){
  	      fprintf(stderr, "Parametros fuera del rango permitido\n");
  	      return -1;
  }
    printf("%d\n",aleat);
  }

  return 0;
}

