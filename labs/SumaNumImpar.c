#include<stdio.h>
int main(void){
   int num0 = 1;
   int num1 = 2;
   int res = 0;
   int aux = 0;

   while(aux < 100)
   {
        res = num0+num1;
        printf("El resultado es: %i\n", res);
        aux=aux+3;
   }
}
