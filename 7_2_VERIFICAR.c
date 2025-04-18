// Aproximações dando errado na soma do seno (linha 17)
// Output requerido pelo avaliador automático pede para imprimir o valor da quantidade de somas realizadas da série
// de taylor, e não o valor da variável x, contradizendo o enunciado.

#include <stdio.h>
#include <math.h>

void main(){
    int n;
    float parcela = 1.0, x = 0.0, seno;

    scanf("%d", &n);
    scanf("%f", &x);

    seno = x;

    for (int i = 1; i < n; i++){
        parcela = -parcela*x*x/((2*i)*((2*i)+1));
        seno += parcela;
    }
    
    printf("%d :  %6.3f =   %6.3f\n", n, seno, sin(x));
}