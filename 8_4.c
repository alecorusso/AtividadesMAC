#include <stdio.h>

long buscar_digitos(char string[], int tamanho){
    char digitos[1000];
    int ndigitos = 0;
    long representante = 0, parcela = 1;
    
    for (int i = 0; i < tamanho; i++){
        if('0' <= string[i] && string[i] <= '9'){
            digitos[ndigitos] = string[i];
            ndigitos++;
        }
    }

    if (ndigitos == 0){
        return 0;
    }

    int aux = digitos[ndigitos-1] - 48, multiplicador = 1;
    representante = aux;
    for (int i = 1; i < ndigitos; i++){
        aux = digitos[(ndigitos-1)-i] - 48;
        multiplicador = multiplicador*10;
        parcela = aux*multiplicador;
        representante += parcela;
    }

    return representante;
}

void main(){
    char string[1000];
    long n, representantes[1000], soma = 0;

    scanf("%ld", &n);

    for(int i = 0; i < n; i++){
        scanf("%s", string);
        int tamanho = 0;
        char caractere = 'a';
        for(int j = 0; caractere != '\0'; j++){
            caractere = string[j];
            if (caractere != '\0'){
                tamanho++;
            }
        }
        representantes[i] = buscar_digitos(string, tamanho);
        soma += buscar_digitos(string, tamanho);
    }

    printf("%ld ", soma);
    for(int i = 0; i < n; i++){
        printf("%ld ", representantes[i]);
    }
    printf("\n");
}