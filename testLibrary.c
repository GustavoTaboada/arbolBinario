#include "testLibrary.h"

void titulo(const char*s);

int test(const char* s, int resultado)
{
  if( resultado == 1 )
  {
    Color(BLACK, LGREEN);
    printf(" %c %s\n",EXITO, s);
    Color(BLACK, WHITE);
    return 1;
  }
  Color(BLACK, RED);
  printf(" %c %s FALLO %d\n",
         FALLO, s, resultado);
  Color(BLACK, WHITE);
  return 0;
}

void crearTestSuite(const char* s, tSuite* p)
{
  *p = (tSuite) malloc(sizeof(sSuite));
  if(!*p)
    return;

  (*p)->pri = NULL;
  (*p)->ult = NULL;
  (*p)->totalExitos = 0;
  (*p)->totalFallos = 0;
  (*p)->nombre = (char*)malloc( strlen(s)+1);

  strcpy((*p)->nombre, s);

}

int addTestCase(int (*test_case)(void), tSuite* p)
{
  tTestCase* testCase = (tTestCase*)malloc(sizeof(tTestCase));
  if(!testCase) return 0;

  testCase->sig = NULL;
  testCase->funcion = test_case;

  if ( !(*p)->ult )
  {
    (*p)->pri = testCase;
    (*p)->ult = testCase;
    return 1;
  }

  (*p)->ult->sig = testCase;
  (*p)->ult = testCase;

  return 1;
}

int ejecutarSuite(tSuite* p)
{

  titulo((*p)->nombre);

  if( !(*p)->pri ) return 0;
  tTestCase* itera = (*p)->pri;

  while( itera )
  {
    if( itera->funcion())
      (*p)->totalExitos++;
    else
      (*p)->totalFallos++;

    itera = itera->sig;
  }


  printf("\n ----------------------------------\n");
  printf("  Se ejecutaron %d casos de prueba\n",(*p)->totalFallos + (*p)->totalExitos);

  Color(WHITE, BLACK);
  printf("  FALLO: %d  EXITO: %d\n",(*p)->totalFallos, (*p)->totalExitos );
  Color(BLACK, WHITE);

  printf(" ==================================\n\n");

  return 1;

}

int ejecutarSuite2(tSuite* p)
{
  int testOk;
  titulo((*p)->nombre);


  if( !(*p)->pri ) return 0;
  tTestCase* itera = (*p)->pri;

  while( itera )
  {
    testOk = itera->funcion();
    if( testOk )
      (*p)->totalExitos+=testOk;
    else
      (*p)->totalFallos++;

    itera = itera->sig;
  }
  printf("\n ----------------------------------\n");
  printf("  Se ejecutaron %d casos de prueba\n",(*p)->totalFallos + (*p)->totalExitos);
  printf("  FALLO: %d  EXITO: %d\n",(*p)->totalFallos, (*p)->totalExitos );
  printf(" ==================================\n\n");
  return 1;

}

void vaciarSuiteTest(tSuite* p)
{
  if( !(*p)->pri ) return ;
  tTestCase* itera = (*p)->pri;

  while(itera)
  {
    tTestCase* aux = itera;
    itera = itera->sig;
    free(aux);
  }
  (*p)->pri = NULL;
  (*p)->ult = NULL;
  (*p)->totalExitos = 0;
  (*p)->totalFallos = 0;
   free((*p)->nombre);
   for(int i=0; i<TAM_MAX_TEXT_GRUP; i++)
   {
     if((*p)->grupos[i])
        free((*p)->grupos[i]);
   }
}

void titulo(const char*s)
{
  Color(BLACK, YELLOW);
  int tam = strlen(s);
  printf("\n  %s\n",s);
  printf("  ");
  while(tam--)
    printf("=");
  printf("\n\n");
  Color(BLACK, WHITE);
}

void testGrup(const char* s,tSuite* suite)
{
  static int index = 0;
  static int indexEjecucion = 0;


  (*suite)->grupos[index] = (char*)malloc(strlen(s)+1);
  strcpy((*suite)->grupos[index],s);

  if( index >= 10)index = 0;
  else  index++;

  int print()
  {

    printf("\n  %s \n\n",(*suite)->grupos[indexEjecucion++]);
    (*suite)->totalExitos--;
    return 1;
  }
  addTestCase(print, suite);
}


void Color(int Background, int Text){ // Función para cambiar el color del fondo y/o pantalla

	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE); // Tomamos la consola.

	// Para cambiar el color, se utilizan números desde el 0 hasta el 255.
	// Pero, para convertir los colores a un valor adecuado, se realiza el siguiente cálculo.
	int    New_Color= Text + (Background * 16);

	SetConsoleTextAttribute(Console, New_Color); // Guardamos los cambios en la Consola.

}
