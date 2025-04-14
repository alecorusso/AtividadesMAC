#include <stdio.h>
#include <math.h>

float dist_euclidiana(int tamanho, float v1[], float v2[]){
    float soma = 0;
    for(int i = 0; i < tamanho; i++){
        float aux = (v1[i]-v2[i]);
        soma += aux*aux;
    }
    return sqrt(soma);
}

void main(){
    int n;
    float vetor1[1000], vetor2[1000];

    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        scanf("%f", &vetor1[i]);
    }

    for(int i = 0; i < n; i++){
        scanf("%f", &vetor2[i]);
    }

    printf("%10.5f\n", dist_euclidiana(n, vetor1, vetor2));
}