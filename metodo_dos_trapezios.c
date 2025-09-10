//Boa sorte :)

#include <stdio.h>
#include <math.h>
#define MAX 10000

int main()
{
    int n = 0;
    double xinicio = -1, xfinal = -1, h;
    double pontosx[MAX], pontosy[MAX];
    double realintegral = exp(1) - 1;
    double integralaprox = 0;
    printf("Aproxime a integral da função e^(x) no intervalo [0, 1]!\n");
    printf("Digite a quantidade de pontos da função: ");
    scanf("%d", &n);
   
    while((xinicio < 0) || (xinicio > 1)){
        printf("Digite o primeiro ponto: ");
        scanf("%lf", &xinicio);
    }
   
    while((xfinal < 0) || (xfinal > 1)){
        printf("Digite o último ponto: ");
        scanf("%lf", &xfinal);
    }
   
    h = (xfinal-xinicio)/(n-1);
   
    for(int i = 0; i < n-1; i++){
        pontosx[i] = xinicio + i*h;
    }
    
    pontosx[n-1] = xfinal;
   
    for(int i = 0; i < n; i++){
        pontosy[i] = exp(pontosx[i]);
    }
    
   
    integralaprox = (pontosy[0]+pontosy[n-1])/2;
    
   
    for(int i=1; i < n-1; i++){
        integralaprox += pontosy[i];
    }
   
    integralaprox *= h;
   
    printf("O valor calculado para os seus pontos é: %lf\n", integralaprox);
    printf("O valor real é: %lf\n", realintegral);
    printf("O erro é: %lf\n", integralaprox-realintegral);
   

    return 0;
}
