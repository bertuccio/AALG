/**
 *
 * Descripcion: Implementacion funciones para medicion de tiempos
 *
 * Fichero: tiempos.c
 * Autor: Ari Handler y Adrián Lorenzo
 * Version: 1.0
 * Fecha: 21-11-2012
 *
 */
#include "tiempos.h"
#include "busqueda.h"
#include "ordenar.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>



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
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int N)
{
    FILE * fichero_out = NULL;
    int i;
    
    /* Control de errores de los parametros de entrada */ 
    if (fichero == NULL || tiempo == NULL || N <= 0)
		return ERR;
    
    if ((fichero_out = fopen(fichero, "w")) == NULL)
		return ERR;

    fprintf(fichero_out, "#Tamano\tTiempo medio\tMedio OB\tMaximo OB\tMinimo OB\n");
    /* Impresion de la tabla de tiempos */ 
    for (i=0; i<N ;i++){
		fprintf(fichero_out, "%d\t%.7f\t%.7f\t%d\t%d\n", 
			tiempo[i].tamanio, tiempo[i].tiempo, tiempo[i].medio_ob,
			tiempo[i].max_ob, tiempo[i].min_ob);
	}
    
    fclose(fichero_out);
    
    return OK;
}

/********************************************************/ 
/* Funcion: genera_tiempos_busqueda Fecha: 22/11/2012   */ 
/* Autores: Adrián Lorenzo Mateo                        */ 
/*	    Ari Handler Gamboa								*/ 
/*                                                      */ 
/* Funcion que escribe en un fichero los tiempos y OBs	*/ 
/* evaluadas de un metodo de busqueda con entradas		*/ 
/* de tamaño incremental y un generador de claves dado.	*/
/*                                                      */ 
/* Entrada:                                             */ 
/* pfunc_ordena metodo: Metodo de busqueda que se		*/ 
/* que se medirá.                                       */
/* pfunc_generador_claves: Generador de claves a		*/
/* utilizar.											*/
/* int orden: Indica si se utilizaran tablas ordenadas.	*/
/* char* fichero: Fichero de salida de las mediciones.	*/
/* int num_min: Tamaño inicial de las permutaciones.	*/ 
/* int num_max: Tamaño maximo de las permutaciones.		*/ 
/* int incr: Ratio de crecimiento del tamaño de las		*/ 
/* permutaciones.										*/
/* double fclaves: Factor que indica el numero de claves*/
/* que se buscaran en cada permutacion.					*/
/* int n_ciclos: Numero de permutaciones a utilizar		*/
/*                                                      */ 
/* Salida:                                              */ 
/* ERR en caso de error y OK en el caso de que las      */ 
/* tablas se ordenen correctamente.                     */ 
/********************************************************/
short genera_tiempos_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador, 
                                int orden, char* fichero, 
                                int num_min, int num_max, 
                                int incr, double fclaves, int n_ciclos)
{
	int i,j;
    PTIEMPO tabla_tiempo=NULL;
    int tamanio_tabla_tiempo=0;
    
    /* Control de errores de los parametros de entrada */ 
    if (metodo == NULL || generador == NULL || 
			((orden != ORDENADO)&&(orden != NO_ORDENADO))|| 
			fichero == NULL || num_max<num_min || 
            num_min <0 || incr<=0 ||fclaves<=0 || n_ciclos <=0)
	return ERR;
    
    /* Se añade 1 puesto que el rango esta incluido en el limite superior */
    tamanio_tabla_tiempo = ((num_max-num_min)/incr)+1;
    
    if((tabla_tiempo=(TIEMPO *)malloc(tamanio_tabla_tiempo*sizeof(TIEMPO)))== NULL)
	    return ERR;
    
    /* Se miden los tiempos de cada tamaño y se rellena la tabla de tiempos */
    /* La variable i itera sobre los tamaños de tabla y la variable j sobre 
	 * el array de elementos de tipo TIEMPO */
    for (i=num_min, j=0; i<=num_max; i+=incr, j++){
	    if (tiempo_medio_busqueda(metodo, generador, orden, i, fclaves,
							n_ciclos, &tabla_tiempo[j]) == ERR){
	        free(tabla_tiempo);
	        return ERR;
	    }
		/* Informacion de las permutaciones finalizadas por salida estandar */
        fprintf(stdout, "\nPermutaciones de tamaño %d finalizadas\n", i);
    }
	
    /* Escritura de la tabla de tiempos en el fichero mediante la funcion guarda_tabla_tiempos */ 
    if (guarda_tabla_tiempos(fichero, tabla_tiempo, tamanio_tabla_tiempo) == ERR){
		free(tabla_tiempo);
		return ERR;
    }
	
    free(tabla_tiempo);
    return OK;
}

