/* El proveedor de repuestos de CosmeFulanito informó que una partida de repuestos salió con falla y debe ser devuelta. Para identificar la partida, el proveedor indicó que la falla fue en el partNumber: 1234 que tiene números de serie con el bit 3 y 5 en 1.
Para estas tareas se solicita:
Hacer una cola con todos los registros fallados
Realizar la baja física a todos los repuestos fallados
Crear un archivo donde se vuelque el contenido de la cola en orden inverso. 
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];
   char ubicacion[100];
}repuestos_t;

struct cola{
    repuestos_t datos;
    struct cola *der, *izq;
};


int main()
{
    FILE *fp, *fpnuevo;
    repuestos_t bf;
    struct cola *aux, *p, *u;
    p=u=NULL;
    char i;

    if(!(fpnuevo=fopen("nuevo.dat","wb"))){
        printf("\nNo se pudo crear el archivo");
        getch();
        return 0;
    }

    fread(&bf,sizeof(repuestos_t),1,fp);

    while(!feof(fp)){
        aux=(struct cola*)malloc(sizeof(struct cola));
        aux->datos=bf;

        bf.serialNumber=bf.serialNumber&0b101000;

        getch();
        if(bf.partNumber==1234 && bf.serialNumber==0b101000){
            if(!p) p=u=aux;   
            else{              
                u->der=aux;
                aux->izq=u;
                u=aux;
            }
        }
        else
            fwrite(&bf,sizeof(repuestos_t),1,fpnuevo);

        fread(&bf,sizeof(repuestos_t),1,fp);

    }
    fclose(fp);
    fclose(fpnuevo);
    
    while(u!=p->izq){
        aux=u;
        u=u->izq;
        bf=aux->datos;
        fwrite(&bf,sizeof(repuestos_t),1,fp);

        printf("\n----------------------------");
        printf("\nDescripcion: %s",aux->datos.descripcion);
        printf("\nPartNumber: %ld",aux->datos.partNumber);
        printf("\nSerialNumber: %ld",aux->datos.serialNumber);
        printf("\nUbicacion: %s",aux->datos.ubicacion);
        free(aux);
    }

    fclose(fp);
    getch();
    return 0;
}
