#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include "testLibrary.h"
#include "arbolSimple.h"

#include <assert.h>

int test_crearArbol();
int test_crearNodo();
int test_vaciarArbol();

int test_ponerEnArbol();
int test_ponerTresElementosEnArbol();
int test_ponerDiezElementosEnArbol();


int test_borrarEnArbol(); // eliminar por eliminar raiz
int test_borrarEnArbolHojas();
int test_borrarEnArbolNodoUnHIJO();
int test_borrarEnArbolNodoDosHIJO();


int test_buscarElementosEnArbol();
int test_buscarNodoMayor();
int test_buscarNodoMenor();
int test_alturaDelArbol();


int test_iterarArbolInOrden();
int test_iteradorOrdenInverso();
int test_iteradorPosOrder();
int test_IteradorPreOrden();

int test_esArbolBinarioBusqueda();
int test_noEsArbolBinarioBusqueda();
int test_borrarRaizArbol();
int test_noEsArbolBinarioBusquedaArbolInvalido();


// auxiliares //
void mostrarArbolito(void* data, FILE* pSalida);
void cargarArbolVector(tArbol *p, int* vec, int tam);

#endif // TEST_H_INCLUDED
