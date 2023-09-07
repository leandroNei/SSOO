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

    prom = nota1*0.4 + nota2*0.3 + nota3*0.3;
    printf("El promedio es: %f", prom);
}