#include <stdio.h>
#define max 1000000

void vetorizar(int vetor[], int *tamanho){
    int i = 0, a;
    for(i=0; i < max; i++){
        scanf("%d", &a);
        if (a < 0) {
            break;
        } else {
        vetor[i] = a;
        }
    }
    *tamanho = i;
}

int busca_elementos(int vetor[], int nelementos, int x){
    for (int i = 0; i < nelementos; i++){
        if (x == vetor[i]){
            return i;
        }
    }
    return -1;
}

void main(){
    int ndados, dados[max], *a = &ndados;
    int nalvos, alvos[max], *b = &nalvos;

    vetorizar(dados, a);
    vetorizar(alvos, b);

    int i, alvo;
    for(i = 0; i < nalvos; i++){
        alvo = alvos[i];
        printf("%d ", busca_elementos(dados, ndados, alvo));
    }
}
