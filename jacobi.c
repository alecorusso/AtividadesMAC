#include <stdio.h>
#include <math.h>

void main(){
    int matriz_estendida_inicial[100][100], linhas, colunas, expoente, cont = 0;
    double x0, y0, epislon, dist,  matriz_iterativa[100], chutes_iniciais[100];

    double x0_verdadeiro = 54.0/29, y0_verdadeiro = 53.0/29, absx, absy;     //variáveis criadas apenas para o propósito da atividade

    printf("Digite o número de linhas da matriz estendida do sistema linear: ");
    scanf("%d", &linhas);
    printf("Digite o número de colunas da matriz estendida do sistema linear: ");
    scanf("%d", &colunas);
    
    printf("Digite em ordem respectiva de coluna e linha os elementos da matriz estendida do sistema linear: \n");
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            scanf("%d", &matriz_estendida_inicial[i][j]);
        }
    }

    printf("Digite o expoente da ordem de grandeza da tolerância do método em base decimal: ");
    scanf("%d", &expoente);
    epislon = pow(10, expoente);

    printf("Digite os chute iniciais para as incógnitas do sistema linear: ");
    for(int i = 0; i < linhas; i++){
        scanf("%lf", &chutes_iniciais[i]);
        matriz_iterativa[i] = chutes_iniciais[i];
    }

    absx = chutes_iniciais[0] - x0_verdadeiro;
    absy = chutes_iniciais[1] - y0_verdadeiro;

    printf("%d %f %f --- %f %f\n", cont, chutes_iniciais[0], chutes_iniciais[1], absx, absy);

    chutes_iniciais[0] = (13 - matriz_iterativa[1])/6.0;
    chutes_iniciais[1] = (11 - matriz_iterativa[0])/5.0;

    int sum = 0;
    for(int i = 0; i < linhas; i++){
        sum += pow(chutes_iniciais[i] - matriz_iterativa[i], 2);
    }
    dist = pow(sum, 0.5);
    cont++;
    while(dist > epislon && cont <= 15){
        printf("%d %f %f %f %f %f\n", cont, chutes_iniciais[0], chutes_iniciais[1], dist, absx, absy);
        for(int i = 0; i < linhas; i++){
            matriz_iterativa[i] = chutes_iniciais[i];
        }
        chutes_iniciais[0] = (13 - matriz_iterativa[1])/6.0;
        chutes_iniciais[1] = (11 - matriz_iterativa[0])/5.0;
        float newsum;
        for(int i = 0; i < linhas; i++){
            newsum += pow(chutes_iniciais[i] - matriz_iterativa[i], 2);
        }
        dist = pow(newsum, 0.5);
        absx = chutes_iniciais[0] - x0_verdadeiro;
        absy = chutes_iniciais[1] - y0_verdadeiro;
        cont++;
    }



}