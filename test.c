#include "test.h"

#define true 1
#define false 0
#define EXITO 2
#define FALLO 26

/// creacion y destruccion ///
int test_crearArbol()
{
  tArbol arbol;
  crearArbol(&arbol);
  int espero = arbol != NULL;

  return test("test crear arbol.", espero);
}

int test_crearNodo()
{
  int dato = 33;
  unsigned pesoDatos = sizeof(dato);
  tNodo* nodo = crearNodo( (void*)&dato, pesoDatos);

  if(!nodo)
    return test("test crear nodo.",nodo!=NULL);

  int espero =  nodo->tamInfo == pesoDatos
                && *(int*)nodo->info == dato
                && nodo->der == NULL
                && nodo->izq == NULL;

  return test("test crear nodo.",espero);
}

int test_vaciarArbol()
{
  const int TAM = 10;
  tArbol arbol;
  crearArbol(&arbol);

  int dato[] = {63,24,70,45,98,14,9,55,77,22};
  cargarArbolVector(&arbol, dato, TAM);

  int retornoFuncionTest = vaciarArbol(&arbol);

  return test("carga un arbol y lo vacia.",
              arbol == NULL &&
              retornoFuncionTest);

}


/// agregar elementos ///

int test_ponerEnArbol()
{
  tArbol arbol;
  crearArbol(&arbol);

  int dato = 33;
  int tam = sizeof(dato);

  int retornoFuncionTest = ponerEnArbol(&arbol, (void*)&dato, tam, cmp_ent);

  int  infoGuardada = *(int *) arbol->info;


  test("poner un entero en el arbol.",
       retornoFuncionTest  &&
       infoGuardada == dato
      );

  vaciarArbol(&arbol);
  return 1;

}

int test_ponerTresElementosEnArbol()
{
  tArbol arbol;
  crearArbol(&arbol);

  int dato[] = {23,24,11};
  int inserciones = 3;
  int retornoFuncionTest = 0;
  int buscados = 0;

  for(int i=0; i<inserciones; i++)
  {
    retornoFuncionTest += ponerEnArbol(&arbol, (void*)&dato[i], sizeof(int), cmp_ent);
  }
  for(int i=0; i<inserciones; i++)
  {
    buscados += estaEnArbol(&arbol, (void*)&dato[i],cmp_ent);
  }

  test("poner tres elementos enteros en el arbol.",
       retornoFuncionTest == inserciones &&
       buscados == inserciones &&
       arbol != NULL );


  vaciarArbol(&arbol);

  return 1;
}

int test_ponerDiezElementosEnArbol()
{
  tArbol arbol;
  crearArbol(&arbol);

  int dato[] = {63,24,70,45,98,14,9,55,77,22};
  int inserciones = 10;
  int retornoFuncionTest = 0;
  int buscados = 0;

  for(int i=0; i<inserciones; i++)
  {
    retornoFuncionTest += ponerEnArbol(&arbol, (void*)&dato[i], sizeof(int), cmp_ent);
  }

  for( int i=0; i<inserciones; i++)
  {
    buscados += estaEnArbol(&arbol,(void*)&dato[i], cmp_ent);
  }

  test( "poner Diez entero en el arbol.",
        retornoFuncionTest == inserciones &&
        buscados == inserciones &&
        arbol != NULL);

  vaciarArbol(&arbol);

  return 1;
}


/// Borrar  y destruccion ///

int test_borrarEnArbolHojas()
{
  int TAM = 10;
  tArbol arbol;
  crearArbol(&arbol);

  int dato[] = {63,24,70,45,98,14,9,55,77,22};
  cargarArbolVector(&arbol, dato, TAM);

  int sinHijos[] = {22,9,55,77,98};
  int retornoFuncionTest = 0;
  int encontrado = 0;



  for(int i=0; i<5; i++)
  {
    retornoFuncionTest = borraraNodoArbol(&arbol,(void*)&sinHijos[i],cmp_ent);

    if( retornoFuncionTest !=1)
      return test("Elimino una hoja del arbol",retornoFuncionTest!=1 );

    encontrado = estaEnArbol(&arbol,(void*)&sinHijos[i], cmp_ent);

    if(encontrado)
      return test("Elimino una hoja del arbol",encontrado!=0 );
  }

  vaciarArbol(&arbol);
  return test("Elimino 5 hojas del arbol.", true );

}

