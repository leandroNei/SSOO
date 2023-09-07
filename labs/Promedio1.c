#include<stdio.h>
int main(void){
    float nota1;
    float nota2;
    float nota3;
    float nota4;
    float prom;
    float aux = 0;

    printf("Escriba PRIMERA nota: \n");
    scanf("%f",&nota1);
    printf("Escriba SEGUNDA nota: \n");
    scanf("%f",&nota2);
    printf("Escriba TERCERA nota: \n");
    scanf("%f",&nota3);
    printf("Escriba CUARTA nota: \n");
    scanf("%f",&nota4);

    prom = (nota1 + nota2 + nota3 + nota4)/4;
    printf("El promedio es: %f", prom);
}