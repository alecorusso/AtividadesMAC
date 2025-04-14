#include <stdio.h>
#define MAX 256

int verificar(char b){
    int a = b;
    if ((64 < a) && (a < 91)){
        return 2;
    } else if ((96 < a) && (a < 123)){
        return 1;
    } else {
        return -1;
    }
}

void main(){
    int tamanho = 0;
    char caractere, string[MAX];

    for(int i = 0; caractere != '0'; i++){
            scanf(" %c", &caractere);
            if (caractere != '0'){
                string[i] = caractere;
                tamanho++;
            }
    }

    for(int i = 0; i < tamanho; i++){
        printf("%d ", verificar(string[i]));
    }
    printf("\n");

}