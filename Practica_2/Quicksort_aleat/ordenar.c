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
int SelectSort(int* tabla, int ip, int iu)
{ 
	int i, j, ob_count, min;
    
	/* Control de errores de los parametros de entrada */
	if((tabla==NULL)||(ip<0)||(iu<ip)) 
        return ERR;

    ob_count=0; 
    /* Bucle que recorre la tabla desde ip hasta iu */
    for(i=ip; i<iu; i++){ 
        min=i; 
        /* Una vez seleccionado el elemento con indice ip 
		 * itera entre los elementos restantes hasta iu */
        for(j=i+1;j<=iu;j++){ 
            ob_count++;
            if(tabla[j]<tabla[min]) /* Operacion Basica */
                min=j;
        }
        swap(i,min,tabla);
    }
     
	return ob_count;
}

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
short tiempo_medio_ordenacion(pfunc_ordena metodo, 
                              int n_perms,
                              int tamanio, 
                              PTIEMPO ptiempo,
                              int n_veces)
{
	int max_ob, min_ob, actual_ob;
	clock_t t_inicio, t_final;
	double t_medio, medio_ob;
	int ** matriz_perm;
	int i, j;
	int * perm_aux=NULL;
	
	/* Comprobacion de los parametros de entrada */
	if (metodo == NULL || n_perms <= 0 || tamanio <= 0 || ptiempo == NULL || n_veces < 0)
		return ERR;

	/* Reserva y comprobacion de memoria de la matriz de permutaciones */
	if ((matriz_perm = genera_permutaciones(n_perms, tamanio)) == NULL)
		return ERR;
		
	/* Inicializacion de variables */
	medio_ob = max_ob = actual_ob = t_medio = 0;
	min_ob = INT_MAX;
	
	/* Reserva de memoria de la permutacion auxiliar que servira para
	 * crear el retardo necesario reordenandola n_veces */
	if ((perm_aux = (int *)malloc(tamanio*sizeof(int))) == NULL){
			/* Se libera la matriz de permutaciones */
			for (i=0; i< n_perms ;i++){
				free(matriz_perm[i]);
			}
			free(matriz_perm);
			return ERR;
    	}
	
	/* Iteracion de cada una de las permutaciones de la matriz */
	for (i=0; i<n_perms ;i++){

                /* Se copia la permutacion original */
                memcpy(perm_aux, matriz_perm[i], (tamanio+1)*sizeof(int));

		t_inicio = clock();
		
		/* Se ordena la permutación original n_veces veces 
                   Si el retardo es 0*/
		for (j=0; j<(n_veces==0 ? 1 : n_veces); j++){
		    if((actual_ob = metodo(matriz_perm[i], 0, tamanio-1)) == ERR){
		    	/* Se liberan la matriz de permutaciones */
				for (i=0; i< n_perms ;i++){
					free(matriz_perm[i]);
				}
				free(matriz_perm);
		    	return ERR;
		    }
		    /* La permutacion es restaurada */
		    memcpy(matriz_perm[i], perm_aux, (tamanio+1)*sizeof(int));
		} 
		
		t_final = clock();
		
		/* Se evalua la cuenta de OBs actual */
		if (actual_ob < min_ob)
			min_ob = actual_ob;
		if (actual_ob > max_ob)
			max_ob = actual_ob;
                
		/* Se promedian las OB */	
		medio_ob += (double)actual_ob/n_perms; 
		
		/* Se promedian los tiempos */
		t_medio += (double) (t_final - t_inicio)/(double) CLOCKS_PER_SEC/n_perms;
	}
	
	/* Se completa la estructura tiempo */
	ptiempo->n_perms = n_perms;
	ptiempo->tamanio = tamanio;
	ptiempo->medio_ob = medio_ob; 
	ptiempo->min_ob = min_ob;
	ptiempo->max_ob = max_ob;
	ptiempo->tiempo = t_medio;
	
	/* Se liberan la matriz de permutaciones y la permutacion auxiliar*/
	for (i=0; i< n_perms ;i++){
		free(matriz_perm[i]);
	}
	free(matriz_perm);
	free(perm_aux);
	
	return OK;
}

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
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero, 
                                int num_min, int num_max, 
                                int incr, int n_perms, int n_veces)
{
    int i,j;
    PTIEMPO tabla_tiempo=NULL;
    int tamanio_tabla_tiempo;
    
    /* Control de errores de los parametros de entrada */ 
    if (metodo == NULL || fichero == NULL || num_max<num_min || 
            num_min <0 || incr<=0 || n_perms <=0)
	return ERR;
    
    /* Se añade 1 puesto que el rango esta incluido en el limite superior */
    tamanio_tabla_tiempo = ((num_max-num_min)/incr)+1;
    
    if( (tabla_tiempo=(TIEMPO *)malloc(tamanio_tabla_tiempo*sizeof(TIEMPO)))== NULL)
	    return ERR;
    
    /* Se miden los tiempos de cada tamaño y se rellena la tabla de tiempos */
    /*la variable i itera sobre los tamaños de tabla, incrementandose incr*/
    /*la variable j itera sobre el array de elementos TIEMPO*/
    for (i=num_min, j=0; i<=num_max; i+=incr, j++){
	    if (tiempo_medio_ordenacion(metodo, n_perms, i, &tabla_tiempo[j], n_veces) == ERR){
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

/****************************************************/
/* Funcion: MergeSort    Fecha: 17/10/2012         */
/* Autores: Adrián Lorenzo Mateo                    */
/*	    Ari Handler Gamboa                      */
/*                                                  */
/* Funcion que ordena un array de enteros haciendo  */
/* uso del método Mergesort, devolviendo el número */
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
int mergesort(int* tabla, int ip, int iu)
{
        int ob_count, imedio, ret;
    
        /* Control de errores de los parametros de entrada */
        if((tabla==NULL)||(ip<0)||(iu<ip)) 
                return ERR;
        
        ob_count=0;   
        
	/* Condicion de parada de la recursion */
        if (ip == iu)
            return ob_count;
        
    
	/* Funcion "sencilla" de partir */
        imedio = (iu+ip)/2;
	/* Llamada recursiva del algoritmo para la sub-tabla izquierda */
        if ((ret = mergesort(tabla, ip, imedio)) == ERR) 
            return ERR;
        ob_count += ret;
	/* Llamada recursiva del algoritmo para la sub-tabla derecha */
        if ((ret = mergesort(tabla, imedio+1, iu)) == ERR) 
            return ERR;
        ob_count += ret;
        
        /* Combinacion de ambas tablas ordenadas */
        if ((ret = merge(tabla, ip, iu, imedio)) == ERR) 
            return ERR;
        return (ob_count + ret);
}

/********************************************************/
/* Funcion: Merge    Fecha: 17/10/2012                  */
/* Autores: Adrián Lorenzo Mateo                        */
/*	    Ari Handler Gamboa                          */
/*                                                      */
/* Funcion que combina de forma ordenada las subtablas	*/
/* definidas por los indices pasados como argumentos	*/
/*                                                      */
/* Entrada:                                             */
/* int tabla: Tabla a ordenar                           */
/* int ip: Primer elemento de la tabla                  */
/* int iu: Ultimo elemento de la tabla                  */
/* int imedio: Indice que marca la mitad de la tabla    */
/* Salida:                                              */
/* int: Número de OBs ejecutadas o                      */
/* ERR en caso de error                                 */
/********************************************************/
int merge(int* tabla, int ip, int iu, int imedio)
{
    int * tabla_aux = NULL;
    int i, j, k, ob_count;
    
	/* Control de errores de los parametros de entrada */
    if ((tabla == NULL) || (ip<0) || (ip>iu) || (imedio<ip) || (imedio>iu))
        return ERR;
    
	/* Reserva de memoria de la tabla auxiliar */
    if ((tabla_aux = (int *)malloc((iu-ip+1)*sizeof(int))) == NULL)
        return ERR;
    
	/* Se copia la tabla original y se inicializan las variables de los bucles */
    memcpy(tabla_aux, tabla, (iu-ip+1)*sizeof(int));
    k  = 0;
    i  = ip;
    j = imedio+1;
    ob_count = 0;
    
	/* Bucle que recorre la tabla de izquierda a derecha ambas sub-tablas */
    while((i<=imedio) && (j<=iu)){
        ob_count++;
		/* Determinacion del elemento menor de ambas subtablas e insercion
		   del mismo en la tabla resultante */
        if (tabla[i] < tabla[j]){ /* Operacion Basica */
            tabla_aux[k] = tabla[i];
            i++;
        }
        else{
            tabla_aux[k] = tabla[j];
            j++;
        }
		/* Aumento del indice que recorre la tabla resultante */
        k++;
    }
	/* Se determina cual de las subtablas tiene un exceso de elementos no
	   insertados en la tabla resultante y se añaden al final de esta */
    if (i>imedio){
        for(;j<=iu;j++,k++)
            tabla_aux[k] = tabla[j];
    }
    else if (j>iu){
        for(;i<=imedio;i++,k++)
            tabla_aux[k] = tabla[i];
    }
	
	/* Se copia la tabla auxiliar resultante en la pasada por argumento 
	   y se libera la memoria de la auxiliar */
    memcpy(&(tabla[ip]), tabla_aux, (iu-ip+1)*sizeof(int));
    free(tabla_aux);
    
    return ob_count;
}

/****************************************************/
/* Funcion: Medio    Fecha: 24/10/2012              */
/* Autores: Adrián Lorenzo Mateo                    */
/*	    Ari Handler Gamboa                      */
/*                                                  */
/* Funcion pivote que devuelve el menor de los      */
/* indices pasados por argumentos.                  */
/*                                                  */
/* Entrada:                                         */
/* int ip: Primer indice                            */
/* int iu: Ultimo indice                            */
/* Salida:                                          */
/* int: Menor de los indices                        */
/****************************************************/
int medio(int ip, int iu){
    
    if(ip<iu)
        return ip;

    return iu;
}


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
int partir(int* tabla, int ip, int iu, pfunc_pivote pivote){
    
    int m;/*indice pivote*/
    int k;/*elemento pivote*/
    int i;
    
    
    m=pivote(ip,iu);
    k=tabla[m];
    
    
    /*Intercambia el pivote con 
     * el primer elemento de la tabla*/
    if(swap(ip,m,tabla)==ERR)
        return ERR;
    
    
    /*se asigna al indice pivote el primer indice*/
    m=ip;
    
    /*Itera sobre la tabla a partir del segundo elemento hasta el ultimo*/
    for(i=ip+1;i<=iu;i++){

        
        /*si el elemento iterado es menor que el elemento pivote*/
        if(tabla[i]<k){
            /*incrementa el indice pivote e intercambia*/
            m++;
            if(swap(i,m,tabla)==ERR)
                return ERR;

        }
    }
    /*Retorna el pivote a la posicion ordenada*/
    if(swap(m,ip,tabla)==ERR)
        return ERR;
    
    return m; 

}



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
int quicksort(int* tabla, int ip, int iu, pfunc_pivote pivote){
	int M, menoresQuePivote, mayoresQuePivote;
	int cuentaOB=0, cuentaAux=0;
	
	/* CdE */
	if(tabla==NULL || ip<0 || ip>iu || pivote==NULL)
		return ERR;
		
	/* Si es de 1 elemento, ya esta ordenada */
	if(ip==iu){
		cuentaOB = 0;
		return cuentaOB;
	}
	
	/* Siempre se realizan iu-ip comparaciones de clave (que es la operacion basica) */
	cuentaOB = iu-ip;
	
	/* M sera ip+num_elements_menores_que_pivote*/
	M = partir(tabla, ip, iu, pivote);
	if(M==ERR) /* Si devolvio ERR terminamos con error. */
		return ERR;
	
	menoresQuePivote = M-ip;
	mayoresQuePivote = (iu-ip)-menoresQuePivote;

	/* Si el num elementos menores que pivote es de 0 o de 1
	 * ya esta ordenado el lado izquierdo.
	 * Sino, hay al menos 2 elementos en la izq para ordenar. */		
	if(menoresQuePivote>=2){
		cuentaAux = quicksort(tabla, ip, M-1, pivote);
		
		if(cuentaAux==ERR)
			return ERR;
		else
			cuentaOB+=cuentaAux;
	}
	
	/* Hacemos lo mismo con el lado derecho (mayores que pivote). */
	if(mayoresQuePivote>=2){
		cuentaAux=quicksort(tabla, M+1, iu, pivote);
		
		if(cuentaAux==ERR)
			return ERR;
		else
			cuentaOB+=cuentaAux;
	}
		
	return cuentaOB;
}

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
int quicksort1(int* tabla, int ip, int iu){
    return quicksort(tabla,ip,iu,medio);
}

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
int quicksort2(int* tabla, int ip, int iu){
    return quicksort(tabla,ip,iu,aleat_num);
}