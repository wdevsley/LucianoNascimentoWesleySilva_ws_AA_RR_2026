# Análise de Algoritmos - Multiplicação de Matrizes

Repositório destinado ao trabalho de seminário da disciplina de Análise de Algoritmos da UFRR, ministrada pelo Prof. Dr. Herbert Oliveira Rocha.

## 🎯 Objetivos do Trabalho
- Definir a função de custo e complexidade do algoritmo tradicional.
- Implementar o código em C e realizar experimentação de tempo de execução.
- Gerar gráficos de tendência assintótica.
- Apresentar uma alternativa algorítmica mais eficiente.

## 📊 1. Função de Custo e Complexidade
O algoritmo tradicional de multiplicação de matrizes quadradas de ordem $n$ utiliza três laços de repetição aninhados.
- **Função de Custo Exata:** $T(n) = c_1n^3 + c_2n^2 + c_3n + c_4$
- **Complexidade Assintótica:** $O(n^3)$ (Melhor, Pior e Caso Médio).

## 💻 2. Código e Experimentação
O código fonte em C está localizado na pasta /src. Foram realizados testes com matrizes de tamanhos variados ($n = 100, 200, 400, 1000, 5000$) preenchidas com valores aleatórios.

**Como compilar e executar:**
```bash
gcc src/multiplicacao.c -o multiplicacao
./multiplicacao
