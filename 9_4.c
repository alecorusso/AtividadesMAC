#include <stdio.h>
#include <math.h>
#define MAX 1000

float distancia(float v1[], float v2[], int n){
    float soma = 0;
    for(int i = 0; i < n; i++){
        float dif = v1[i]-v2[i];
        soma += dif*dif;
    }
    return sqrt(soma);
}

void calcula_produto(float M[][MAX], float x[], float vetR[], int n){

    for(int i = 0; i < n; i++){
        float soma = 0;
        for(int j = 0; j < n; j++){
            float parcela = M[i][j]*x[j];
            soma += parcela;
        }
        vetR[i] = soma;
    }
}

void main(){
    int tamanho;
    float A[MAX][MAX], x[MAX], B[MAX], Ax[MAX];

    scanf("%d", &tamanho);

    for(int i = 0; i < tamanho; i++)
        for(int j = 0; j < tamanho; j++)
            scanf("%f", &A[i][j]);
    
    for(int i = 0; i < tamanho; i++)
        scanf("%f", &x[i]);

    for(int i = 0; i < tamanho; i++)
        scanf("%f", &B[i]);

    calcula_produto(A, x, Ax, tamanho);

    for(int i = 0; i < tamanho; i++)
        printf("%f ", Ax[i]);
    printf("\n");
    printf("%f\n", distancia(Ax, B, tamanho));

}