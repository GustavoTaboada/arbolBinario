#ifndef ARBOLSIMPLE_H_INCLUDED
#define ARBOLSIMPLE_H_INCLUDED
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define CLA_DUP -1
#define SIN_MEM 0
#define TODO_BIEN 1
#define true 1
#define false 0

typedef struct sNodo
{
  void* info;
  unsigned tamInfo;
  struct sNodo* izq;
  struct sNodo* der;
}tNodo;

typedef tNodo* tArbol;


/// CREAR  ///  /// Iteradores internos //
void crearArbol(tArbol* pA);

tNodo* crearNodo(void* d, unsigned cantBytes);

/// ELIMINACION //
int vaciarArbol(tArbol* pA);
int liberarNodo(tArbol* pA);

/// poner elementos ///
int ponerEnArbol(tArbol* pA, void* d, unsigned cantBytes
                 ,int (*comparar)(void*,void*));

/// Borrar ///

int borraraNodoArbol(tArbol* pA, void* d
                ,int (*comparar)(void*,void*));

int borrarRaizArbol(tArbol* pA, void* d
                     ,int (*comparar)(void*,void*));


/// BUSCAR ///

int estaEnArbol(tArbol* pA, void* d
                ,int (*comparar)(void*,void*));

int esABB(tArbol* pA,int (*comparar)(void*,void*));

tNodo** buscarNodoAeliminar(tArbol* pA, void* d
                ,int (*comparar)(void*,void*));

tNodo** buscarPadreNodoAeliminar(tArbol* pA, void* d
                ,int (*comparar)(void*,void*)
                ,tArbol* encontrado);

tNodo** buscarNodoMayor(tArbol* pA);

tNodo** buscarNodoMenor(tArbol* pA);

tNodo** buscarNodoMayorDesordenado(tArbol* p, int (*comparar)(void*,void*));
tNodo** buscarNodoMenorDesordenado(tArbol* p, int (*comparar)(void*,void*));



int alturaArbol(tArbol *pA);

//int alturaArbol(tArbol* pA);
/// Iteradores internos //

typedef int(*functionAccion)(void*,void*);

int iterarEnOrden(tArbol *p, functionAccion f ,void* extra);
int iterarPosOrden(tArbol *p, functionAccion f ,void* extra);
int iterarPreOrden(tArbol *p, functionAccion f ,void* extra);
int iterarEnOrdenInverso(tArbol *p, functionAccion f ,void* extra);


typedef void (*mostrar)(void* data, FILE* salida);
int mostarArbol(tArbol* pA
                ,void (*mostrar)(void* data, FILE* salida)
                ,FILE* sal);



/// catedra
tNodo ** mayorNodoArbolBinBusq(const tArbol * p);
tNodo ** menorNodoArbolBinBusq(const tArbol * p);
int eliminarRaizArbolBinBusq(tArbol * p);
///


/// choreadas
void imprimirConForma(void * info, unsigned tam, unsigned n, void * params);

void imprimir(void * info, unsigned tam, unsigned n, void * params);

unsigned leerDesdeVectorEnteros(void ** d, void * vec, unsigned pos, void * params);

int cmp_ent( void *v1,  void *v2);
void printBonito( tArbol *p, unsigned nivel);
#endif // ARBOLSIMPLE_H_INCLUDED
