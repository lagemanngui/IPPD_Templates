#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 
 * Printa a matriz mat de tamanho m x m
 * 
 **/
void printMatrix(int **mat, int m, char msg[256]);
int **reduzir(int **mat, int m, int iteracao);

int **matriz;
int main() {

    //Tamanho da matrix m*m
    int m = 8, i = 0, j = 0;

    //Aloca espaço para as colunas
    matriz = calloc(m, sizeof(int *));

    //Aloca espaço para as linhas
    for(i=0; i<m; i++) 
        matriz[i] = calloc(m, sizeof(int));

    printMatrix(matriz, m, "Matriz alocada");
    

    int acc = 1;
    for(i = 0; i<m; i++) {
        for(j=0; j<m; j++) {
            matriz[i][j] = acc;
            acc++;
        }
    }

    printMatrix(matriz, m, "Matriz preenchida");

    int reduzir_para = m;

    reduzir(matriz, m, 0);


}

int** reduzir(int **mat, int m, int iteracao) {

    int **m1, **m2, **m3, **m4;
    int i=0;
    int j=0;

    int acc1 = 0, acc2 = 0, acc3 = 0, acc4 = 0;

    //Aloca espaço para as colunas
    m1 = calloc(m/2, sizeof(int *));
    m2 = calloc(m/2, sizeof(int *));
    m3 = calloc(m/2, sizeof(int *));
    m4 = calloc(m/2, sizeof(int *));


    //Aloca espaço para as linhas
    for(i=0; i<m/2; i++) 
    {
        m1[i] = calloc(m/2, sizeof(int));
        m2[i] = calloc(m/2, sizeof(int));
        m3[i] = calloc(m/2, sizeof(int));
        m4[i] = calloc(m/2, sizeof(int));

    }    

    printf("ITERACAO: %d....m = %d\n", iteracao, m);


    if(m > 2) {

        int reduzir_para = m/2;
        int base_i = 0;
        int base_j = 0;


        //Primeira redução
        for(i = 0; i < reduzir_para; i++) {
            for(j = 0; j < reduzir_para; j++) {
                m1[base_i][base_j] = mat[i][j];
                base_j++;
            }
            base_i++;
            base_j = 0;
        }

        base_i = 0;
        base_j = 0;

        //Segunda redução
        for(i = 0; i < reduzir_para; i++) {
            for(j = reduzir_para; j < m; j++) {
                m2[base_i][base_j] = mat[i][j];
                base_j++;
            }
            base_i++;
            base_j=0;

        }

        base_i = 0;
        base_j = 0;

        //Terceira redução
        for(i = reduzir_para; i < m; i++) {
            for(j = 0; j < reduzir_para; j++) {
                m3[base_i][base_j] = mat[i][j];
                base_j++;
            }
            base_i++;
            base_j = 0;

        }

        base_i = 0;
        base_j = 0;

        //Quarta redução
        for(i = reduzir_para; i < m; i++) {
            for(j = reduzir_para; j < m; j++) {
                m4[base_i][base_j] = mat[i][j];
                base_j++;
            }
            base_i++;
            base_j = 0;

        }

        base_i = 0;
        base_j = 0;

        printMatrix(m1, m/2, "Matriz 1");
        printMatrix(m2, m/2, "Matriz 2");
        printMatrix(m3, m/2, "Matriz 3");
        printMatrix(m4, m/2, "Matriz 4");

        if(reduzir_para > 2) {
            m1 = reduzir(m1, reduzir_para, iteracao+1);
            m2 = reduzir(m2, reduzir_para, iteracao+1);
            m3 = reduzir(m3, reduzir_para, iteracao+1);
            m4 = reduzir(m4, reduzir_para, iteracao+1);

        }

        for(i = 0; i < 2; i++) {
            for(j = 0; j < 2; j++) {
                acc1 += m1[i][j];
                acc2 += m2[i][j];
                acc3 += m3[i][j];
                acc4 += m4[i][j];
            }
        }
    }

    int **matriz_final;
    matriz_final = calloc(2, sizeof(int *));
    for(i = 0; i < 2; i++) matriz_final[i] = calloc(2, sizeof(int));

    matriz_final[0][0] = acc1/4;
    matriz_final[0][1] = acc2/4;
    matriz_final[1][0] = acc3/4;
    matriz_final[1][1] = acc4/4;

    printMatrix(matriz_final, 2, "Média");

    
    return matriz_final;
}

void printMatrix(int **mat, int m, char msg[256]) {
    int i = 0;
    int j = 0;

    printf("%s:\n", msg);
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < m; j++) 
        {
            printf("[%d]", mat[i][j]);

        }
        
        printf("\n");
    }
    printf("\n");
        
}
