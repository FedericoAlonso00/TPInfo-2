/* El depósito de la empresa CosmeFulanito necesita cargar su stock de repuestos en forma ordenada. Para dicha tarea se solicitó categorizar a los respuestos bajo la siguiente estructura de datos:
typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];       
   chat ubicacion[100];        
}repuestos_t;
Los repuestos no están ordenados, se solicita cargarlos en una lista, la cual ordene por descripción a los repuestos para luego guardarlos en un archivo de stock con organización secuencial.
Imprimir en pantalla la lista con cada inserción.
El archivo se generará cuando el usuario decide no cargar mas productos.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];
   char ubicacion[100];
}repuestos_t;

struct lista{
    repuestos_t datos;
    struct lista *lazo;
};


int main()
{
    struct lista *p, *u, *aux, *r;
    p=u=NULL;
    char continuar, flag=0;
    FILE *fp;

    do{
        system("cls");
        aux=(struct lista*)malloc(sizeof(struct lista));
        printf("\nPartNumber: ");
        scanf("%ld",&aux->datos.partNumber);
        fflush(stdin);
        printf("\nSerialNumber: ");
        scanf("%ld",&aux->datos.serialNumber);
        fflush(stdin);
        printf("\nDescripcion: ");
        gets(aux->datos.descripcion);
        fflush(stdin);
        printf("\nUbicacion: ");
        gets(aux->datos.ubicacion);
        fflush(stdin);
        r=p;
        if(!p){
            p=u=aux;
            u->lazo=NULL;
        }
        else{
            if((strcmp(aux->datos.descripcion,p->datos.descripcion))<0){
                aux->lazo=p;
                p=aux;
            }
            else{
                if((strcmp(u->datos.descripcion,aux->datos.descripcion))<0){
                    u->lazo=aux;
                    u=aux;
                    u->lazo=NULL;
                }else flag=1;
            }
            while(flag==1){
                if((strcmp(aux->datos.descripcion,r->lazo->datos.descripcion))<0){
                    aux->lazo=r->lazo;
                    r->lazo=aux;
                    flag=0;
                }else r=r->lazo;
            }
        }
        r=p;
        while(r){
            printf("\nDescripcion: %s",r->datos.descripcion);
            printf("\nPartNumber: %ld",r->datos.partNumber);
            printf("\nSerialNumber: %ld",r->datos.serialNumber);
            printf("\nUbicacion: %s",r->datos.ubicacion);
            r=r->lazo;
        }
        printf("\n\nContinuar cargando?\t(0)NO\t(1)SI\t");
        scanf("%d",&continuar);
        fflush(stdin);
    }while(continuar);

    while(p){
        aux=p;
        p=aux->lazo;
        fwrite(&aux->datos,sizeof(repuestos_t),1,fp);
        free(aux);
    }
    fclose(fp);

    return 0;
}
