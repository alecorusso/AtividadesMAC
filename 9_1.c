#include <stdio.h>
#define MAX 1000

void main(){
    int m, n;
    float matriz[MAX][MAX];

    scanf("%d %d", &m, &n);

    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            scanf("%f", &matriz[i][j]); 

    for(int i = 0; i < m; i++){
        float soma = 0;
        for(int j = 0; j < n; j++){
            printf("%5.1f ", matriz[i][j]);
            soma += matriz[i][j];
        }
        printf("= %5.1f\n", soma);
    }
    
}