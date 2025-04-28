// Aproximações dando errado na soma do seno (linha 17)

#include <stdio.h>
#include <math.h>

void main(){
    int n;
    float parcela = 1.0, x = 0.0, seno;

    scanf("%d", &n);
    scanf("%f", &x);

    seno = x;
    parcela = x;

    printf("Parcela 1: %6.3f\n", parcela);
    printf("Seno 1: %6.3f\n", seno);
    
    for (int i = 1; i < n; i++){
        parcela = -parcela*x*x/((2*i)*((2*i)+1));
        seno += parcela;
        printf("Parcela %d: %6.3f\n", i+1, parcela);
        printf("Seno %d: %6.3f\n", i+1, seno);
    }
    
    printf("%1.1f :  %6.3f =   %6.3f\n", x, seno, sin(x));
}