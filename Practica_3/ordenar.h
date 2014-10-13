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

typedef int (* pfunc_ordena)(int*, int, int);
typedef int (* pfunc_pivote)(int, int);


/* Funciones */
int swap(int pos_1, int pos_2, int *vector);

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


#endif
