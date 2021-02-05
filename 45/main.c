/*La lista creada en el ejercicio 44 es procesada por el depósito. Para dicha tarea se pide hacer un programa que:
Descuente las cantidades solicitadas del archivo de stock, creado en el Ejercicio 41.
Hacer una cola con los repuestos en los que no se encontró stock suficiente para poder notificar a los clientes la demora de la reparación.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];
   char ubicacion[100];
   char estado;  // baja o alta
}repuestos_t;

typedef struct{
    repuestos_t repuesto;
    int cantidad;
}extraccionRepuestos_t;

struct cola{
    long partNumber;
    struct cola *lazo;
};

// ej anterior
struct lista44{
    extraccionRepuestos_t datos;
    struct lista44 *lazo;
};

int main()
{

    struct lista44 *pr, *ul, *au, *re;
    FILE *fp;
    repuestos_t bf;
    struct cola *p, *u, *aux;
    p=u=NULL;
    char cant=0,flag1=0;

    if(!(fp=fopen("stock_cosmefulanito.dat","rb+"))){
        printf("\nNo se pudo abrir el archivo de stock");
        return 0;
    }

    au=pr;
    fread(&bf,sizeof(repuestos_t),1,fp);
    while(!feof(fp) && flag1==0){
        if(au->datos.repuesto.partNumber==bf.partNumber){ 
            bf.estado='B';
            fseek(fp,-1L*sizeof(repuestos_t),SEEK_CUR);     // retrocedo 1 reg
            fwrite(&bf,sizeof(repuestos_t),1,fp);
            cant++;
        }
        if(cant==au->datos.cantidad) flag1=1;   

        fread(&bf,sizeof(repuestos_t),1,fp);
    }

    fclose(fp);

    if(flag1 != 1){  
        aux=(struct lista44*)malloc(sizeof(struct lista44));
        aux->partNumber=au->datos.repuesto.partNumber;

        free(au);

        if(!p) p=u=aux;
        else{
            u->lazo=aux;
            u=aux;
            u->lazo=NULL;
        }
    }

    return 0;
}
