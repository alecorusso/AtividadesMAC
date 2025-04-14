#include <stdio.h>

int determineSeOrdenado(int tamanho, int vetor[]){
    for(int i = 1; i < tamanho; i++){
        if(vetor[i-1] > vetor[i]){
            return 0;
        }
    }
    return 1;
}

void main(){
    int n, v[40];

    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }

    printf("%d\n", determineSeOrdenado(n, v));

}