/********************************************************/
/* Funcion: tiempo_medio_busqueda Fecha: 22/11/2012		*/ 
/* Autores: Adrián Lorenzo Mateo                        */ 
/*	    Ari Handler Gamboa								*/ 
/*                                                      */ 
/* Funcion que calcula el tiempo medio de busqueda		*/ 
/* en una matriz de permutaciones aplicando el metodo   */ 
/* de busqueda que se pasa como argumento, realizando	*/
/* busquedas de los elementos que devuelve el generador	*/
/* de claves y rellenando una estructura tiempo con		*/
/* datos como tiempo medio de ordenacion, promedio de	*/
/* Obs, tamaño de las permutaciones, etc.				*/ 
/*                                                      */ 
/* Entrada:                                             */ 
/* pfunc_ordena metodo: Metodo de ordenacion que se     */ 
/* que se medirá.                                       */
/* pfunc_generador_claves: Generador de claves a		*/
/* utilizar.											*/
/* int orden: Indica si se utilizara una tabla ordenada.*/
/* int tamanio: Numero de elementos de la permutacion.	*/
/* double fclaves: Factor que indica el numero de claves*/
/* que se buscaran en la iteracion.						*/
/* int n_ciclos: Numero de veces que se repetiran las	*/
/* busquedas de las claves.								*/
/* PTIEMPO ptiempo: Puntero a una estructura de tipo	*/ 
/* TIEMPO que se rellenará una vez finalizada la		*/ 
/* ejecucion de la rutina.								*/ 
/*                                                      */ 
/* Salida:                                              */ 
/* ERR en caso de error y OK en el caso de que las      */ 
/* tablas se ordenen correctamente.                     */ 
/********************************************************/
short tiempo_medio_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador,
                              int orden,
                              int tamanio, 
                              double fclaves,
                              int n_ciclos,
                              PTIEMPO ptiempo)
{
    PDICC diccionario = NULL;
    int * permutacion = NULL;
    int * claves = NULL;
	int pos;
    int tamanio_claves;
    int max_ob, min_ob, actual_ob;
    clock_t t_inicio, t_final;
    double t_medio, medio_ob;
    int i, j;
    
    /* Control de errores de los argumentos de entrada */
    if (metodo == NULL || generador == NULL ||
            ((orden != ORDENADO)&&(orden != NO_ORDENADO)) ||
            fclaves <= 0 || tamanio <= 0 || n_ciclos <= 0 || ptiempo == NULL)
        return ERR;
    
    /* Reserva de memoria del diccionario */
    if ((diccionario = ini_diccionario(tamanio,orden)) == NULL)
        return ERR;
    
    /* Reserva de memoria e insercion de la permutacion en el diccionario */
    if ((permutacion = genera_perm(tamanio)) == NULL){
        libera_diccionario(diccionario);
        return ERR;
    }
    if ((insercion_masiva_diccionario(diccionario, permutacion, tamanio)) == ERR){
        libera_diccionario(diccionario);
		free(permutacion);
        return ERR;
    }
	
	free(permutacion);
    
    /* Reserva de memoria y generacion de las claves a buscar */
    tamanio_claves = tamanio*fclaves;
    if ((claves = (int *)malloc(sizeof(int)*tamanio_claves)) == NULL){
        libera_diccionario(diccionario);
        return ERR;
    }
    
    generador(claves, tamanio_claves, tamanio);
    
    /* Inicializacion de variables */
    medio_ob = max_ob = actual_ob = t_medio = 0;
    min_ob = INT_MAX;
    
    /* Bucle que repite la medicion n_ciclos veces sobre la misma permutacion */
    for(i=0; i<n_ciclos ; i++){
        
		medio_ob = 0;
		
        /* Busqueda de claves y medicion de rendimiento */
        for(j=0; j<tamanio_claves ;j++){
            
            t_inicio = clock();
            
            /* Busqueda sobre la tabla de cada clave 
			 * Como las claves comienzan por 1 en vez de por 0, es necesario
			 * restarle 1 a cada clave para buscar correctamente */
            actual_ob = busca_diccionario(diccionario, claves[j]-1, &pos, metodo);
            
            if(actual_ob == ERR){
                libera_diccionario(diccionario);
				free(claves);
                return ERR;
            }

            t_final = clock();
            
            /* Se evalua la cuenta de OBs actual */
            if (actual_ob < min_ob)
                    min_ob = actual_ob;
            if (actual_ob > max_ob)
                    max_ob = actual_ob;

            /* Se promedian las OB */	
            medio_ob += ((double)actual_ob/tamanio_claves); 

            /* Se promedian los tiempos */
            t_medio += (double) (t_final - t_inicio)/(double) CLOCKS_PER_SEC/n_ciclos;
        }
		
		ptiempo->medio_ob += medio_ob/n_ciclos;
		
    }
    
    /*  Se completa el TAD de tiempo */
    ptiempo->max_ob = max_ob;
    ptiempo->min_ob = min_ob;
    ptiempo->n_ciclos = n_ciclos;
    ptiempo->tamanio = tamanio;
    ptiempo->tiempo = t_medio;
    
    /* Libera el diccionario y las claves */
    libera_diccionario(diccionario);
	free(claves);
    
    return OK;
}

