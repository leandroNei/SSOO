#include<stdio.h>
int main(){
   int num0 = 1;
   int res = 0;
   int aux = 1;

   while(aux < 99)
   {
      num0=num0+2;
      res=num0;
      res=res+res;
      printf("El resultado es: %d \n", res);

   }

}
