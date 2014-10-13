/**
 *
 * Descripcion: Implementacion funciones para busqueda 
 *
 * Fichero: busqueda.c
 * Autor: 
 * Version: 1.0
 * Fecha: 11-11-2011
 *
 */

#include "busqueda.h"
#include "ordenar.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
PDICC ini_diccionario (int tamanio, char orden)
{
    PDICC nuevoDiccionario;
    
    /* Control de errores de los argumentos de entrada */
    if (tamanio <= 0 || ((orden != ORDENADO)&&(orden != NO_ORDENADO)))
        return NULL;
    
    /* Creacion del TAD Diccionario */
    if ((nuevoDiccionario = (PDICC)malloc(sizeof(DICC))) == NULL)
        return NULL;
    
    /* Reserva de memoria para la tabla de enteros del diccionario */
    if ((nuevoDiccionario->tabla = (int *)calloc(tamanio,sizeof(int))) == NULL){
        free(nuevoDiccionario);
        return NULL;   
    }
    
    /* Completado del resto de campos del diccionario */
    nuevoDiccionario->tamanio = tamanio;
    nuevoDiccionario->n_datos = 0;
    nuevoDiccionario->orden = orden;
    
    return nuevoDiccionario;
}

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
void libera_diccionario(PDICC pdicc)
{
    free(pdicc->tabla);
    free(pdicc);
}

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
int inserta_diccionario(PDICC pdicc, int clave)
{
    int i;
    int  cuenta_obs=0;
    
    /* Control de errores de los argumentos de entrada */
    if (pdicc == NULL)
        return ERR;
    
    /* Comprobacion de sobrepaso del tamano de tabla */
    if (pdicc->n_datos == pdicc->tamanio)
        return ERR;
    
    /* Si la tabla esta ordenada, se utiliza InserSort para insertar el elemento */
    if (pdicc->orden == ORDENADO){
        
    /* Para ordenar, inserto al final y comparo con las anteriores */
    pdicc->tabla[pdicc->n_datos] = clave;
    i = pdicc->n_datos;
    /* Se realizan swaps sucesivos hasta dejar el elemento en su posicion ordenada */
    while ((i>0) && (pdicc->tabla[i] < pdicc->tabla[i-1])){
        cuenta_obs++;
        swap(i, i-1, pdicc->tabla);
        i--;
     }

    }
    /* Si no esta ordenada, se inserta al final */
    if (pdicc->orden == NO_ORDENADO){
        
        pdicc->tabla[pdicc->n_datos] = clave;
        cuenta_obs = 1;
    }
    /* El numero de datos ahora es 1 mas grande */
    pdicc->n_datos++;
    
    return cuenta_obs;
}

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
int insercion_masiva_diccionario (PDICC pdicc,int *claves, int n_claves)
{
    int i;
    int cuenta_obs = 0;
    int ret;
    
    /* Control de errores de los argumentos de entrada */
    if (pdicc == NULL || claves == NULL || n_claves < 0)
        return ERR;
    
    /* Comprobacion de sobrepaso del tamano de tabla */
    if (pdicc->tamanio < (pdicc->n_datos + n_claves))
        return ERR;
    
    /* Bucle que llama a la insercion de un unico elemento por cada clave
     * en el array de claves */
    for(i=0; i<n_claves ;i++){
        if ((ret = inserta_diccionario(pdicc, claves[i])) == ERR)
            return ERR;
        cuenta_obs += ret;
    }
    
    return cuenta_obs;
}

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
/* contrario. Adicionalmente, la posicion de la clave   */
/* encontrada si fuera el caso en ppos.                 */
/********************************************************/
int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo)
{
    int cuenta_obs=0;
    
    /* Control de errores de los argumentos de entrada */
    if (pdicc == NULL || metodo == NULL)
        return ERR;
    
    /* Se llama al metodo de busqueda. La salida de dicho metodo se devuelve
     * directamente puesto que el CDE correspondiente se hara en un nivel
     * superior. */
    cuenta_obs = metodo(pdicc->tabla, 0, pdicc->n_datos-1, clave, ppos);
    
    return cuenta_obs;
}

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
void imprime_diccionario(PDICC pdicc)
{
    int i;
    
    if (pdicc == NULL)
        return;
    
    printf("\nTamanio del diccionario = %d\n", pdicc->tamanio);
    printf("# de elementos del diccionario = %d\n", pdicc->n_datos);
    printf("Ordenado = %s\n", pdicc->orden == ORDENADO ? "Si" : "No");
    printf("Tabla = ");
    for(i=0; i<pdicc->n_datos ;i++){
        printf("%d\t", pdicc->tabla[i]);
        if((i%10) == 9)
            printf("\n");
    }
    
    printf("\n");
    
    return;
}

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
int bbin(int *tabla,int P,int U,int clave,int *ppos)
{
    int M; /*indice medio de la tabla*/
    int ob_count = 0; /*contador de operaciones basicas*/
    
    /* Control de argumentos de entrada */
    if (tabla == NULL || P<0 || U<P)
        return ERR;
    
    /* Algoritmo de busqueda binaria */
    while (P <= U){
        M = (P + U)/2;
        ob_count++; /* CDC */
        if (tabla[M] == clave){ 
            *ppos = M;
            return ob_count;
        }
        if (clave < tabla[M])
            U = M - 1;
        else
            P = M + 1;
    }
    
    return NO_ENCONTRADO;
}

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
int blin(int *tabla,int P,int U,int clave,int *ppos)
{
    int i;
    int cuenta_obs = 0;
    
    /* Control de argumentos de entrada */
    if (tabla == NULL || P>U)
        return ERR;
    
    /* Algoritmo de la busqueda lineal */
    for(i=0; i<=U ;i++){
        cuenta_obs++; /* CDC */
        if (tabla[i] == clave){
            *ppos = i;
            return cuenta_obs;
        }
    }
    
    return NO_ENCONTRADO;
}

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
int blin_auto(int *tabla,int P,int U,int clave,int *ppos)
{
    int i;
    int cuenta_obs = 0;
    
    /* Control de argumentos de entrada */
    if (tabla == NULL || P>U)
        return ERR;
    
    /* Algoritmo de busqueda lineal auto-organizada */
    for(i=0; i<=U ;i++){
        cuenta_obs++; /* CDC */
        /* Si no es el primer elemento realiza un swap */
        if ((tabla[i] == clave)&&(i!=0)){
            swap(i, i-1, tabla);
            *ppos = i;
            return cuenta_obs;
        }
        /*si es el primer elemento no intercambia*/
        else if((tabla[i] == clave)&&(i==0))
            return cuenta_obs;
    }
    
    return NO_ENCONTRADO;
}

/**
 *  Funciones de geracion de claves
 *
 *  Descripcion: Recibe el numero de claves que hay que generar
 *               en el parametro n_claves. Las claves generadas
 *               iran de 1 a max. Las claves se devuelven en 
 *               el parametro claves que se debe reservar externamente
 *               a la funcion.
 */
  
/**
 *  Funcion: generador_claves_uniforme
 *               Esta fucnion genera todas las claves de 1 a max de forma 
 *               secuencial. Si n_claves==max entonces se generan cada clave
 *               una unica vez.
 */
void generador_claves_uniforme(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) claves[i] = 1 + (i % max);

  return;
}

/**
 *  Funcion: generador_claves_potencial
 *               Esta funcion genera siguiendo una distribucion aproximadamente
 *               potencial. Siendo los valores mas pequenos mucho mas probables
 *               que los mas grandes. El valor 1 tiene una probabilidad del 50%,
 *               el dos del 17%, el tres el 9%, etc.
 */
void generador_claves_potencial(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) {
    claves[i] = (1+max) / (1 + max*((double)rand()/RAND_MAX));
  }

  return;
}



