#include <stdio.h>

void main(){
    int n, vetor[1000];
    
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        scanf("%d", &vetor[i]);
    }

    for(int i = n-1; i >= 0; i--){
        printf("%d ", vetor[i]);
    }
    printf("\n");
}