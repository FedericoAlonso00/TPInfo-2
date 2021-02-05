/*El servicio técnico utiliza la pila generada en el ejercicio 43 en su labor diaria. Cada técnico toma una tarea de la pila y genera un orden de extracción de repuestos al depósito. Para optimizar los viajes al depósito se arma una lista con los repuestos que cada orden necesita utilizando la siguiente estructura:
typedef struct{
    repuestos_t repuesto;        
    int cantidad;
}extraccionRepuestos_t;
Se pide cargar la lista de repuestos solicitados por los técnicos. Tener en cuenta que varios técnicos pueden necesitar la misma parte, y en esos casos se debe incrementar la cantidad pedida en la lista.
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
}orden_t;

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];
   char ubicacion[100];
}repuestos_t;

typedef struct{
    repuestos_t repuesto;
    int cantidad;
}extraccionRepuestos_t;

struct pila{
    orden_t datos;
    struct pila *lazo;
};

struct lista{
    extraccionRepuestos_t datos;
    struct lista *lazo;
};

int main()
{
    char flag=0, continuar;
    FILE *fp;
    orden_t bf;
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
        fwrite(&bf,sizeof(orden_t),1,fp);

        aux=(struct pila*)malloc(sizeof(orden_t));
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

        printf("\nIngresar otra orden?   ");
        scanf("%d",&continuar);
        fflush(stdin);
    }while(continuar);

    extraccionRepuestos_t bfr;
    struct lista *pr, *ul, *au, *re;
    pr=ul=NULL;
    flag=0;
 
    do{
        printf("\nPresione una tecla para tomar la tarea mas antigua ");
        getch();
        aux=p;
        p=p->lazo;
        printf("\nNum Orden: %d",aux->datos.numeroDeOrden);
        printf("\nCliente: %s",aux->datos.cliente);
        printf("\nDescripcion de falla; %s",aux->datos.descripciondeFalla);
        printf("\nModelo: %s",aux->datos.modelo);
        printf("\nFecha: %s",aux->datos.fecha);
        printf("\nHora: %s",aux->datos.hora);

        free(aux);

        au=(struct lista*)malloc(sizeof(struct lista));

        printf("\n\nPartNumber del repuesto solicitado: ");
        scanf("%d",&au->datos.repuesto.partNumber);
        printf("\nCuantos repuestos necesita?\t");
        scanf("%d",&au->datos.cantidad);

        // lista de extraccion de repuestos
        if(!pr) pr=au;
      
        re=pr;
        if(pr->datos.repuesto.partNumber==au->datos.repuesto.partNumber){
                pr->datos.cantidad= pr->datos.cantidad + au->datos.cantidad;
                flag=1;
        }
        while(re->lazo && flag==0){

            if(re->lazo->datos.repuesto.partNumber==au->datos.repuesto.partNumber){
                re->lazo->datos.cantidad=re->datos.cantidad+au->datos.cantidad;
                flag=1;
            }else r=r->lazo;
        }
        if(flag=0){
            ul->lazo=au;
            ul=au;
            ul->lazo=NULL;
        }

        printf("\nTomar otra tarea?   ");
        scanf("%d",&continuar);
        fflush(stdin);
    }while(continuar);

    fclose(fp);
    return 0;
}
