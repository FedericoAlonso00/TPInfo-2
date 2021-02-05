/*Hacer un programa que tome los datos de medición de potencia, cargados por el usuario, de un sistema de medición a distancia.
Los datos que cargará el usuario tienen la siguiente estructura:
char desc[60];
    unsigned char potencia;
    unsigned int estado;
Donde estado es la multiplicación del valor ASCII de la primer letra de la descripción por la potencia. Los datos cargados se deberán guardar en una lista ordenada, de mayor a menor, del valor de potencia. Una vez finalizada la carga guardar los datos en un archivo de organización directa llamado "potencia.dat" imprimiendo en pantalla los datos.
*/
    

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct d{
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
};

struct e{
    int id;
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
};

struct lista{
    struct d datos;
    struct lista * lazo;
};

int main()
{
    FILE *fp;
    struct lista *p, *u, *aux, *r;
    struct e bf;
    bf.id=0;
    p=u=NULL;
    char continuar, flag=0;
    fflush(stdin);
    do{
        aux=(struct lista*)malloc(sizeof(struct lista));
        printf("\nDescripcion: ");
        gets(aux->datos.desc);
        fflush(stdin);
        printf("\nPotencia: ");
        scanf("%d", &aux->datos.potencia);
        aux->datos.estado=aux->datos.potencia*aux->datos.desc[0];
        r=p;
        if(p){
            if(aux->datos.potencia>p->datos.potencia){
                aux->lazo=p;
                p=aux;
                flag=1;
            }
            while(r->lazo && flag == 0){
                if(aux->datos.potencia<r->lazo->datos.potencia)r=r->lazo;
                else{
                    aux->lazo=r->lazo;
                    r->lazo=aux;
                    flag=1;
                }
            }
            if(r==u && flag==0){
                u->lazo=aux;
                u=aux;
                u->lazo=NULL;
                flag=1;
            }
            flag=0;
        }
        if(!p){
            p=u=aux;
            u->lazo=NULL;
        }
        printf("\n¿Hay mas datos? NO=0 / SI=1");
        scanf("%d",&continuar);
        fflush(stdin);
    }while(continuar);
	
	if((fp=fopen("potencia.dat","ab"))==NULL){
        printf("\nError archivo potencia.dat");
        return 0;
    }
    while(p){
        aux=p;
        p=p->lazo;
        printf("\nDescripcion: %s",aux->datos.desc);
        printf("\nPotencia: %d",aux->datos.potencia);
        printf("\nEstado: %d",aux->datos.estado);
        bf.id=bf.id++;
        strcpy(bf.desc,aux->datos.desc);
        bf.estado=aux->datos.estado;
        bf.potencia=aux->datos.potencia;
        fwrite(&bf,sizeof(struct e),1,fp);
        free(aux);
    }
    getch();
    
    return 0;
}
