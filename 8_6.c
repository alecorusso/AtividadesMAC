#include <stdio.h>

void main(){
    int n, quadrado[1000][1000];

    scanf("%d", &n);

    for(int linha = 0; linha < n; linha++){
        char input[1000];
        scanf("%s", input);
        int coluna = 0;
        int j = 0;
        while(coluna < n){
            char caractere = input[j];
            if ('0' <= caractere && caractere <= '9'){
                int numero = caractere - 48;
                quadrado[linha][coluna] = numero;
                coluna++;
                printf("linha %d coluna %d: %c\n", linha, coluna, caractere);
            }
            j++;
        }
        printf("linha %d: ", linha);
        for(int i = 0; i < n; i++){
            printf("%d ", quadrado[linha][i]);
        }
        printf("\n");
    }

    printf("saiu\n");
}