#include <stdio.h>

int verificarLatino(int vetor[][1000], int tamanho){
    for(int linha = 0; linha < tamanho; linha++){
        int bits[1000] = {0};
        for(int coluna = 0; coluna < tamanho; coluna++){
            bits[vetor[linha][coluna]]++;
        }
        for(int i = 0; i < tamanho; i++){
            if(bits[i] != 1){
                return -1;
            }
        }
    }

    for(int coluna = 0; coluna < tamanho; coluna++){
        int bits[1000] = {0};
        for(int linha = 0; linha < tamanho; linha++){
            bits[vetor[linha][coluna]]++;
        }
        for(int i = 0; i < tamanho; i++){
            if(bits[i] != 1){
                return -1;
            }
        }
    }

    return 1;

}


void main(){
    int n, quadrado[1000][1000];

    scanf("%d", &n);

    for(int linha = 0; linha < n; linha++){
        for(int coluna = 0; coluna < n; coluna++){
            scanf("%d", &quadrado[linha][coluna]);
        }
    }

    if(verificarLatino(quadrado, n) == 1){
        printf("SIM\n");
    } else {
        printf("NAO\n");
    }

}