/* Utilizando el archivo “potencia.dat” creado en el Ejercicio 39, realizar una función que pase como parámetro, entre otros datos, la clave del registro (id).
La función ubicará el registro correspondiente al id pasado como parámetro, y utilizando punteros imprimirá la primera palabra del campo "desc" en forma inversa, además cambiará el estado del bit 3 para luego actualizar el archivo. Además, se agregará a una pila la potencia cuando los bits 0 y 2, del campo estado, estén encendidos, en caso contrario se agregará el registro al archivo “salida.dat” de organización secuencial.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct e{
    int id;
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
};

struct pila{
    unsigned char potencia;
    struct pila *lazo;
};

struct pila * funcion(int id, struct pila*p);

int main()
{
    char continuar;
    int id;
    struct pila *p,*aux;
    p=NULL;

    fflush(stdin);

    do{
        printf("\nIngresar registro: ");
        scanf("%d",&id);
        fflush(stdin);
        p=funcion(id,p);
        printf("\n¿Hay otro registro? NO (0) / SI (1)");
        scanf("%d",&continuar);
        fflush(stdin);
    }while(continuar);
    return 0;
}

struct pila * funcion (int id,struct pila* p){
    FILE *fp;
    struct e bf;
    char *s, *i, *z,aux[60];

    if(!(fp=fopen("potencia.dat","rb+"))){
        printf("\nError con el archivo potencia.dat");
        return 0;
    }

    fseek(fp,(1L)*sizeof(struct e)*(id-1),0);
    fread(&bf,sizeof(struct e),1,fp);
    if(bf.id==id){
        s=&bf.desc[0];
        i=aux;
        while(*s != ' ')s++;
        z=s;
        s--;
        while(s != &bf.desc[0]){
            *i=*s;
            s--;
            i++;
        }
        *i=*s;
        i++;
        *i=0;
        
        strcpy(bf.desc,strcat(aux,z)); 
        bf.estado=(bf.estado^8);

        fseek(fp,(1L)*sizeof(struct e)*(id-1),0);
        fwrite(&bf,sizeof(struct e),1,fp);
        fclose(fp);
    }
    else{
        printf("\nNo se encontro la clave");
        getch();
        return p;
    }

    if(bf.estado&(1<<2) && bf.estado&1){
        struct pila *aux;
        aux=(struct pila*)malloc(sizeof(struct pila));
        aux->potencia=bf.potencia;
        aux->lazo=p;
        p=aux;
    }
    else{
        if(!(fp=fopen("salida.dat","ab"))){
            printf("\nNo se pudo crear el archivo salida.dat");
            return p;
        }
        fwrite(&bf,sizeof(struct e),1,fp);
        fclose(fp);
    }

    return p;
};
