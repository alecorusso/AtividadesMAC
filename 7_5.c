#include <stdio.h>

int determineSeOrdenado(int tamanho, int vetor[]){
    int quebras = 0;
    for(int i = 1; i < tamanho; i++){
        if(vetor[i-1] > vetor[i]){
            quebras++;
        }
    }
    return quebras;
}

void main(){
    int n, v[40];

    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }

    if(determineSeOrdenado(n, v) == 0){
        printf("sim\n");
    } else {
    printf("não %d\n", determineSeOrdenado(n, v));
    }

}