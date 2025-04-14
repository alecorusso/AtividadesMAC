#include <stdio.h>
#include <math.h>

void main(){
    int n;
    float parcela = 1.0, x = 0.0, seno;

    scanf("%d", &n);
    scanf("%f", &x);

    seno = x;

    for (int i = 1; i <= n; i++){
        parcela = -parcela*x*x/((2*i)*((2*i)+1));
        seno += parcela;
    }
    
    printf("%6.3f\n", seno);
    printf("%6.3f\n", sin(x));
}