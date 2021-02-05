/*
Hacer un programa que lea al archivo "contactos.dat" creado en el Ejercicio 35 y crear una lista, en memoria dinámica, ordenada alfabéticamente. Una vez creada la lista guardarla en un archivo de organización directa llamado "contactos_ordenados.dat" imprimiendola en pantalla.
*/

#include "lib.h"

int main(){
    FILE *file;
    struct lista *p=NULL, *u=NULL, *aux,*r;
    struct datos d;
    file = fopen("contactos.dat","rb");
    fread(&d,sizeof(d),1,file);
    while(!feof(file)){
        aux = (struct lista*)malloc(sizeof(struct lista));
        if(aux){
            strcpy(aux->d.nombre,d.nombre);
            printf("Variable aux: %s\n",aux->d.nombre);
            if(p==NULL){
                printf("0\n");
                p=u=aux;
                u->l=NULL;
            }
            else{
                r=p;
                while(1){
                    if(strOrden(20,r->d.nombre,aux->d.nombre)){
                        printf("%s < %s\n",r->d.nombre,aux->d.nombre);
                        printf("1\n");
                        aux->l=p;
                        p=aux;
                        break;
                    }
                    while(r->l){
                        if(!strOrden(20,r->l->d.nombre,aux->d.nombre)){
                            printf("%s < %s\n",r->l->d.nombre,aux->d.nombre);
                            r=r->l;
                            printf("2\n");
                        }
                        else {
                            printf("3\n");
                            break;
                        }
                    }
                    if(r==u){
                        u->l=aux;
                        u=aux;
                        u->l=NULL;
                        printf("4\n");
                        break;
                    }
                    else{
                        printf("5\n");
                        aux->l=r->l;
                        r->l=aux;break;
                    }
                }
            }
        } 
        fread(&d,sizeof(d),1,file);
    }
    fclose(file);
    printf("Lista ordenada?:\n");
    while(aux){
        printf("%s\n",aux->d.nombre);
        aux=aux->l;
    }
    return 0;
}
