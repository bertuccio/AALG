/**
 *
 * Descripcion: Funciones de cabecera para ordenacion 
 *
 * Fichero: ordenar.h
 * Autor: 
 * Version: 1.0
 * Fecha: 22-09-2011
 *
 */

#ifndef ORDENA_H
#define ORDENA_H

/* constantes */

#define ERR -1
#define OK (!(ERR))


#include <limits.h>
#include <stdlib.h>
#include <string.h>

/* definiciones de tipos */

typedef struct tiempo {
  int n_perms;     /* numero de permutaciones */
  int tamanio;     /* tamanio de las permutaciones */
  double tiempo;   /* tiempo promedio */
  double medio_ob; /* numero premedio de veces que se ejecuta la OB */
  int min_ob;      /* minimo de ejecuciones de la OB */
  int max_ob;      /* maximo de ejecuciones de la OB */
} TIEMPO, *PTIEMPO;

typedef int (* pfunc_ordena)(int*, int, int);
typedef int (* pfunc_pivote)(int, int);


/* Funciones */

/***************************************************/
/* Funcion: aleat_num Fecha: 29/09/2012            */
/* Autores: Adrián Lorenzo Mateo                   */
/*	    Ari Handler Gamboa			   */
/*                                                 */
/* Rutina que genera un numero aleatorio           */
/* entre dos numeros dados                         */
/*                                                 */
/* Entrada:                                        */
/* int inf: limite inferior                        */
/* int sup: limite superior                        */
/* Salida:                                         */
/* int: numero aleatorio                           */
/***************************************************/
int aleat_num(int inf, int sup);

/***************************************************/
/* Funcion: genera_perm Fecha: 19/09/2012          */
/* Autores: Adrián Lorenzo Mateo                   */
/*	    Ari Handler Gamboa                     */
/*                                                 */
/* Rutina que genera una permutacion               */
/* aleatoria                                       */
/*                                                 */
/* Entrada:                                        */
/* int n: Numero de elementos de la                */
/* permutacion                                     */
/* Salida:                                         */
/* int *: puntero a un array de enteros            */
/* que contiene a la permutacion                   */
/* o NULL en caso de error                         */
/***************************************************/
int* genera_perm(int n);

/***************************************************/
/* Funcion: genera_permutaciones Fecha: 20/09/2012 */
/* Autores: Adrián Lorenzo Mateo                   */
/*	    Ari Handler Gamboa			   			   */
/*                                                 */
/* Funcion que genera n_perms permutaciones        */
/* aleatorias de tamanio elementos                 */
/*                                                 */
/* Entrada:                                        */
/* int n_perms: Numero de permutaciones            */
/* int tamanio: Numero de elementos de cada        */
/* permutacion                                     */
/* Salida:                                         */
/* int**: Array de punteros a enteros              */
/* que apuntan a cada una de las                   */
/* permutaciones                                   */
/* NULL en caso de error                           */
/***************************************************/
int** genera_permutaciones(int n_perms, int tamanio);


/****************************************************/
/* Funcion: SelectSort    Fecha: 26/10/2012         */
/* Autores: Adrián Lorenzo Mateo                    */
/*	    Ari Handler Gamboa                      */
/*                                                  */
/* Funcion que ordena un array de enteros haciendo  */
/* uso del método SelectSort, devolviendo el número */
/* de OBs durante la ejecución                      */
/*                                                  */
/* Entrada:                                         */
/* int tabla: Tabla a ordenar                       */
/* int ip: Primer elemento de la tabla              */
/* int iu: Ultimo elemento de la tabla              */
/* Salida:                                          */
/* int: Número de OBs ejecutadas o                  */
/* ERR en caso de error                             */
/****************************************************/
int SelectSort(int* tabla, int ip, int iu);


