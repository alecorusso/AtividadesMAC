#include <stdio.h>

int conjunto_representantes(int tamanho, int vetor[], int conjunto[], int *soma){
    conjunto[0] = vetor[0];
    int tamanho_conjunto = 1;

    for (int i = 1; i < tamanho; i++){
        int j = 0;
        while (conjunto[j] != vetor[i] && j < tamanho_conjunto){
            if (j == tamanho_conjunto-1){
                conjunto[j+1] = vetor[i];
                tamanho_conjunto++;
            }
            j++;
        }    
    }

    int s = 0;
    for(int i = 0; i < tamanho_conjunto; i++){
        s += conjunto[i];
    }
    *soma = s;

    return tamanho_conjunto;
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
    int n, v[1000], representantes[1000], sum, *appontsum = &sum;

    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }

    int tamanho_representantes = conjunto_representantes(n, v, representantes, appontsum);

    for(int i = 0; i<tamanho_representantes-1; i++){
        int indice = determineIndiceDoMenor(representantes, i, tamanho_representantes);
        int aux = representantes[i];
        representantes[i] = representantes[indice];
        representantes[indice] = aux;
    }

    printf("%d\n", tamanho_representantes);
    for(int i = 0; i < tamanho_representantes; i++){
        printf("%d ", representantes[i]);
    }
    printf("\n");
    printf("%d\n", sum);

}