short tiempo_medio_busqueda2(pfunc_busqueda metodo, pfunc_generador_claves generador,
                              int orden,
                              int tamanio, 
                              double fclaves,
                              int n_ciclos,
                              PTIEMPO ptiempo)
{
    PDICC diccionario = NULL;
    int * permutacion = NULL;
    int * claves = NULL;
	int pos;
    int tamanio_claves;
    int max_ob, min_ob, actual_ob;
    clock_t t_inicio, t_final;
    double t_medio, medio_ob;
    int i, j;
    
    /* Control de errores de los argumentos de entrada */
    if (metodo == NULL || generador == NULL ||
            ((orden != ORDENADO)&&(orden != NO_ORDENADO)) ||
            fclaves <= 0 || tamanio <= 0 || n_ciclos <= 0 || ptiempo == NULL)
        return ERR;
    
    /* Reserva de memoria del diccionario */
    if ((diccionario = ini_diccionario(tamanio,orden)) == NULL)
        return ERR;
    
    /* Reserva de memoria e insercion de la permutacion en el diccionario */
    if ((permutacion = genera_perm(tamanio)) == NULL){
        libera_diccionario(diccionario);
        return ERR;
    }
    if ((insercion_masiva_diccionario(diccionario, permutacion, tamanio)) == ERR){
        libera_diccionario(diccionario);
		free(permutacion);
        return ERR;
    }
	
	free(permutacion);
    
    /* Reserva de memoria y generacion de las claves a buscar */
    tamanio_claves = tamanio*fclaves;
    if ((claves = (int *)malloc(sizeof(int)*tamanio_claves)) == NULL){
        libera_diccionario(diccionario);
        return ERR;
    }
    
 
    
    /* Inicializacion de variables */
    medio_ob = max_ob = actual_ob = t_medio = 0;
    min_ob = INT_MAX;
    
    /* Bucle que repite la medicion n_ciclos veces sobre la misma permutacion */
    for(i=0; i<n_ciclos ; i++){
        
		medio_ob = 0;
		generador(claves, tamanio_claves, tamanio);
        /* Busqueda de claves y medicion de rendimiento */
        for(j=0; j<tamanio_claves ;j++){
            
            t_inicio = clock();
            
            /* Busqueda sobre la tabla de cada clave 
			 * Como las claves comienzan por 1 en vez de por 0, es necesario
			 * restarle 1 a cada clave para buscar correctamente */
            actual_ob = busca_diccionario(diccionario, claves[j]-1, &pos, metodo);
            
            if(actual_ob == ERR){
                libera_diccionario(diccionario);
				free(claves);
                return ERR;
            }

            t_final = clock();
            
            /* Se evalua la cuenta de OBs actual */
            if (actual_ob < min_ob)
                    min_ob = actual_ob;
            if (actual_ob > max_ob)
                    max_ob = actual_ob;

            /* Se promedian las OB */	
            medio_ob += ((double)actual_ob/tamanio_claves); 

            /* Se promedian los tiempos */
            t_medio += (double) (t_final - t_inicio)/(double) CLOCKS_PER_SEC/n_ciclos;
        }
		
		ptiempo->medio_ob += medio_ob/n_ciclos;
		
    }
    
    /*  Se completa el TAD de tiempo */
    ptiempo->max_ob = max_ob;
    ptiempo->min_ob = min_ob;
    ptiempo->n_ciclos = n_ciclos;
    ptiempo->tamanio = tamanio;
    ptiempo->tiempo = t_medio;
    
    /* Libera el diccionario y las claves */
    libera_diccionario(diccionario);
	free(claves);
    
    return OK;
}

