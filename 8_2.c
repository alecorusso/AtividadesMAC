#include <stdio.h>
#define MAX 256

int teste_anagrama(char vetor1[], char vetor2[], int tamanho1, int tamanho2){
    if(tamanho1 != tamanho2){
        return -1;
    }

    int vetor[MAX] = {0};

    for(int i = 0; i < tamanho1; i++){
        int p = vetor1[i];
        int l = vetor2[i];
        vetor[p]++;
        vetor[l]--;
    }

    for(int i = 0; i < MAX; i++){
        if(vetor[i] != 0){
            return -1;
        }
    }

    return 1;
}

void main(){
    char palavra1[MAX], palavra2[MAX];
    int npalavra1 = 0, npalavra2 = 0;

    scanf("%s", palavra1);
    for(int i = 0; palavra1[i] != '\0'; i++){
        if(64 < palavra1[i] && palavra1[i] < 91){
            palavra1[i] += 32;
        }
        npalavra1++;
    }
    
    scanf("%s", palavra2);
    for(int i = 0; palavra2[i] != '\0'; i++){
        if(64 < palavra2[i] && palavra2[i] < 91){
            palavra2[i] += 32;
        }
        npalavra2++;
    }


    if(teste_anagrama(palavra1, palavra2, npalavra1, npalavra2) == 1){
        printf("ANAGRAMAS\n");
    } else {
        printf("NAO\n");
    }
}