/* Universidade Presbiteriana Mackenzie
 * Ciencia da Computacao 4G - Matutino
 * Trabalho de Analise Numérica II - Paulino 
 * Yuri Serrano  TIA: 41414349
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//Uso para o tipo bool
#include <stdbool.h>

double f(double t, double y, int *eq, bool real);


int main(int argc, char *argv[])
{
  //Variaveis
  double a,b,alfa,N; 
  double h = 0.2; // dado do exercicio
  //Iterações para eq = 0,1: 
  //Sendo: 0 == a), 1 == b)...
   int i,eq;
  //Faz uma iteração com real outra com derivada
   int j;

  double t[5] = {0};         
  double w[5] = {0};
  //Calculo da parte real
  bool real = false;  

  //Runge - Kutta;
  double k1,k2,k3,k4;
  
  for(eq = 0; eq <= 3; eq++){
     
     if(eq == 0){
        a = 0; b = 1; alfa = 0;
     }
     else if(eq == 1){
        a = 2; b = 3; alfa = 1;    
     }
     else if(eq == 2){
        a = 1; b = 2; alfa = 2;
     }
     else if(eq == 3){
        a = 0; b = 1; alfa = 1;
     }                      
   //N é o mesmo para todos as equaçõess 
    N = (b - a)/h;  
    printf("N: %f",N);   
    real = false;
    
      for(j = 0; j <= 1; j++){
         w[0] = alfa;
         t[0] = a;
         if(j == 1)
         printf("\n\nf(x)\n");
         else
             printf("\n\nf'(x)\n");
             
         for(i = 1; i <= 3; i++){
            k1 = h*f(t[i - 1],w[i - 1],&eq,real);
            k2 = h*f(t[i - 1] + h/2.0,w[i - 1] + k1/2.0,&eq,real);
            k3 = h*f(t[i - 1] + h/2.0,w[i - 1] + k2/2.0,&eq,real);
            k4 = h*f(t[i - 1] ,w[i - 1] + k3,&eq,real);
            w[i] = w[i - 1] + (k1+2.0*k2+ 2.0*k3+ k4)/6.0;
            t[i] = a + i*h;
            printf("\nt: %f, w: %f",t[i],w[i]);
          
         }       
         for( ;i<=N; i++){
            t[i] = a + i*h;
            //Prediz wi
            w[i] = w[3] + h*(55*f(t[3],w[3],&eq,real) - 59*f(t[2],w[2],&eq,real) + 37*f(t[1],w[1],&eq,real) - 9*f(t[0],w[0],&eq,real))/24.0;
            //Corrige wi
            w[i] = w[3] + h*(9*f(t[i],w[i],&eq,real) + 19*f(t[3],w[3],&eq,real) - 5*f(t[2],w[2],&eq,real) + f(t[1],w[1],&eq,real))/24.0;
            printf("\nt: %f, w: %f",t[i],w[i]);
         }
         real = true;
      }
  printf("\n");
  system("PAUSE");	
  }
  return 0;
}

double f(double t, double y, int *eq, bool real){
       //a)
       if((*eq == 0) && (real == false))
          return(t*exp(3.0*t) - 2.0*y);       
       else if((*eq == 0) && (real == true))
               return(1.0/5.0*t*exp(3.0*t) - 1.0/25.0*exp(3.0*t) + 1.0/25.0*exp(-2*t));
       //b)
       else if((*eq == 1) && (real == false))
              return(1 + pow((t - y),2));
       else if((*eq == 1) && (real == true))
              return(t + 1.0/(1.0 - t));
       //c)
       else if((*eq == 2) && (real == false))
              return(1 + (y/t));
       else if((*eq == 2) && (real == true))
              return(t*log(t) + 2.0*t);             
       //d)
       else if((*eq == 3) && (real == false))
               return(cos(2.0*t) + sin(3.0*t));
       else if((*eq == 3) && (real == true))
              return(0.5*sin(2.0*t) - 1.0/3.0*cos(3.0*t) + 4.0/3.0);              
}