short genera_tiempos_busqueda2(pfunc_busqueda metodo, pfunc_generador_claves generador, 
                                int orden, char* fichero, 
                                int num_min, int num_max, 
                                int incr, double fclaves, int n_ciclos)
{
	int i,j;
    PTIEMPO tabla_tiempo=NULL;
    int tamanio_tabla_tiempo=0;
    
    /* Control de errores de los parametros de entrada */ 
    if (metodo == NULL || generador == NULL || 
			((orden != ORDENADO)&&(orden != NO_ORDENADO))|| 
			fichero == NULL || num_max<num_min || 
            num_min <0 || incr<=0 ||fclaves<=0 || n_ciclos <=0)
	return ERR;
    
    /* Se añade 1 puesto que el rango esta incluido en el limite superior */
    tamanio_tabla_tiempo = ((num_max-num_min)/incr)+1;
    
    if((tabla_tiempo=(TIEMPO *)malloc(tamanio_tabla_tiempo*sizeof(TIEMPO)))== NULL)
	    return ERR;
    
    /* Se miden los tiempos de cada tamaño y se rellena la tabla de tiempos */
    /* La variable i itera sobre los tamaños de tabla y la variable j sobre 
	 * el array de elementos de tipo TIEMPO */
    for (i=num_min, j=0; i<=num_max; i+=incr, j++){
	    if (tiempo_medio_busqueda2(metodo, generador, orden, i, fclaves,
							n_ciclos, &tabla_tiempo[j]) == ERR){
	        free(tabla_tiempo);
	        return ERR;
	    }
		/* Informacion de las permutaciones finalizadas por salida estandar */
        fprintf(stdout, "\nPermutaciones de tamaño %d finalizadas\n", i);
    }
	
    /* Escritura de la tabla de tiempos en el fichero mediante la funcion guarda_tabla_tiempos */ 
    if (guarda_tabla_tiempos(fichero, tabla_tiempo, tamanio_tabla_tiempo) == ERR){
		free(tabla_tiempo);
		return ERR;
    }
	
    free(tabla_tiempo);
    return OK;
}

