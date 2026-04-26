#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para alocar matriz dinamicamente
double** alocar_matriz(int n) {
    double **matriz = (double**) malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matriz[i] = (double*) malloc(n * sizeof(double));
    }
    return matriz;
}

// Função para liberar a memória da matriz
void liberar_matriz(double **matriz, int n) {
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

// Algoritmo Tradicional de Multiplicação de Matrizes: O(n^3)
void multiplicar_matrizes(int n, double **A, double **B, double **C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0; // Inicializa a posição
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    // Diferentes tamanhos de entrada para experimentação
    int tamanhos[] = {100, 200, 400, 1000, 5000};
    int num_experimentos = 5;

    printf("Resultados da Multiplicacao de Matrizes O(n^3):\n");
    printf("------------------------------------------------\n");
    printf("Tamanho (n x n)\t| Tempo de Execucao (segundos)\n");
    printf("------------------------------------------------\n");

    for (int e = 0; e < num_experimentos; e++) {
        int n = tamanhos[e];

        double **A = alocar_matriz(n);
        double **B = alocar_matriz(n);
        double **C = alocar_matriz(n);

        // Preenchendo as matrizes com valores arbitrários
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = (double)(rand() % 100) / 10.0;
                B[i][j] = (double)(rand() % 100) / 10.0;
            }
        }

        // Inicia a contagem do tempo
        clock_t inicio = clock();
        
        multiplicar_matrizes(n, A, B, C);
        
        // Finaliza a contagem do tempo
        clock_t fim = clock();
        double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

        printf("%d x %d\t\t| %f\n", n, n, tempo_gasto);

        liberar_matriz(A, n);
        liberar_matriz(B, n);
        liberar_matriz(C, n);
    }

    return 0;
}