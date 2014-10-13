/**
 *
 * Descripcion: Implementacion de funciones de ordenacion 
 *
 * Fichero: ordenar.c
 * Autor: 
 * Version: 1.0
 * Fecha: 22-09-2011
 *
 */


#include "ordenar.h"
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <math.h>

/********************************************************/
/* Funcion: swap	Fecha: 19/09/2012		*/
/* Autores: Adrián Lorenzo Mateo			*/
/*	    Ari Handler Gamboa				*/
/*							*/                                       
/* Rutina que intercambia dos elementos de un array	*/
/* de enteros						*/
/*							*/
/* Entrada:						*/
/* int pos_1: posicion del primer elemento		*/
/* int pos_2: posicion del segundo elemento		*/
/* int * vector: array sobre el que se operara		*/
/* Salida:						*/
/* OK en caso de realizar el intercambio, ERR en	*/
/* caso contrario					*/
/********************************************************/

int swap(int pos_1, int pos_2, int *vector)
{
	int temp;
	
	if((vector == NULL) || ((pos_1 < 0) || (pos_2 < 0)))
		return ERR;

	temp = *(vector+pos_1);
	*(vector+pos_1) = *(vector+pos_2);
	*(vector+pos_2) = temp;
	
	return OK;
	
}

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
int aleat_num(int inf, int sup)
{
    /* Control de errores de los parametros de entrada*/
	if ((sup < inf) || (sup > RAND_MAX) || ((inf < 0 ) || 
			(sup < 0)) || (sup > RAND_MAX))
		return ERR;
    /*la función rand() limita el rango [0, 1) debido a la división entre RAND_MAX+1.
     * La segunda parte multiplica dicho valor por un número que se encuentre aproximadamente
     * en la mitad del rango (sup-inf +1), de este modo se normaliza el anterior valor 
     * acotándolo entre 0 y el número intermedio.  Sin embargo, es necesario sumar el límite 
     * inferior al resultado con el fin de que se obtenga un valor superior a este.*/    
    return (int)((rand()/(RAND_MAX+1.))*(sup-inf+1))+inf;
}

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
int* genera_perm(int n)
{
	int *array_perm = NULL;
	int i;

	/* Contro de errores de los parametros de entrada */
	if (n <= 0) 
		return NULL;

	/* Reserva y comprobacion de memoria de la permutacion */
	array_perm = (int *)malloc(n*sizeof(int));
	if (array_perm == NULL) 
			return NULL;
	
	/* Inicializacion del array */	
	for (i=0; i<n ;i++)
		array_perm[i] = i;

	/* Bucle de llenado del array aleatorio */
	for (i=0; i<n ;i++)
		/* Puesto que se opera con un array de n elementos
		   el limite superior del indice debe ser n-1 */
		swap(i,aleat_num(i,n-1),array_perm);

	return array_perm;
}

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
int** genera_permutaciones(int n_perms, int tamanio)
{
	int ** matriz_perm;
	int i, j;

	/* Control de errores de los parametros de entrada */
	if (n_perms <=0 || tamanio <= 0)
		return NULL;
		
	/* Reserva y comprobacion de memoria de la matriz de permutaciones */
	matriz_perm = (int **)malloc(n_perms*sizeof(int *));
	if (matriz_perm == NULL)
		return NULL;
	
	/* Bucle que por cada fila de la matriz genera una permutacion */
	for (i=0; i<n_perms ;i++){
		/* Reserva y comprobacion de cada una de las permutaciones*/
		matriz_perm[i] = genera_perm(tamanio);
		if (matriz_perm[i] == NULL){
			/* Si no se ha podido reservar una de las permutaciones se 
			 * liberan todas las reservadas de forma descendente */
			for (j=i; j>=0 ;j--){
				free(matriz_perm[j]);
			}
			free(matriz_perm);
			return NULL;
		}
	}       

	return matriz_perm;
}