short tiempo_medio_busqueda3(pfunc_busqueda metodo, pfunc_generador_claves generador,
                              int orden,
                              int tamanio, 
                              double fclaves,
                              int n_ciclos,
                              PTIEMPO ptiempo)
{
    PDICC diccionario = NULL;
    int * permutacion = NULL;
    int * claves = NULL;
	int pos;
    int tamanio_claves;
    int max_ob, min_ob, actual_ob;
    clock_t t_inicio, t_final;
    double t_medio, medio_ob;
    int i, j;
    
    /* Control de errores de los argumentos de entrada */
    if (metodo == NULL || generador == NULL ||
            ((orden != ORDENADO)&&(orden != NO_ORDENADO)) ||
            fclaves <= 0 || tamanio <= 0 || n_ciclos <= 0 || ptiempo == NULL)
        return ERR;
    

 
    
    /* Inicializacion de variables */
    medio_ob = max_ob = actual_ob = t_medio = 0;
    min_ob = INT_MAX;
    
    /* Bucle que repite la medicion n_ciclos veces sobre la misma permutacion */
    for(i=0; i<n_ciclos ; i++){
        
		medio_ob = 0;
		/* Reserva de memoria del diccionario */
                if ((diccionario = ini_diccionario(tamanio,orden)) == NULL)
                    return ERR;

                /* Reserva de memoria e insercion de la permutacion en el diccionario */
                if ((permutacion = genera_perm(tamanio)) == NULL){
                    libera_diccionario(diccionario);
                    return ERR;
                }
                if ((insercion_masiva_diccionario(diccionario, permutacion, tamanio)) == ERR){
                    libera_diccionario(diccionario);
                            free(permutacion);
                    return ERR;
                }

                    free(permutacion);

                /* Reserva de memoria y generacion de las claves a buscar */
                tamanio_claves = tamanio*fclaves;
                if ((claves = (int *)malloc(sizeof(int)*tamanio_claves)) == NULL){
                    libera_diccionario(diccionario);
                    return ERR;
                }
                generador(claves, tamanio_claves, tamanio);
                
        /* Busqueda de claves y medicion de rendimiento */
        for(j=0; j<tamanio_claves ;j++){
            
            t_inicio = clock();
            
            /* Busqueda sobre la tabla de cada clave 
			 * Como las claves comienzan por 1 en vez de por 0, es necesario
			 * restarle 1 a cada clave para buscar correctamente */
            actual_ob = busca_diccionario(diccionario, claves[j]-1, &pos, metodo);
            
            if(actual_ob == ERR){
                libera_diccionario(diccionario);
				free(claves);
                return ERR;
            }

            t_final = clock();
            
            /* Se evalua la cuenta de OBs actual */
            if (actual_ob < min_ob)
                    min_ob = actual_ob;
            if (actual_ob > max_ob)
                    max_ob = actual_ob;

            /* Se promedian las OB */	
            medio_ob += ((double)actual_ob/tamanio_claves); 

            /* Se promedian los tiempos */
            t_medio += (double) (t_final - t_inicio)/(double) CLOCKS_PER_SEC/n_ciclos;
        }
		
		ptiempo->medio_ob += medio_ob/n_ciclos;
		
    }
    
    /*  Se completa el TAD de tiempo */
    ptiempo->max_ob = max_ob;
    ptiempo->min_ob = min_ob;
    ptiempo->n_ciclos = n_ciclos;
    ptiempo->tamanio = tamanio;
    ptiempo->tiempo = t_medio;
    
    /* Libera el diccionario y las claves */
    libera_diccionario(diccionario);
	free(claves);
    
    return OK;
}

short genera_tiempos_busqueda3(pfunc_busqueda metodo, pfunc_generador_claves generador, 
                                int orden, char* fichero, 
                                int num_min, int num_max, 
                                int incr, double fclaves, int n_ciclos)
{
	int i,j;
    PTIEMPO tabla_tiempo=NULL;
    int tamanio_tabla_tiempo=0;
    
    /* Control de errores de los parametros de entrada */ 
    if (metodo == NULL || generador == NULL || 
			((orden != ORDENADO)&&(orden != NO_ORDENADO))|| 
			fichero == NULL || num_max<num_min || 
            num_min <0 || incr<=0 ||fclaves<=0 || n_ciclos <=0)
	return ERR;
    
    /* Se añade 1 puesto que el rango esta incluido en el limite superior */
    tamanio_tabla_tiempo = ((num_max-num_min)/incr)+1;
    
    if((tabla_tiempo=(TIEMPO *)malloc(tamanio_tabla_tiempo*sizeof(TIEMPO)))== NULL)
	    return ERR;
    
    /* Se miden los tiempos de cada tamaño y se rellena la tabla de tiempos */
    /* La variable i itera sobre los tamaños de tabla y la variable j sobre 
	 * el array de elementos de tipo TIEMPO */
    for (i=num_min, j=0; i<=num_max; i+=incr, j++){
	    if (tiempo_medio_busqueda3(metodo, generador, orden, i, fclaves,
							n_ciclos, &tabla_tiempo[j]) == ERR){
	        free(tabla_tiempo);
	        return ERR;
	    }
		/* Informacion de las permutaciones finalizadas por salida estandar */
        fprintf(stdout, "\nPermutaciones de tamaño %d finalizadas\n", i);
    }
	
    /* Escritura de la tabla de tiempos en el fichero mediante la funcion guarda_tabla_tiempos */ 
    if (guarda_tabla_tiempos(fichero, tabla_tiempo, tamanio_tabla_tiempo) == ERR){
		free(tabla_tiempo);
		return ERR;
    }
	
    free(tabla_tiempo);
    return OK;
}