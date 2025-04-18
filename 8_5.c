#include <stdio.h>

void main(){
    int n, inteiro, bits[1000] = {0};

    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        scanf("%d", &inteiro);
        bits[inteiro] = 1;
    }

    int indice = 0;
    while(bits[indice] == 1 && indice < n){
    indice++;
    }

    if(indice == n){
        printf("SIM\n");
    } else {
        printf("NAO\n");
    }
}