/**
 *
 * Descripcion: Funciones de cabecera para busqueda 
 *
 * Fichero: busqueda.h
 * Autor: 
 * Version: 1.0
 * Fecha: 22-09-2011
 *
 */

#ifndef BUSQUEDA_H_
#define BUSQUEDA_H_

/* constantes */

#define NO_ENCONTRADO -2

#define ORDENADO 1
#define NO_ORDENADO 0

#define ERR -1

/* definiciones de tipos */
typedef struct diccionario {
  int tamanio; /* tamano de la tabla */
  int n_datos; /* numero de datos en la tabla */
  char orden;  /* tabla ordenada o desordenada */
  int *tabla;  /* tabla de datos */
} DICC, *PDICC;

typedef int (* pfunc_busqueda)(int*, int, int, int, int*);
typedef void (* pfunc_generador_claves)(int*, int, int);

/* TAD Diccionario */
/********************************************************/
/* Funcion: ini_diccionario    Fecha: 15/10/2012        */
/* Autores: Adrián Lorenzo Mateo                        */
/*      Ari Handler Gamboa                              */
/*                                                      */
/* Funcion que reserva memoria tanto para el TAD        */
/* diccionario como para la el campo que guarda la tabla*/
/* asociada                                             */
/*                                                      */
/* Entrada:                                             */
/* int tamanio: tamaño de la tabla asociada.            */
/* char ordena: Constante que define si la tabla estara */
/* ordenada o no.                                       */
/* Salida:                                              */
/* El diccionario inicializado en caso de que todo vaya */
/* bien, NULL en caso de algun error.                   */
/********************************************************/
PDICC ini_diccionario (int tamanio, char orden);

/********************************************************/
/* Funcion: libera_diccionario    Fecha: 15/10/2012     */
/* Autores: Adrián Lorenzo Mateo                        */
/*      Ari Handler Gamboa                              */
/*                                                      */
/* Funcion que libera toda la memoria reservada para    */
/* el diccionario pasado como argumento.                */
/*                                                      */
/* Entrada:                                             */
/* PDICC pdicc: Puntero al diccionario a liberar.       */
/* Salida:                                              */
/* Esta funcion no retorna ningun valor.                */
/********************************************************/
void libera_diccionario(PDICC pdicc);

/********************************************************/
/* Funcion: inserta_diccionario    Fecha: 15/10/2012    */
/* Autores: Adrián Lorenzo Mateo                        */
/*      Ari Handler Gamboa                              */
/*                                                      */
/* Funcion que inserta un elemento en la tabla asociada */
/* al diccionario mediante el algoritmo InsertSort si   */
/* dicha tabla esta ordenada o al final si no es asi.   */
/*                                                      */
/* Entrada:                                             */
/* PDICC pdicc: Puntero al diccionario donde insertar   */
/* la clave.                                            */
/* Salida:                                              */
/* Numero de OBs ejecutadas si todo va bien, ERR en caso*/
/* contrario.                                           */
/********************************************************/
int inserta_diccionario(PDICC pdicc, int clave);

/****************************************************************/
/* Funcion: insercion_masiva_diccionario    Fecha: 15/10/2012   */
/* Autores: Adrián Lorenzo Mateo                                */
/*      Ari Handler Gamboa                                      */
/*                                                              */
/* Funcion que inserta en el diccionario pasado como argumento  */
/* todas las claves del array claves.                           */
/*                                                              */
/* Entrada:                                                     */
/* PDICC pdicc: Puntero al diccionario donde insertar las claves*/
/* int *claves: Array de claves a insertar.                     */
/* int n_claves: Tamaño del array de claves a insertar.         */
/* Salida:                                                      */
/* Numero de OBs ejecutadas si todo va bien, ERR en caso        */
/* contrario.                                                   */
/****************************************************************/
int insercion_masiva_diccionario (PDICC pdicc,int *claves, int n_claves);

/********************************************************/
/* Funcion: busca_diccionario    Fecha: 15/10/2012      */
/* Autores: Adrián Lorenzo Mateo                        */
/*      Ari Handler Gamboa                              */
/*                                                      */
/* Funcion que busca una clave en el diccionario        */
/* mediante un determinado metodo, devolviendo por      */
/* referencia la posicion de dicha clave en la tabla.   */
/*                                                      */
/* Entrada:                                             */
/* PDICC pdicc: Puntero al diccionario donde buscar.    */
/* int clave: Clave a buscar en el diccionario.         */
/* int *ppos: Puntero a la posicion donde se encuentre  */
/* la clave buscada.                                    */
/* pfunc_busqueda metodo: Metodo de busqueda a utilizar */
/* Salida:                                              */
/* Numero de OBs ejecutadas si todo va bien, ERR en caso*/
/* contrario.                                           */
/********************************************************/
int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo);

