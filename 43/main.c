/*El servicio técnico de CosmeFulanito recibe órdenes de trabajo diarias. Las mismas son cargadas en un archivo secuencial por el personal de recepción bajo la siguiente estructura de datos:
typedef struct{
   long numeroDeOrden;
   char cliente[40];       
   char descripciondeFalla[200];        
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestos_t;
Se pide:
Hacer una pila con las órdenes de trabajo de forma tal que la más vieja sea la última en cargarse.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct{
   long numeroDeOrden;
   char cliente[40];
   char descripciondeFalla[200];
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestos_t;

struct pila{
    repuestos_t datos;
    struct pila *lazo;
};

int main()
{
    char flag=0, continuar;
    FILE *fp;
    repuestos_t bf;
    struct pila *p,*aux, *r;
    p=NULL;

    if(!(fp=fopen("ordenes.dat","ab"))){
        printf("\nError: No se puede abrir o crear archivo");
        return 0;
    }

    do{
        printf("\nNumero de orden: ");
        scanf("%ld",&bf.numeroDeOrden);
        fflush(stdin);
        printf("\nCliente: ");
        gets(bf.cliente);
        fflush(stdin);
        printf("\nDescripcion de falla: ");
        gets(bf.descripciondeFalla);
        fflush(stdin);
        printf("\nModelo: ");
        gets(bf.modelo);
        fflush(stdin);
        printf("\nFecha: ");
        gets(bf.fecha);
        fflush(stdin);
        printf("\nHora: ");
        gets(bf.hora);
        fflush(stdin);
        fwrite(&bf,sizeof(repuestos_t),1,fp);

        aux=(struct pila*)malloc(sizeof(repuestos_t));
        aux->datos=bf;
        r=p;
        if(!p) p=aux;
        else{
            if(aux->datos.fecha < p->datos.fecha){ 
                aux->lazo=p;
                p=aux;
                flag=1;
            }
            while(r->lazo && flag==0){
                if(aux->datos.fecha > r->lazo->datos.fecha) r=r->lazo;
                else{
                    r->lazo=aux;
                    aux->lazo=r->lazo->lazo;
                    flag=1;
                }
            }
            flag=0;
        }
        printf("\nIngresar otra orden?    ");
        scanf("%d",&continuar);
        fflush(stdin);
    }while(continuar);
    fclose(fp);
    return 0;
}
