/*Tomando el algoritmo anterior, solicitar los 5 nombres por consola, y almacenarlos en
Arrays. Luego mostrar los nombres guardados.*/

#include<stdio.h>
#include<string.h>

int main()
{
    char Nombres[5][20];
    int aux=0;
     
    for (int i=0;i<5;i++)
    {
        printf("Ingrese nombre: ");
        scanf("%s", &Nombres[i]);
    }

    while (aux<5)
    {
        printf("%s \n", Nombres[aux]);
        aux++;
    }

    return 0;
}