int test_borrarEnArbolNodoUnHIJO()
{
  int TAM = 14;
  tArbol arbol;
  crearArbol(&arbol);

  int dato[] = {63,24,70,45,98,14,9,55,77,22,100,2,99,76};
  cargarArbolVector(&arbol, dato, TAM);

  int conUnHijo[4] = {45,9,77,100};
  int hijos[4] = {55,2,76,99};
  int retornoFuncionTest = 0;
  int encontrado = 0;
  int testOk = 0;


  for(int i=0; i<4; i++)
  {
    retornoFuncionTest += borraraNodoArbol(&arbol,(void*)&conUnHijo[i],cmp_ent);

    encontrado += estaEnArbol(&arbol,(void*)&conUnHijo[i], cmp_ent);
  }


  testOk = test("Elimino nodos con un hijo.",
                encontrado == 0 &&
                retornoFuncionTest == 4 );


  for(int j=0; j<4; j++)
  {
    encontrado += estaEnArbol(&arbol,(void*)&hijos[j], cmp_ent);
  }

  testOk += test("Los nodos hurfanos estan en el arbol.",
                 encontrado == 4 );

  vaciarArbol(&arbol);
  return testOk == 2;
}

int test_borrarEnArbolNodoDosHIJO()
{
  int TAM = 15;
  tArbol arbol;
  crearArbol(&arbol);

  int dato[] =  {63,24,70,45,98,14,9,55,77,22,23,8,15,97,100};
  cargarArbolVector(&arbol, dato, TAM);
// printBonito(&arbol,0);
  int nodoConDosHijo[] = {24, 70};
  int cantEliminar = 2;
  int huerfanos[] = {14, 45, 97, 98};
  int cantHuerfanos = 4;

  int retornoFuncionTest = 0;
  int encontrado = 0;

  for(int i=0; i<cantEliminar; i++)
  {
    retornoFuncionTest += borraraNodoArbol(&arbol,(void*)&nodoConDosHijo[i],cmp_ent);

    encontrado += estaEnArbol(&arbol,(void*)&nodoConDosHijo[i], cmp_ent);

  }
  int buscarHurfanos = 0;
  for(int j=0; j<cantHuerfanos; j++)
  {
    buscarHurfanos += estaEnArbol(&arbol,(void*)&huerfanos[j], cmp_ent);
  }

// printBonito(&arbol,0);
 int retorno = test("barrado elementos del arbol con dos hijos.",
                    retornoFuncionTest == cantEliminar &&
                    encontrado == 0 &&
                    buscarHurfanos == cantHuerfanos &&
                    esABB(&arbol, cmp_ent));

 vaciarArbol(&arbol);

 return  retorno;
}
int test_borrarRaizArbol()
{
  int TAM = 15;
  tArbol arbol;
  crearArbol(&arbol);

  int dato[] =  {63,24,70,45,98,14,9,55,77,22,23,8,15,97,100};
  cargarArbolVector(&arbol, dato, TAM);
  test("barrado raiz valida que arbol de partida es ABB valido.",
       esABB(&arbol, cmp_ent) );

  int nodoConDosHijo[] = {63};
  int cantEliminar = 1;
  int huerfanos[] = {24, 70};
  int cantHuerfanos = 2;

  int retornoFuncionTest = 0;
  int encontrado = 0;


  retornoFuncionTest = borraraNodoArbol(&arbol,(void*)&nodoConDosHijo[0],cmp_ent);

  encontrado = estaEnArbol(&arbol,(void*)&nodoConDosHijo[0], cmp_ent);


  int buscarHurfanos = 0;
  for(int j=0; j<cantHuerfanos; j++)
  {
    buscarHurfanos += estaEnArbol(&arbol,(void*)&huerfanos[j], cmp_ent);
  }


  test("barrado raiz del arbol. ",
       retornoFuncionTest == cantEliminar
      );

  test("barrado raiz del arbol. elemneto eliminado",

       encontrado == 0 );

  test("barrado raiz del arbol. hurfanos perdidos",
       buscarHurfanos == cantHuerfanos
      );

  test("barrado raiz del arbol, no es ABB valido.",

       esABB(&arbol, cmp_ent) );
  //printBonito(&arbol,0);
  vaciarArbol(&arbol);

  return   retornoFuncionTest == cantEliminar &&
           buscarHurfanos == cantHuerfanos  &&
           encontrado == 0 ;
}

/// Buscar ///

