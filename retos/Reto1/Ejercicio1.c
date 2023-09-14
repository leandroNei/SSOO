/*Realizar un algoritmo que permita inicializar 5 nombres en Arrays. Utilizar ciclos para la
impresión de los nombres.*/
#include<stdio.h>
#include<string.h>

int main()
{
    char Nombres[5][20]={"leandro","roc3l","Piter","joseluiiiis","happy"};
    int aux = 0;
    //muestra los nombres del arreglo
    while (aux<5)
    {
        printf("%s \n", Nombres[aux]);
        aux++;
    }
    
    return 0;
}