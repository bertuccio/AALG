/**
 *
 * Descripcion: Funciones de cabecera para medicion de tiempos 
 *
 * Fichero: tiempos.h
 * Autor: 
 * Version: 1.0
 * Fecha: 11-11-2011
 *
 */

#ifndef TIEMPOS_H
#define TIEMPOS_H

#include "ordenar.h"
#include "busqueda.h"

/* constantes */

#define ERR -1
#define OK (!(ERR))

/* definiciones de tipos */

typedef struct tiempo {
  int n_ciclos;    /* numero de veces que se repita la medici\'on de tiempos */
  int tamanio;     /* tamanio */
  double tiempo;   /* tiempo promedio */
  double medio_ob; /* numero premedio de veces que se ejecuta la OB */
  int min_ob;      /* minimo de ejecuciones de la OB */
  int max_ob;      /* maximo de ejecuciones de la OB */
} TIEMPO, *PTIEMPO;



short genera_tiempos_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador, 
                                int orden, char* fichero, 
                                int num_min, int num_max, 
                                int incr, double fclaves, int n_ciclos);

short tiempo_medio_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador,
                              int orden,
                              int tamanio, 
                              double fclaves,
                              int n_ciclos,
                              PTIEMPO ptiempo);

short tiempo_medio_busqueda2(pfunc_busqueda metodo, pfunc_generador_claves generador,
                              int orden,
                              int tamanio, 
                              double fclaves,
                              int n_ciclos,
                              PTIEMPO ptiempo);

short genera_tiempos_busqueda2(pfunc_busqueda metodo, pfunc_generador_claves generador, 
                                int orden, char* fichero, 
                                int num_min, int num_max, 
                                int incr, double fclaves, int n_ciclos);

short tiempo_medio_busqueda3(pfunc_busqueda metodo, pfunc_generador_claves generador,
                              int orden,
                              int tamanio, 
                              double fclaves,
                              int n_ciclos,
                              PTIEMPO ptiempo);

short genera_tiempos_busqueda3(pfunc_busqueda metodo, pfunc_generador_claves generador, 
                                int orden, char* fichero, 
                                int num_min, int num_max, 
                                int incr, double fclaves, int n_ciclos);
#endif

