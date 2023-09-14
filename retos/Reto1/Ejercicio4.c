/*Realizar un programa que solicité por teclado los valores de dos matrices de 2x2, y mostrar
el resultado de la suma de las dos matrices por pantalla.*/
#include<stdio.h>

int main(){
    int matriz1[2][2];
    int matriz2[2][2];
    int matriz3[2][2];
    int i;
    int j;
    //ingresa Valores primera matriz
    printf("Ingrese valores 4 para la PRIMERA matriz 2x2\n");
    for(i=0; i<=1; i++)
    {
        for (j=0; j<=1; j++)
        {
            printf("Ingrese: ");
            scanf("%d",&matriz1[i][j]);
        }
    }
    //muestra valores primera matriz
    for(i=0; i<=1; i++)
    {
        printf("\n");
        for (j=0; j<=1; j++)
        {
            printf(" [%d] ", matriz1[i][j]);
        }
    }
    //ingresa valores a las segunda matriz
    printf("\nIngrese valores 4 para la SEGUNDA matriz 2x2\n");
    for(i=0; i<=1; i++)
    {
        for (j=0; j<=1; j++)
        {
            printf("Ingrese: ");
            scanf("%d",&matriz2[i][j]);
        }
    }
    //muestra segunda matriz
    for(i=0; i<=1; i++)
    {
        printf("\n");
        for (j=0; j<=1; j++)
        {
            printf(" [%d] ", matriz2[i][j]);
        }
    }
    //suma posicion por posicion los valores
    printf("Suma de las matrices: ");
    for(i=0; i<=1; i++)
    {
        printf("\n");
        for (j=0; j<=1; j++)
        {
            matriz3[i][j]=matriz1[i][j]+matriz2[i][j];
        }
    }
    //muestra la nueva matriz
    for(i=0; i<=1; i++)
    {
        printf("\n");
        for (j=0; j<=1; j++)
        {
            printf(" [%d] ", matriz3[i][j]);
        }
    }

}