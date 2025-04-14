#include <stdio.h>
#define max 40

void vetorizar(int vetor[], int tamanho){
    for(int i = 0; i < tamanho; i++){
        scanf("%d", &vetor[i]);
    }
    printf("\n");
}

void printvetor(int vetor[], int tamanho){
    int i = 0;
    for(i=0; i < tamanho; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int determineIndiceDoMenor(int vetor[], int inicial, int tamanho){
    int menor = inicial;
    for(int i = inicial; i < tamanho; i++){
        if(vetor[i] < vetor[menor]){
            menor = i;
        }
    }
    return menor;
}

void main(){
    int dados[max], ndados;

    scanf("%d", &ndados);

    vetorizar(dados, ndados);

    for(int i = 0; i<ndados-1; i++){
        int indice = determineIndiceDoMenor(dados, i, ndados);
        printf("%d %d\n", indice, dados[indice]);
        int aux = dados[i];
        dados[i] = dados[indice];
        dados[indice] = aux;
    }

    printvetor(dados, ndados);
}