int test_buscarElementosEnArbol()
{
  int TAM = 10;
  tArbol arbol;
  crearArbol(&arbol);

  int dato[] = {63, 24, 70, 45, 98, 14, 9, 55, 77, 22};
  int inexistentes[] = { 456, 89, 0, 99, 987, 25, 15, -80, 90, 101};

  cargarArbolVector(&arbol, dato, TAM);

  int retornoFuncionTest = 0;

  for(int i=0; i<TAM; i++)
  {
    retornoFuncionTest += estaEnArbol(&arbol, (void*)&dato[i], cmp_ent);
    retornoFuncionTest += estaEnArbol(&arbol, (void*)&inexistentes[i], cmp_ent);
  }

  vaciarArbol(&arbol);

  return test("buscar elementos enteros en el arbol.",
              retornoFuncionTest == TAM);

}
int test_buscarNodoMayor()
{
  int TAM = 10;
  tArbol arbol;
  crearArbol(&arbol);

  int dato[] = {63,24,70,45,98,14,9,55,77,22};
  int mayor = 98;
  cargarArbolVector(&arbol, dato, TAM);

  tNodo** nodoMayor = buscarNodoMayor(&arbol);

  int result = test("buscar nodo mayor enteros en el arbol.",
                    *(int *)(*nodoMayor)->info == mayor);

  vaciarArbol(&arbol);
  return result;
}
int test_buscarNodoMenor()
{
  int TAM = 10;
  tArbol arbol;
  crearArbol(&arbol);

  int dato[] = {63,24,70,45,98,14,9,55,77,22};
  int menor = 9;
  cargarArbolVector(&arbol, dato, TAM);

  tNodo** nodoMenor = buscarNodoMenor(&arbol);

  int res = test( "buscar nodo menor enteros en el arbol.",
                  *(int *)(*nodoMenor)->info == menor );

  vaciarArbol(&arbol);
  return res;
}


/// Iteradores internos ///

int test_iterarArbolInOrden()
{
  tArbol arbol;
  crearArbol(&arbol);

  int TAM = 10;
  int dato[] = {63,24,70,45,98,14,9,55,77,22};
  cargarArbolVector(&arbol, dato, TAM);

  int enOrden[] = {9,14,22,24,45,55,63,70,77,98};
  int testOk = 1;

  int cmpOrden(void*a,void*b)
  {
    static int index =0;
    int dato =*(int *) a;
    int* vec = (int*) b;
    if(dato != vec[index])
    {
      testOk = 0;
      index++;
      return 0;//assert(("Falla iterando el Arbol en Orden",NULL));
    }
    index++;
    return 1;
  }

  int cant = iterarEnOrden(&arbol, cmpOrden, (void *)&enOrden);

  vaciarArbol(&arbol);

  return test("Iterado del arbol en orden.", testOk && cant == TAM );
}

int test_iteradorOrdenInverso()
{
  const int TAM = 10;
  tArbol arbol;
  crearArbol(&arbol);

  int dato[10] = {63,24,70,45,98,14,9,55,77,22};
  cargarArbolVector(&arbol, dato, TAM);


  int ordenInverso[] = {98,77,70,63,55,45,24,22,14,9};
  int testOk = 1;

  int cmpInverso(void*a,void*b)
  {
    static int index =0;
    int dato =*(int *) a;
    int* vec = (int*) b;
    if(dato != vec[index])
    {
      testOk = 0;
      index++;
      return 0;//assert(("Falla iterando el Arbol en Orden inverso.",NULL));
    }
    index++;
    return 1;
  }

  int cant = iterarEnOrdenInverso(&arbol, cmpInverso, (void *) &ordenInverso);

  vaciarArbol(&arbol);

  return test("Iterado del arbol en orden inverso.",testOk && cant == TAM);

}

int test_iteradorPosOrder()
{
  const int TAM = 10;
  tArbol arbol;
  crearArbol(&arbol);

  int dato[10] = {63,24,70,45,98,14,9,55,77,22};
  cargarArbolVector(&arbol, dato, TAM);


  int posOrden[] = {9,22,14,55,45,24,77,98,70,63};
  int testOk = 1;

  int cmpPosOrden(void*a,void*b)
  {
    static int index =0;
    int dato =*(int *) a;
    int* vec = (int*) b;
    if(dato != vec[index])
    {
      testOk = 0;
      index++;
      return 0; //assert(("Falla iterando  Arbol en pos Orden.",NULL));
    }
    index++;
    return 1;
  }

  int cant = iterarPosOrden(&arbol, cmpPosOrden, (void *) &posOrden);

  vaciarArbol(&arbol);

  return test("Iterado del arbol en pos orden.",testOk && cant == TAM);

}

