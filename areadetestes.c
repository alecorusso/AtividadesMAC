#include <stdio.h>

void main(){
    int vetor[1000], n;

    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        scanf("%d", &vetor[i]);
    }

    for(int i = 0; i < n; i++){
        printf("%d", vetor[i]);
    }
}