#include <stdio.h>

// Definições de constantes
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Protótipo da função
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

int main() {
    // 1. Represente o Tabuleiro: Matriz 10x10 inicializada com AGUA (0)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int i, j;

    // Inicialização do tabuleiro
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // 2. Posicione os Navios

    // 2.1 Navio Horizontal (Linha 2, Coluna 1)
    int linha_h = 2;
    int coluna_h = 1;

    // Validação de limites para o navio horizontal
    if (coluna_h + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        // Posicionamento
        for (j = 0; j < TAMANHO_NAVIO; j++) {
            tabuleiro[linha_h][coluna_h + j] = NAVIO;
        }
    } else {
        printf("ERRO: Navio Horizontal fora dos limites.\n");
    }

    // 2.2 Navio Vertical (Linha 5, Coluna 7)
    int linha_v = 5;
    int coluna_v = 7;

    // Validação de limites e não sobreposição (garantida pela escolha de coordenadas)
    if (linha_v + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        // Posicionamento
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha_v + i][coluna_v] = NAVIO;
        }
    } else {
        printf("ERRO: Navio Vertical fora dos limites.\n");
    }

    // 3. Exiba o Tabuleiro
    printf("--- Tabuleiro de Batalha Naval ---\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}

// Implementação da função de exibição
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int i, j;

    // Cabeçalho das Colunas (0-9)
    printf("   ");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf(" %d", j);
    }
    printf("\n");

    // Linha separadora
    printf("  +-");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("--");
    }
    printf("\n");

    // Conteúdo
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Índice da Linha (0-9)
        printf("%d |", i);
        
        // Valores da linha
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %d", tabuleiro[i][j]);
        }
        printf(" |\n");
    }

    //rodapé
    printf("  +-");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("--");
    }
    printf("\n");
}

