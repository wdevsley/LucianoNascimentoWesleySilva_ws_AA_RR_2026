#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para alocar matrizes dinamicamente
int** alocar(int n) {
    int** m = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) m[i] = (int*)malloc(n * sizeof(int));
    return m;
}

void liberar(int** m, int n) {
    for (int i = 0; i < n; i++) free(m[i]);
    free(m);
}

void somar(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) C[i][j] = A[i][j] + B[i][j];
}

void subtrair(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) C[i][j] = A[i][j] - B[i][j];
}

// O CORAÇÃO DO STRASSEN
void strassen(int** A, int** B, int** C, int n) {
    if (n <= 64) { // Limiar: para matrizes pequenas, o tradicional é mais rápido
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] = 0;
                for (int k = 0; k < n; k++) C[i][j] += A[i][k] * B[k][j];
            }
        }
        return;
    }

    int k = n / 2;
    int** a11 = alocar(k); int** a12 = alocar(k); int** a21 = alocar(k); int** a22 = alocar(k);
    int** b11 = alocar(k); int** b12 = alocar(k); int** b21 = alocar(k); int** b22 = alocar(k);
    int** p1 = alocar(k); int** p2 = alocar(k); int** p3 = alocar(k); int** p4 = alocar(k);
    int** p5 = alocar(k); int** p6 = alocar(k); int** p7 = alocar(k);
    int** aux1 = alocar(k); int** aux2 = alocar(k);

    // Divisão em quadrantes
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            a11[i][j] = A[i][j]; a12[i][j] = A[i][j+k];
            a21[i][j] = A[i+k][j]; a22[i][j] = A[i+k][j+k];
            b11[i][j] = B[i][j]; b12[i][j] = B[i][j+k];
            b21[i][j] = B[i+k][j]; b22[i][j] = B[i+k][j+k];
        }
    }

    // Os 7 produtos de Strassen
    somar(a11, a22, aux1, k); somar(b11, b22, aux2, k); strassen(aux1, aux2, p1, k); // p1 = (a11+a22)(b11+b22)
    somar(a21, a22, aux1, k); strassen(aux1, b11, p2, k); // p2 = (a21+a22)b11
    subtrair(b12, b22, aux2, k); strassen(a11, aux2, p3, k); // p3 = a11(b12-b22)
    subtrair(b21, b11, aux2, k); strassen(a22, aux2, p4, k); // p4 = a22(b21-b11)
    somar(a11, a12, aux1, k); strassen(aux1, b22, p5, k); // p5 = (a11+a12)b22
    subtrair(a21, a11, aux1, k); somar(b11, b12, aux2, k); strassen(aux1, aux2, p6, k); // p6 = (a21-a11)(b11+b12)
    subtrair(a12, a22, aux1, k); somar(b21, b22, aux2, k); strassen(aux1, aux2, p7, k); // p7 = (a12-a22)(b21+b22)

    // Unindo os resultados em C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = p1[i][j] + p4[i][j] - p5[i][j] + p7[i][j];
            C[i][j+k] = p3[i][j] + p5[i][j];
            C[i+k][j] = p2[i][j] + p4[i][j];
            C[i+k][j+k] = p1[i][j] - p2[i][j] + p3[i][j] + p6[i][j];
        }
    }

    // Liberação de memória (MUITO importante para n=10000)
    liberar(a11, k); liberar(a12, k); liberar(a21, k); liberar(a22, k);
    liberar(b11, k); liberar(b12, k); liberar(b21, k); liberar(b22, k);
    liberar(p1, k); liberar(p2, k); liberar(p3, k); liberar(p4, k);
    liberar(p5, k); liberar(p6, k); liberar(p7, k);
    liberar(aux1, k); liberar(aux2, k);
}

int main() {
    int tamanhos[] = {100, 200, 400, 1000, 10000};
    for(int i = 0; i < 5; i++) {
        int n = tamanhos[i];
        // O Strassen padrão precisa de n como potência de 2. 
        // Para simplificar seu teste, vamos usar n direto.
        int** A = alocar(n); int** B = alocar(n); int** C = alocar(n);
        
        printf("Rodando Strassen para n = %d...\n", n);
        clock_t start = clock();
        strassen(A, B, C, n);
        clock_t end = clock();
        
        printf("Tempo: %.4f segundos\n\n", (double)(end - start) / CLOCKS_PER_SEC);
        liberar(A, n); liberar(B, n); liberar(C, n);
    }
    return 0;
}
