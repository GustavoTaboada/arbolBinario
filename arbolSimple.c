#include "arbolSimple.h"
#define ES_NODO_HOJA(x) ( !(x)->izq && !(x)->der  )
#define ES_NODO_COMPLETO(x) ( (x)->izq && (x)->der  )
#define TIENE_HIJO_IZQ(x) ( (x)->izq != NULL )
#define TIENE_HIJO_DER(x) ( (x)->der != NULL )

/// CREAR ///

void crearArbol(tArbol* pA)
{
  *pA = NULL;
}

tNodo* crearNodo( void* d, unsigned cantBytes)
{
  tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
  if(!nue) return NULL;
  nue->info = malloc(cantBytes);
  if(!nue->info)
  {
    free(nue);
    return NULL;
  }
  memcpy(nue->info, d, cantBytes);
  nue->tamInfo = cantBytes;
  nue->izq = NULL;
  nue->der = NULL;

  return nue;
}

/// PONER ///

int ponerEnArbol(tArbol* pA, void* d, unsigned cantBytes
                 ,int (*comparar)(void*,void*))
{
  tNodo *nue = crearNodo(d,cantBytes);
  if(!nue)
    return SIN_MEM;

  int comparado;

  while(*pA)
  {
    if((comparado = comparar(d, (*pA)->info)) < 0)
      pA = &(*pA)->izq;
    else if (comparado > 0)
      pA = &(*pA)->der;
    else
      return CLA_DUP;
  }
  *pA = nue;
  return TODO_BIEN;
}

/// Borrar  y ELIMINAR MEMORY ///

int liberarNodo(tArbol* pA)
{
  if( !*pA ) return 0;
  free( (*pA)->info);
  free(*pA);
  *pA = NULL;
  return 1;
}

int vaciarArbol(tArbol* pA)
{
  int cont = 0;
  if(!*pA)
  {
    return cont;
  }
  vaciarArbol( &(*pA)->izq );
  vaciarArbol( &(*pA)->der );
  cont +=liberarNodo(pA);
  return cont;
}

int borrarRaizArbol(tArbol* pA, void* d
                    ,int (*comparar)(void*,void*))
{
  tArbol arbol = *pA;
  tArbol nodo = *pA;

  if(!arbol) return 0;

  free(nodo->info);

  if( !nodo->der && !nodo->izq) // ES_NODO_HOJA(nodo)
  {
    liberarNodo(&nodo);
    *pA = NULL;
    return 1;
  }

  if(  nodo->der && !nodo->izq) // TIENE_SOLO_HIJO_DER(nodo)
  {
    *pA = nodo->der;
    liberarNodo(&nodo);
    return 1;
  }

  if( !nodo->der &&  nodo->izq) // TIENE_SOLO_HIJO_IZQ(nodo)
  {
    *pA = nodo->izq;
    liberarNodo(&nodo);
    return 1;
  }
  /**
  * if( no_es_completo(nodo) )
    {
      if( ES_NODO_HOJA(nodo))
         *pA = NULL;
      else if( TIENE_SOLO_HIJO_DER(nodo) )
         *pA = nodo->der;
      else
         *pA = nodo->izq;
      liberarNodo(&nodo);
      return 1;
    }
  **/
  /// caso nodo con dos hijos

  int alturaIsq = alturaArbol(&arbol->izq);
  int alturaDer = alturaArbol(&arbol->der);
  int comparo =   alturaIsq - alturaDer;


  tNodo** mayorDeLosMenores = buscarNodoMayor(&arbol->izq);
  tNodo** menorDeLosMayores = buscarNodoMenor(&arbol->der);

  tNodo** liberar = comparo < 0 ?  mayorDeLosMenores :menorDeLosMayores  ;

  nodo->info = malloc((*liberar)->tamInfo);

  memcpy(nodo->info, (*liberar)->info,(*liberar)->tamInfo );

  borrarRaizArbol(liberar, d, comparar);

  return 1;

}

int borraraNodoArbol(tArbol* pA, void* d
                     ,int (*comparar)(void*,void*))
{

  if(!*pA) return false;
  tNodo** borrar = buscarNodoAeliminar(pA, d, comparar);

  if(!(*borrar))
    return false;

  return borrarRaizArbol(borrar, d, comparar);
 // return eliminarRaizArbolBinBusq(borrar);
}
//////////////


//alturaArbolBin(const tArbol * p);

