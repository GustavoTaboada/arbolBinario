#ifndef TESTLIBRARY_H_INCLUDED
#define TESTLIBRARY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#define EXITO 2
#define FALLO 26

typedef int (*test_case)(void);

typedef struct sTestCase
{
  test_case funcion;
  struct sTestCase* sig;
}
tTestCase;

#define TAM_MAX_TEXT_GRUP 10


typedef struct
{
  char* nombre;
  char* grupos[TAM_MAX_TEXT_GRUP];
  int totalExitos;
  int totalFallos;
  struct sTestCase* ult;
  struct sTestCase* pri;
}sSuite;
void Color(int Background, int Text); // Prototipo de función

enum Colors { // Listado de colores (La letra "L" al inicio, indica que es un color más claro que su antecesor).
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LGREY = 7,
	DGREY = 8,
	LBLUE = 9,
	LGREEN = 10,
	LCYAN = 11,
	LRED = 12,
	LMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
};

typedef  sSuite* tSuite;

void crearTestSuite(const char* s, tSuite* p);

void vaciarSuiteTest(tSuite* p);

int addTestCase(int (*test_case)(void), tSuite* p);

int ejecutarSuite(tSuite* p);

int test(const char* s, int resultado);

void testGrup(const char* s,tSuite* suite);



#endif // TESTLIBRARY_H_INCLUDED
