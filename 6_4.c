#include <stdio.h>
#define max 1000

void printvetor(int vetor[], int tamanho){
    for(int i = 0; i < tamanho; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void vetorizar(int vetor[], int tamanho){
    for(int i = 0; i < tamanho; i++){
        scanf("%d", &vetor[i]);
    }
}
    
int ordenar_eficiente(int v1[], int v2[], int v0[], int n){
    int i1 = 0, i2 = 0;
    for(int i = 0; i < 2*n; i++){
        if(i1 < n && i2 < n){
            if(v1[i1] <= v2[i2]){
                v0[i] = v1[i1];
                i1++;
            } else {
                v0[i] = v2[i2];
                i2++;
            }
        }
        else if (i1 < n && i2 >= n){
            v0[i] = v1[i1];
            i1++;
        } else {
            v0[i] = v2[i2];
            i2++;
        }
    }
    return 2*n;
}
    
void main(){
    int vetor1[max], vetor2[max], tam, fusao[max];
    scanf("%d", &tam);
    vetorizar(vetor1, tam);
    vetorizar(vetor2, tam);
    ordenar_eficiente(vetor1, vetor2, fusao, tam);
    printvetor(fusao, 2*tam);  
}