int eliminarRaizArbolBinBusq(tArbol * p)
{
  tNodo ** remp;
    tNodo         * elim;
  if(!*p)
    return 0; ///ARBOL_VACIO

  free((*p)->info);
  if (!(*p)->izq && !(*p)->der)
  {
    free(*p);
    *p = NULL;
    return 1; ///OK
  }
 //  int i = alturaArbolBin(&(*p)->izq);
  remp = alturaArbol(&(*p)->izq) > alturaArbol(&(*p)->der) ?
         mayorNodoArbolBinBusq(&(*p)->izq):
         menorNodoArbolBinBusq(&(*p)->der);

  elim = *remp;
  (*p)->info = elim->info;
  (*p)->tamInfo = elim->tamInfo;

  *remp = elim->izq ? elim->izq : elim->der;

  free(elim);

  return 1; ///OK
}
tNodo ** mayorNodoArbolBinBusq(const tArbol * p)
{
  if(!*p)
    return NULL;
  while((*p)->der)
    p = &(*p)->der;
  return (tNodo **) p;
}


tNodo ** menorNodoArbolBinBusq(const tArbol * p)
{
  if(!*p)
    return NULL;
  while((*p)->izq)
    p = &(*p)->izq;
  return (tNodo **) p;
}
////////////////////////////////////////////////////////////////
/// BUSCAR ///

tNodo** buscarNodoAeliminar(tArbol* pA, void* d
                            ,int (*comparar)(void*,void*))
{
  if(!*pA) return NULL;

  int cmp = comparar((*pA)->info, d);

  if(!cmp)
    return &(*pA);

  if( cmp < 0)
    return buscarNodoAeliminar( &(*pA)->der, d, comparar);

  return buscarNodoAeliminar( &(*pA)->izq, d, comparar);

  return NULL;
}
int esABB(tArbol* p,int (*comparar)(void*,void*))
{
#define NO_ES_ABB 0

  tArbol arbol = *p;

  if(!arbol)
    return 0;

  int cumple = 1;

  if( arbol->der )
  {
    tNodo** menor =  buscarNodoMenorDesordenado(&arbol->der, comparar);// buscarNodoMenor(&arbol->der);

    if( comparar( arbol->info, arbol->der->info ) >= 0   ||
        comparar( arbol->info, (*menor)->info ) >= 0 )
    {
      return NO_ES_ABB;
    }

    cumple =  esABB( &arbol->der, comparar);

    if( !cumple )
    {
      return NO_ES_ABB;
    }
  }

  if( arbol->izq )
  {
    tNodo** mayor =  buscarNodoMayorDesordenado(&arbol->izq, comparar);// buscarNodoMayor(&arbol->izq);//

    if( comparar( arbol->info, arbol->izq->info ) <= 0   ||
        comparar( arbol->info, (*mayor)->info ) <= 0 )
    {
      return NO_ES_ABB;
    }

    cumple = esABB( &arbol->izq, comparar);

    if( !cumple )
    {
      return NO_ES_ABB;
    }
  }

  return cumple;
}


int estaEnArbol(tArbol* pA, void* d
                ,int (*comparar)(void*,void*))
{
  if(!*pA) return false;
// tArbol abb = *pA;
  int cmp = comparar((*pA)->info, d);

  if( cmp < 0)
  {
    return estaEnArbol( &(*pA)->der, d, comparar);
  }
  else if ( cmp > 0)
  {
    return estaEnArbol( &(*pA)->izq, d, comparar);
  }
  return true;
}

tNodo** buscarNodoMayor(tArbol* pA)
{
  if(!*pA) return NULL;
  if( !(*pA)->der)
    return pA;
  return buscarNodoMayor(&(*pA)->der);
}

tNodo** buscarNodoMayorDesordenado(tArbol* p, int (*comparar)(void*,void*))
{
  if(!*p)
    return NULL;

  tNodo** mayor = &(*p);
  tNodo** hijo;

  if( (*p)->izq )
  {
    hijo = buscarNodoMayorDesordenado(&(*p)->izq, comparar);

    if( comparar( (*mayor)->info, (*hijo)->info)< 0 )
        mayor = hijo;
  }

  if( (*p)->der )
  {
    hijo = buscarNodoMayorDesordenado(&(*p)->der, comparar);

    if(  comparar((*mayor)->info, (*hijo)->info)< 0 )
        mayor = hijo;
  }

  return mayor;

}

