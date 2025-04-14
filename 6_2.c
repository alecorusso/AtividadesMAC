#include <stdio.h>
#define max 1000000

void vetorizar(int vetor[], int *tamanho){
    int i= 0, a = 0;
    while(a >= 0){
        scanf("%d", &a);
        if (a >= 0){
        vetor[i] = a;
        i++;
        }
    }
    *tamanho = i;
}

int busca_binaria(int vetor[], int nelementos, int alvo){
    if(nelementos == 0){
        return -1;
    }
    int inf = 0, sup = nelementos-1;
    while (inf <= sup){
        printf("%d %d\n", inf, sup);
        int med = (inf+sup)/2;
        if(alvo < vetor[med]){
            sup = med - 1;
        } else if (alvo > vetor[med]) {
            inf = med + 1;
        } else {
            return med;
        }  
    }
    return -1;
}

void main(){
    int ndados, dados[max], *a = &ndados, alvo = 0;

    vetorizar(dados, a);

    while(alvo >= 0){
        scanf("%d", &alvo);
        if(alvo >= 0){
            printf("%d\n", busca_binaria(dados, ndados, alvo));
        }
    }
}