/********************************************************/ 
/* Funcion: tiempo_medio_ordenacion Fecha: 26/09/2012   */ 
/* Autores: Adrián Lorenzo Mateo                        */ 
/*	    Ari Handler Gamboa                          */ 
/*                                                      */ 
/* Funcion que calcula el tiempo medio de ordenacion    */ 
/* de una matriz de permutaciones aplicando el metodo   */ 
/* de ordenacion que se pasa como argumento,            */ 
/* rellenando una estructura tiempo con datos como      */ 
/* tiempo medio de ordenacion, promedio de Obs,         */ 
/* tamaño de las permutaciones, etc.                    */ 
/*                                                      */ 
/* Entrada:                                             */ 
/* pfunc_ordena metodo: Metodo de ordenacion que se     */ 
/* que se medirá.                                       */ 
/* int n_perms: Numero de permutaciones a utilizar      */ 
/* int tamanio: Numero de elementos de cada             */ 
/* permutacion                                          */ 
/* PTIEMPO ptiempo: Puntero a una estructura de tipo    */ 
/* TIEMPO que se rellenará una vez finalizada la        */ 
/* ejecucion de la rutina                               */ 
/* int n_veces: Numero de veces que se repetirá cada    */ 
/* ordenacion de la misma permutacion con el fin        */ 
/* de conseguir un retraso en el tiempo de ejecucion.   */ 
/*                                                      */ 
/* Salida:                                              */ 
/* ERR en caso de error y OK en el caso de que las      */ 
/* tablas se ordenen correctamente.                     */ 
/********************************************************/
short tiempo_medio_ordenacion(pfunc_ordena metodo, int n_perms,int tamanio, PTIEMPO ptiempo, int n_veces);


/********************************************************/ 
/* Funcion: genera_tiempos_ordenacion Fecha: 27/09/2012	*/ 
/* Autores: Adrián Lorenzo Mateo                      	*/ 
/*	    Ari Handler Gamboa				*/ 
/*                                                    	*/ 
/* Funcion que escribe en un fichero los tiempos y OBs	*/ 
/* evaluadas de un metodo de ordenacion con entradas	*/ 
/* de tamaño incremental.				*/ 
/*                                                    	*/ 
/* Entrada:                                           	*/ 
/* pfunc_ordena metodo: Metodo de ordenacion que se   	*/ 
/* que se medirá.		                      	*/ 
/* char* fichero: Fichero de salida de las mediciones	*/ 
/* int num_min: Tamaño inicial de las permutaciones	*/ 
/* int num_max: Tamaño maximo de las permutaciones	*/ 
/* int incr: Ratio de crecimiento del tamaño de las	*/ 
/* permutaciones					*/ 
/* int n_perms: Numero de permutaciones a utilizar    	*/ 
/* int n_veces: Numero de veces que se repetirá cada  	*/ 
/* ordenacion de la misma permutacion con el fin      	*/ 
/* de conseguir un retraso en el tiempo de ejecucion. 	*/ 
/*                                                    	*/ 
/* Salida:                                            	*/ 
/* ERR en caso de error y OK en el caso de que las	*/ 
/* tablas se ordenen correctamente y se escriba en el	*/ 
/* fichero.						*/ 
/********************************************************/
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero, int num_min, int num_max, int incr, int n_perms, int n_veces);


/********************************************************/ 
/* Funcion: guarda_tabla_tiempos Fecha: 28/09/2012	*/ 
/* Autores: Adrián Lorenzo Mateo                      	*/ 
/*	    Ari Handler Gamboa			      	*/ 
/*                                                    	*/ 
/* Funcion que imprime en un fichero la informacion que	*/ 
/* contiene una tabla de tiempos.			*/ 
/*                                                    	*/ 
/* Entrada:                                           	*/ 
/* char* fichero: Fichero de salida de las mediciones	*/ 
/* PTIEMPO tiempo: Tabla de tiempos a imprimir		*/ 
/* int N: Numero de elementos de la tabla de tiempos	*/ 
/*                                                    	*/ 
/* Salida:                                            	*/ 
/* ERR en caso de error y OK en el caso de que se la	*/ 
/* tabla de tiempos se escriba correctamente.		*/ 
/********************************************************/ 
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int N);

/****************************************************/
/* Funcion: MergeSort    Fecha: 17/10/2012         */
/* Autores: Adrián Lorenzo Mateo                    */
/*	    Ari Handler Gamboa                      */
/*                                                  */
/* Funcion que ordena un array de enteros haciendo  */
/* uso del método SelectSort, devolviendo el número */
/* de OBs durante la ejecución                      */
/*                                                  */
/* Entrada:                                         */
/* int tabla: Tabla a ordenar                       */
/* int ip: Primer elemento de la tabla              */
/* int iu: Ultimo elemento de la tabla              */
/* Salida:                                          */
/* int: Número de OBs ejecutadas o                  */
/* ERR en caso de error                             */
/****************************************************/
int mergesort(int* tabla, int ip, int iu);