tNodo** buscarNodoMenorDesordenado(tArbol* p, int (*comparar)(void*,void*))
{
  if(!*p)
    return NULL;

  tNodo** menor = &(*p);
  tNodo** hijo;

  if( (*p)->izq )
  {
    hijo = buscarNodoMenorDesordenado(&(*p)->izq, comparar);

    if( comparar( (*menor)->info, (*hijo)->info)> 0 )
        menor = hijo;
  }

  if( (*p)->der)
  {
    hijo = buscarNodoMenorDesordenado(&(*p)->der, comparar);

    if(  comparar((*menor)->info, (*hijo)->info)> 0 )
        menor = hijo;
  }

  return menor;

}

tNodo** buscarNodoMenor(tArbol* pA)
{
  if(!*pA) return NULL;
  if( !(*pA)->izq)
    return pA;
  return buscarNodoMenor(&(*pA)->izq);
}
// iterativa //
tNodo** buscarNodoMenorItera(tArbol* p)
{
  if(!*p)
    return NULL;

  while(*p && (*p)->izq )
  {
      p = &(*p)->izq;
  }

  return (tNodo**) p;

}

/// Iteradores internos //


int mostarArbol(tArbol* pA
                ,void (*mostrar)(void* data, FILE* salida)
                ,FILE* sal)
{
  // recurciva Pre-Orden
  if(!*pA)
    return 0;

  mostrar( (*pA)->info, sal);

  mostarArbol(&(*pA)->izq, mostrar, sal);

  mostarArbol(&(*pA)->der, mostrar, sal);

  return 1;
}

// recursivas //
int iterarEnOrden(tArbol *p, functionAccion accion,void* extra)
{
  tArbol arbol = *p;
  int cont = 0;

  if(!arbol)
    return cont;

  cont += iterarEnOrden(&arbol->izq, accion, extra);

  if(accion)
    accion(arbol->info, extra);

  cont++;

  cont += iterarEnOrden(&arbol->der, accion, extra);

  return cont;
}

int iterarPosOrden(tArbol *p, functionAccion accion,void* extra)
{
  int cont = 0;

  if(!*p)
    return cont;

  cont += iterarPosOrden(&(*p)->izq, accion, extra);

  cont += iterarPosOrden(&(*p)->der, accion, extra);

  if(accion)
    accion((*p)->info, extra);

  cont++;

  return cont;
}


int iterarPreOrden(tArbol *p, functionAccion accion,void* extra)
{
  int cont = 0;

  if(!*p)
    return cont;

  if(accion)
    accion((*p)->info, extra);

  cont += iterarPreOrden(&(*p)->izq, accion, extra);

  cont += iterarPreOrden(&(*p)->der, accion, extra);

  cont++;
  return cont;
}

int iterarEnOrdenInverso(tArbol *p, functionAccion accion,void* extra)
{
  tArbol arbol = *p;

  int cont = 0;

  if(!arbol)
    return cont;

  cont += iterarEnOrdenInverso(&arbol->der, accion, extra);

  accion(arbol->info, extra);
  cont++;

  cont += iterarEnOrdenInverso(&arbol->izq, accion, extra);

  return cont;
}




/// auxuliares ///
int alturaArbol(tArbol *p)
{
  tArbol abb = *p;

  if(!abb)
    return 0;

  int alturaIsq = alturaArbol(&abb->izq);

  int alturaDer = alturaArbol(&abb->der);

  return alturaIsq > alturaDer
         ? alturaIsq + 1
         : alturaDer + 1;

}




/// para test catedra //
void imprimirConForma(void * info, unsigned tam, unsigned n, void * params)
{
  int * i = (int *) info;
  printf("%*s-%3d-\n",n*5,"", *i);
}

void printBonito( tArbol *p, unsigned nivel)
{
  if(!(*p))
  {
    return;
  }
  printBonito(&(*p)->izq, nivel+1);
  imprimirConForma( (*p)->info, 0, nivel, NULL);
  printBonito(&(*p)->der, nivel+1);
  return ;

}

void imprimir(void * info, unsigned tam, unsigned n, void * params)
{
  int * i = (int *) info;
  printf("-%d-", *i);
}

unsigned leerDesdeVectorEnteros(void ** d, void * vec, unsigned pos, void * params)
{
  *d = malloc(sizeof(int));
  if(!*d)
    return 0;
  memcpy(*d, vec+(sizeof(int)*pos), sizeof(int));
  return sizeof(int);
}

int cmp_ent( void *v1,  void *v2)
{
  return *((int*)v1)-*((int*)v2);
}





