/* 
Hacer un programa que tome los datos de contacto de una persona (Nombre, Apellido, edad, teléfono, mail) y los cargue, en forma directa, en una pila de memoria dinámica. Imprimir en pantalla y cargar en un archivo llamado "contactos.dat", de organización secuencial, los registros ingresados por el usuario si la persona tiene una edad mayor a 21 años. 
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(){
    struct datos{
    char nombre[20];
    char apellido[20];
    char edad;
    long tel;
    char mail[40];
};

struct pila{
    struct datos d;
    struct pila *l;
};
    struct pila *p=NULL,*aux;
    struct datos ej;
    char op = 'y';
    FILE *file;
    int i=0,c=0;
    
    do{
        c++;
        aux=(struct pila*) malloc(sizeof(struct pila));
        printf("\nNombre: ");
        gets(aux->d.nombre);
        printf("\nApellido: ");
        gets(aux->d.apellido);
        printf("\nEdad: ");
        scanf("%d",&aux->d.edad);fflush(stdin);
        printf("\nTelefono: ");
        scanf("%ld",&aux->d.tel);fflush(stdin);
        printf("\nEmail: ");
        gets(aux->d.mail);
        printf("\n");
        aux->l = p;
        p = aux;
        system("cls");
        printf("Agregar mas personas? Y/N");
        scanf("%c",&op);fflush(stdin);
        system("pause");
    }while(toupper(op) == 'Y');
    
    while(c != 0){
        c--;
        if(aux->d.edad > 21){
            printf("\nNombre: ");
            puts(aux->d.nombre);
            printf("\nApellido: ");
            puts(aux->d.apellido);
            printf("\nEdad: %d",aux->d.edad);
            printf("\nTelefono: %d",aux->d.tel);
            printf("\nEmail: ");
            puts(aux->d.mail);
            printf("\n");
            system("pause");
            strcpy(ej.nombre,aux->d.nombre);
            strcpy(ej.apellido,aux->d.apellido);
            ej.edad = aux->d.edad;
            ej.tel = aux->d.tel;
            strcpy(ej.mail,aux->d.mail);

            if(!(file = fopen("contactos.dat","ab"))){
                printf("Error abriendo el archivo\n");
            }
            fwrite(&ej,sizeof(ej),1,file);
            fclose(file);
        }
        aux=aux->l;
    }
    system("cls");
    printf("Leyendo archivo\n");
    system("pause");
    system("cls");
    if(!(file = fopen("contactos.dat","rb"))){
        printf("Error abriendo el archivo\n");
    }
    printf("Archivo abierto:\n");
    
    fread(&ej,sizeof(ej),1,file);
    while(!feof(file)){
        printf("\nNombre: %s",ej.nombre);
        printf("\nApellido: %s",ej.apellido);
        printf("\nEdad: %d",ej.edad);
        printf("\nTelefono: %d",ej.tel);
        printf("\nMail: %s",ej.mail);
        printf("\n");
        fread(&ej,sizeof(ej),1,file);
    }
    fclose(file);
    free(p);
    return 1;
}
