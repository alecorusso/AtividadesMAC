#include <stdio.h>

int buscaBinária(int vt_inicial[], int num , int tam) {
    if(num == 0){
        return -1;
    }
    int inferior = 0;
    int superior = tam - 1;
    while (inferior <= superior){
        printf("%d %d\n", inferior, superior);
        int meio = (inferior + superior) / 2;
        if (num  == vt_inicial[meio]) {
            return meio;
        }

        if (num < vt_inicial[meio]) {
            superior = meio-1;
        }

        else {
            inferior = meio+1;
        }

    }
    return -1;
}


int main () {

    int vt_incial[100];
    int vt_final[100];
    int tam_incial = 0;
    int tam_final = 0;
    int x = 0;
    int j = 0;
    int i = 0;
    int k = 0;
    int buscado = 0;

    scanf("%d", &x);
    while (x >= 0) {
        vt_incial[tam_incial] = x;
        tam_incial++;
        scanf("%d", &x);

    }

    /*for ( i = 0; i < tam_incial; i++) {
        printf("%d\n", vt_incial[i]);
    }*/

    scanf("%d", &j);
    while ( j >= 0) {
        vt_final[tam_final] = j;
        tam_final++;
        scanf("%d", &j);
    }

    /*for ( i = 0; i < tam_final; i++) {
        printf("%d\n", vt_final[i]);
    }*/

    if (tam_final != 0){
        for (i = 0; i < tam_final; i++) {
            buscado = vt_final[i];
            printf("%d\n", buscaBinária(vt_incial, buscado, tam_incial));
        }
    }

    return 0;
}