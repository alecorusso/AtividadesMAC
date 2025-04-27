#include <stdio.h>
#define MAX 1000

float func_media(float vet[], int n){
    float soma = 0;
    for(int i = 0; i < n; i++){
        soma += vet[i];
    }
    float media = soma/n;
    return media;
}

void main(){
    int linhas, colunas, linhaalvo;
    float matriz[MAX][MAX], vetor[MAX];

    scanf("%d %d", &linhas, &colunas);

    for(int i = 0; i < linhas; i++)
        for(int j = 0; j < colunas; j++)
            scanf("%f", &matriz[i][j]);

    scanf("%d", &linhaalvo);

    printf("%.1f\n", func_media(matriz[linhaalvo], colunas));
    
}