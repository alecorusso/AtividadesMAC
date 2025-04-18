//Teste 2 dando errado no avaliador automatico e dando certo no GCC com o WSL

#include <stdio.h>
#include <string.h>
#define MAX 256

long buscar_digitos(char string[], char digitos[], int tamanho, int *tamanhodigitos){
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

    *tamanhodigitos = ndigitos;

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
    char string[MAX], numeros[MAX];
    int nnumeros, *appontnnumeros = &nnumeros;

    scanf("%s", string);

    printf("%ld\n", buscar_digitos(string, numeros, strlen(string), appontnnumeros));
    for(int i = 0; i < nnumeros; i++){
        int a = numeros[i];
        printf("%c :: %d\n", numeros[i], a);
    }
}