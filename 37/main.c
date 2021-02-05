/* Existe un archivo llamado "datos.dat", de tipo binario, cuya organización es secuencial. Los datos están organizados según la siguiente estructura:
struct d{                                                                                            
long clave; //Clave o Id del registro
char d[30]; // Descripcion                                                                                          
unsigned char tipo; //Tipo de datos como entero sin signo                                                                                                                                            
char b; //'A':Alta 'B':Baja                                                                                                                                                                          
}
Se Pide: Realizar una funciún que pase como parámetro la clave, entre otros parámetros, y apile dos valores, la Clave y su posición física respecto al archivo (registro 1, 2, etc), si es que el campo tipo tiene el bit 4 con valor 1. En caso de no encontrarlo mostrar por pantalla "Registro no encontrado". La función debe devolver el puntero de pila. Realizar el main con varias llamadas a dicha función y proceder a mostrar las descripciones del archivo, mediante la pila como acceso directo, NO USAR VARIABLES GLOBALES.
*/

#include <malloc.h>
#include <stdio.h>

struct datos{
  int clave;
  char d[30];
  unsigned int tipo;
};

struct pila{
  int clave;
  long acceso;
  struct pila *siguiente;
};

struct pila *funcion(int clave, struct pila *anterior);

int main(int argc, char const *argv[])
{
  struct pila *ult,*aux;
  struct datos fdata;
  long claves[]={10,20,30,40,50,60,70,80,90,11,12};
  FILE *archivo;
  ult = NULL;
  char e;
  for(e=0; e<sizeof(claves); e++)
    {
    ult = funcion(claves[e], ult);
    }
  if(ult == NULL){
    printf("No hay registro con esa clave\n");
    return 0;
  }

  do{
    if((archivo=fopen("datos.dat","rb"))==NULL){
      printf("Error al intentar abrir datos.dat\n");
      return 0;
    }
    fseek(archivo, ult -> acceso *(long)sizeof(struct datos), SEEK_SET);
    fread(&fdata, sizeof(datos), 1, archivo);
    printf("La descripcion es %s\n", fdata.d);
  }while (ult -> siguiente != NULL);
    fclose(archivo);
  return 0;
}

struct pila * funcion(int clave, struct pila *anterior){
    struct pila *aux;
    FILE *bf;
    struct datos data;
    long contador = 0;

    if((bf= fopen("datos.dat","rb"))== NULL)
        {
      printf("No se encontro archivo\n");
      return NULL;
        }

    fread(&data, sizeof(struct datos), 1, bf);
    while(!feof(bf))
        {
      if(data.clave == clave)
      {
        if(data.tipo & (1<<0))
        {
          aux = malloc(sizeof(struct pila));
          aux -> clave = data.clave;
          aux -> acceso = contador;
          if(anterior == NULL)
	  {
            aux -> siguiente = NULL;
          }else{
            aux -> siguiente = anterior;
          }
          fclose(bf);
          return aux;
        }
      }
      fread(&data, sizeof(struct datos), 1, bf);
      contador++;
        }
    fclose(bf);
    return anterior;
}