int test_IteradorPreOrden()
{
  const int TAM = 10;
  tArbol arbol;
  crearArbol(&arbol);

  int dato[10] = {63,24,70,45,98,14,9,55,77,22};
  cargarArbolVector(&arbol, dato, TAM);

  int preOrden[] = {63,24,14,9,22,45,55,70,98,77};
  int testOk = 1;

  int cmpPreOrden(void*a,void*b)
  {
    static int index =0;

    int dato =*(int *) a;
    int* vec = (int*) b;

    if(dato != vec[index])
    {
      testOk = 0;
      index++;
      return 0;///assert(("Falla iterando  Arbol en pre Orden.",NULL));
    }
    index++;
    return 1;
  }

  int cant = iterarPreOrden(&arbol, cmpPreOrden, (void *) &preOrden);

  vaciarArbol(&arbol);

  return test("Iterado del arbol en pre orden.", testOk && cant == TAM);

}

int test_alturaDelArbol()
{
  const int TAM = 10;
  tArbol arbol;
  crearArbol(&arbol);
  int espero;
  int aciertos =0;
  int dato[10] = {63,24,70,45,98,14,9,55,77,22};

  espero = alturaArbol(&arbol) == 0 ? 1 : 0;

  aciertos += test("La Altura del arbol vacio es de  0.", espero);

  cargarArbolVector(&arbol, dato, TAM);

  espero = alturaArbol(&arbol) == 4 ? 1 : 0;

  aciertos += test("La Altura del arbol de 10 elementos es de 4.", espero);

  return aciertos;
}

/// ORDENAR    es algo //


int test_esArbolBinarioBusqueda()
{
  const int TAM = 10;
  tArbol arbol;
  crearArbol(&arbol);

  int dato[] = {63,24,70,45,98,14,9,55,77,22};
  cargarArbolVector(&arbol, dato, TAM);

  int funcionTest = esABB(&arbol, cmp_ent);

  vaciarArbol(&arbol);

  return test("El arbol  es ABB.", funcionTest );
}
int test_noEsArbolBinarioBusqueda()
{
  int TAM = 10;
  tArbol arbol;
  crearArbol(&arbol);

  int dato[] = {63,24,70,45,98,14,9,55,77,22};
  cargarArbolVector(&arbol, dato, TAM);

  int falso = 60;
  (arbol->izq->izq->izq->info) = (void*)&falso;

  int es = esABB(&arbol, cmp_ent);

  vaciarArbol(&arbol);
  test("El arbol No es ABB nodo hijo izq > padre.", !es );

  cargarArbolVector(&arbol, dato, TAM);

  falso = 11;
  (arbol->izq->izq->der->info) = (void*)&falso;

  es = esABB(&arbol, cmp_ent);

  vaciarArbol(&arbol);
  return test("El arbol No es ABB nodo hijo der < padre.", !es );
};



int test_noEsArbolBinarioBusquedaArbolInvalido()
{
  int TAM = 10;
  tArbol arbol;
  crearArbol(&arbol);

  int dato[] = {63,24,70,45,98,14,9,55,77,22};
  cargarArbolVector(&arbol, dato, TAM);

  int falso = 25; // 24
  (arbol->izq->izq->der->info) = (void*)&falso;

  int es = esABB(&arbol, cmp_ent);

  test("El arbol No es ABB,un hijo isq mayor que un abuelo.", !es );
  vaciarArbol(&arbol);

//  cargarArbolVector(&arbol, dato, TAM);
//
//  falso = 69;// 70 //63
//  (arbol->der->der->izq->info) = (void*)&falso;
//
//  es += esABB(&arbol, cmp_ent);
//
//  vaciarArbol(&arbol);
  return test("El arbol No es ABB,un hijo der mayor que un abuelo.", !es );
};
/// auxiliares ///

void mostrarArbolito(void* data, FILE* pSalida)
{
  fprintf(pSalida,"-%d-",*(int*)data);

}

void cargarArbolVector(tArbol *p, int* vec, int tam)
{
  for(int i=0; i<tam; i++)
  {
    ponerEnArbol(p, (void*)&vec[i], sizeof(int), cmp_ent);
  }
}

