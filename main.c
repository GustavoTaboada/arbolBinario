#include "main.h"
#define true 1
#define false 0
int main()
{
  tSuite suite;

  crearTestSuite("TestTDA arbol binario de busqueda ABB-BST",&suite);

  testGrup("Prueba primitivas para crear y destruir ",&suite);
  addTestCase(test_crearArbol, &suite);
  addTestCase(test_crearNodo, &suite);
  addTestCase(test_vaciarArbol, &suite);


  testGrup("Prueba primitivas insercion",&suite);
  addTestCase(test_ponerEnArbol, &suite);
  addTestCase(test_ponerTresElementosEnArbol, &suite);
  addTestCase(test_ponerDiezElementosEnArbol, &suite);

  testGrup("Prueba iteradores internos", &suite);
  addTestCase(test_iterarArbolInOrden, &suite);
  addTestCase(test_iteradorOrdenInverso, &suite);
  addTestCase(test_iteradorPosOrder, &suite);
  addTestCase(test_IteradorPreOrden, &suite);

  testGrup("Prueba primitivas de busqueda y verificacion ",&suite);
  addTestCase(test_buscarElementosEnArbol, &suite);
  addTestCase(test_buscarNodoMenor, &suite);
  addTestCase(test_buscarNodoMayor, &suite);

  addTestCase(test_alturaDelArbol, &suite);
  addTestCase( test_esArbolBinarioBusqueda,&suite);
  addTestCase( test_noEsArbolBinarioBusqueda,&suite);
  addTestCase( test_noEsArbolBinarioBusquedaArbolInvalido,&suite);

  testGrup("Prueba primitivas borrarEnArbol ", &suite);
  addTestCase(test_borrarEnArbolHojas, &suite);
  addTestCase(test_borrarEnArbolNodoUnHIJO, &suite);
  addTestCase(test_borrarEnArbolNodoDosHIJO, &suite);
  addTestCase( test_borrarRaizArbol,&suite);




  ejecutarSuite(&suite);

  vaciarSuiteTest(&suite);

  printf("\nTodo Ok\n");
  return 0;
}