/********************************************************/
/* Funcion: imprime_diccionario    Fecha: 15/10/2012    */
/* Autores: Adrián Lorenzo Mateo                        */
/*      Ari Handler Gamboa                              */
/*                                                      */
/* Funcion que realiza una impresion por pantalla de    */
/* toda la informacion del diccionario en cuestion.     */
/*                                                      */
/* Entrada:                                             */
/* PDICC pdicc: Puntero al diccionario a imprimir.      */
/* Salida:                                              */
/* No se genera ninguna salida.                         */
/********************************************************/
void imprime_diccionario(PDICC pdicc);

/* Funciones de busqueda del TAD Diccionario */
/********************************************************/
/* Funcion: bbin    Fecha: 15/10/2012                   */
/* Autores: Adrián Lorenzo Mateo                        */
/*      Ari Handler Gamboa                              */
/*                                                      */
/* Funcion implementa la busqueda binaria de una clave, */
/* devolviendo por referencia la posicion de dicha clave*/
/*                                                      */
/* Entrada:                                             */
/* int *tabla: Tabla donde realizar la busqueda.        */
/*              DEBE ESTAR ORDENADA.                    */
/* int P: Primer elemento de la tabla.                  */
/* int U: Ultimo elemento de la tabla.                  */
/* int clave: Clave a buscar.                           */
/* int *ppos: Puntero a la posicion de la clave.        */
/* Salida:                                              */
/* Numero de OBs ejecutadas si todo va bien, ERR en caso*/
/* contrario. Adicionalmente, la posicion de la clave   */
/* encontrada si fuera el caso en ppos.                 */
/********************************************************/
int bbin(int *tabla,int P,int U,int clave,int *ppos);

/********************************************************/
/* Funcion: blin    Fecha: 15/10/2012                   */
/* Autores: Adrián Lorenzo Mateo                        */
/*      Ari Handler Gamboa                              */
/*                                                      */
/* Funcion implementa la busqueda lineal de una clave,  */
/* devolviendo por referencia la posicion de dicha clave*/
/*                                                      */
/* Entrada:                                             */
/* int *tabla: Tabla donde realizar la busqueda.        */
/* int P: Primer elemento de la tabla.                  */
/* int U: Ultimo elemento de la tabla.                  */
/* int clave: Clave a buscar.                           */
/* int *ppos: Puntero a la posicion de la clave.        */
/* Salida:                                              */
/* Numero de OBs ejecutadas si todo va bien, ERR en caso*/
/* contrario. Adicionalmente, la posicion de la clave   */
/* encontrada si fuera el caso en ppos.                 */
/********************************************************/
int blin(int *tabla,int P,int U,int clave,int *ppos);

/********************************************************/
/* Funcion: blin_auto    Fecha: 15/10/2012              */
/* Autores: Adrián Lorenzo Mateo                        */
/*      Ari Handler Gamboa                              */
/*                                                      */
/* Funcion que implementa la busqueda lineal en su      */
/* version auto-organizadora de una clave, devolviendo  */
/* por referencia la posicion de dicha clave            */
/*                                                      */
/* Entrada:                                             */
/* int *tabla: Tabla donde realizar la busqueda.        */
/* int P: Primer elemento de la tabla.                  */
/* int U: Ultimo elemento de la tabla.                  */
/* int clave: Clave a buscar.                           */
/* int *ppos: Puntero a la posicion de la clave.        */
/* Salida:                                              */
/* Numero de OBs ejecutadas si todo va bien, ERR en caso*/
/* contrario. Adicionalmente, la posicion de la clave   */
/* encontrada si fuera el caso en ppos.                 */
/********************************************************/
int blin_auto(int *tabla,int P,int U,int clave,int *ppos);

/**
 *  Funciones de geracion de claves
 *
 *  Descripcion: Reciben el numero de claves que hay que generar
 *               en el parametro n_claves. Las claves generadas
 *               van de 1 a max. Las claves se devuelven en 
 *               el parametro claves que se debe reservar externamente
 *               a la funcion.
 *
 */
void generador_claves_uniforme(int *claves, int n_claves, int max);
void generador_claves_potencial(int *claves, int n_claves, int max);


#endif