/****************************************************/
/* Funcion: Merge    Fecha: 17/10/2012              */
/* Autores: Adrián Lorenzo Mateo                    */
/*	    Ari Handler Gamboa                      */
/*                                                  */
/* Funcion que ordena un array de enteros haciendo  */
/* uso del método SelectSort, devolviendo el número */
/* de OBs durante la ejecución                      */
/*                                                  */
/* Entrada:                                         */
/* int tabla: Tabla a ordenar                       */
/* int ip: Primer elemento de la tabla              */
/* int iu: Ultimo elemento de la tabla              */
/* Salida:                                          */
/* int: Número de OBs ejecutadas o                  */
/* ERR en caso de error                             */
/****************************************************/
int merge(int* tabla, int ip, int iu, int imedio);

/****************************************************/
/* Funcion: Partir    Fecha: 24/10/2012             */
/* Autores: Adrián Lorenzo Mateo                    */
/*	    Ari Handler Gamboa                      */
/*                                                  */
/* Funcion que redistribuye la tabla entre los      */
/* indices pasados por argumento,                   */
/*  dejando  a la izquierda                         */
/* los elementos menores que el                     */
/* pivote elegido por la función pivote y a la      */
/* derecha los mayores.                             */
/*                                                  */
/* Entrada:                                         */
/* int tabla: Tabla a redistribuir                  */
/* int ip: Primer elemento de la tabla              */
/* int iu: Ultimo elemento de la tabla              */
/* pivote: Función que elige un pivote              */
/* *ob_count: Contador de OBs                       */
/* Salida:                                          */
/* int: indice del pivote                           */
/****************************************************/
int partir(int* tabla, int ip, int iu, pfunc_pivote pivote);


/****************************************************/
/* Funcion: Quicksort    Fecha: 24/10/2012          */
/* Autores: Adrián Lorenzo Mateo                    */
/*	    Ari Handler Gamboa                      */
/*                                                  */
/* Funcion que ordena un array de enteros haciendo  */
/* uso del método Quicksort, devolviendo el número  */
/* de OBs durante la ejecución                      */
/*                                                  */
/* Entrada:                                         */
/* int tabla: Tabla a ordenar                       */
/* int ip: Primer elemento de la tabla              */
/* int iu: Ultimo elemento de la tabla              */
/* pfunc_pivote pivote: Funcion pivote              */
/* Salida:                                          */
/* int: Número de OBs ejecutadas o                  */
/* ERR en caso de error                             */
/****************************************************/
int quicksort(int* tabla, int ip, int iu, pfunc_pivote pivote);

/****************************************************/
/* Funcion: Quicksort1    Fecha: 24/10/2012         */
/* Autores: Adrián Lorenzo Mateo                    */
/*	    Ari Handler Gamboa                      */
/*                                                  */
/* Encapsulamiento de Quicksort para utilizar    */
/* la funcion medio como pivote                     */
/*                                                  */
/* Entrada:                                         */
/* int tabla: Tabla a ordenar                       */
/* int ip: Primer elemento de la tabla              */
/* int iu: Ultimo elemento de la tabla              */
/* Salida:                                          */
/* int: Número de OBs ejecutadas o                  */
/* ERR en caso de error                             */
/****************************************************/
int quicksort1(int* tabla, int ip, int iu);

/****************************************************/
/* Funcion: Quicksort2    Fecha: 31/10/2012         */
/* Autores: Adrián Lorenzo Mateo                    */
/*	    Ari Handler Gamboa                      */
/*                                                  */
/* Encapsulamiento de Quicksort para utilizar   */
/* la funcion aleat_num como pivote                     */
/*                                                  */
/* Entrada:                                         */
/* int tabla: Tabla a ordenar                       */
/* int ip: Primer elemento de la tabla              */
/* int iu: Ultimo elemento de la tabla              */
/* Salida:                                          */
/* int: Número de OBs ejecutadas o                  */
/* ERR en caso de error                             */
/****************************************************/
int quicksort2(int* tabla, int ip, int iu);

/****************************************************/
/* Funcion: Quicksort_src    Fecha: 4/11/2012         */
/* Autores: Adrián Lorenzo Mateo                    */
/*	    Ari Handler Gamboa                      */
/*                                                  */
/* Quicksort sin recursion de cola para evitar el*/
/* overhead. */
/*                                                  */
/* Entrada:                                         */
/* int tabla: Tabla a ordenar                       */
/* int ip: Primer elemento de la tabla              */
/* int iu: Ultimo elemento de la tabla              */
/* Salida:                                          */
/* int: Número de OBs ejecutadas o                  */
/* ERR en caso de error                             */
/****************************************************/
int quicksort_src(int* tabla, int ip, int iu);
#endif
