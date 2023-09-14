/*Desarrollar un programa que sea capaz de crear una matriz 3x3 de solo números enteros y
mostrar la matriz por consola.*/
#include<stdio.h>

int main(){
    int matriz[3][3]={1,2,3,4,5,6,7,8,9};
    int i;
    int j;
    //muestra valores de la matriz
    for(i=0; i<=2; i++)
    {
        printf("\n");
        for (j=0; j<=2; j++)
        {
            printf(" [%d] ", matriz[i][j]);
        }
    }
}