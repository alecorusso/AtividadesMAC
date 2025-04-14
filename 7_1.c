#include <stdio.h>

void main(){
    int n;
    double parcela = 1.0, cosseno = 1.0, x = 0.0;

    scanf("%d", &n);
    scanf("%lf", &x);

    for (int i = 1; i <= n; i++){
        parcela = -parcela*x*x/((2*i)*((2*i)-1));
        cosseno += parcela;
    }
    printf("%lf\n", cosseno);
}