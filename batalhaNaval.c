#include <stdio.h>
#include <stdbool.h>

// Definições de constantes
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Protótipos de funções
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
bool posicionarNavioNormal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                           int linha_inicio, int col_inicio, int orientacao);
bool posicionarNavioDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                             int linha_inicio, int col_inicio, int tipo_diagonal);

int main() {
    // 1. Represente o Tabuleiro: Matriz 10x10 inicializada com AGUA (0)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    inicializarTabuleiro(tabuleiro);

    printf("--- Posicionamento dos Navios (Nível Aventureiro) ---\n");

    // 2. Posicione os Quatro Navios (2 Normais e 2 Diagonais)

    // Navio 1: Horizontal (Normal) - Linha 2, Coluna 1. Ocupa (2,1) a (2,3).
    posicionarNavioNormal(tabuleiro, 2, 1, 0); 
    
    // Navio 2: Vertical (Normal) - Linha 5, Coluna 7. Ocupa (5,7) a (7,7).
    posicionarNavioNormal(tabuleiro, 5, 7, 1);

    // Navio 3: Diagonal Principal (linha++, coluna++) - Linha 0, Coluna 6. Ocupa (0,6), (1,7), (2,8).
    posicionarNavioDiagonal(tabuleiro, 0, 6, 0); 

    // Navio 4: Diagonal Secundária (linha++, coluna--) - Linha 6, Coluna 3. Ocupa (6,3), (7,2), (8,1).
    posicionarNavioDiagonal(tabuleiro, 6, 3, 1);
    
    // Exemplo de teste de sobreposição (deve falhar e não posicionar)
    printf("\n--- Teste de Validação (Deve falhar) ---\n");
    posicionarNavioNormal(tabuleiro, 1, 7, 1); 

    // 3. Exiba o Tabuleiro
    printf("\n--- Tabuleiro Final (4 Navios) ---\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}

void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

bool posicionarNavioNormal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                           int linha_inicio, int col_inicio, int orientacao) {
    int i, j;
    int direcao_linha = (orientacao == 1) ? 1 : 0;
    int direcao_col = (orientacao == 0) ? 1 : 0;
    
    // 1. Validação de Limites
    if (linha_inicio < 0 || col_inicio < 0 || 
        linha_inicio + direcao_linha * (TAMANHO_NAVIO - 1) >= TAMANHO_TABULEIRO ||
        col_inicio + direcao_col * (TAMANHO_NAVIO - 1) >= TAMANHO_TABULEIRO) {
        printf("Falha ao posicionar Navio Normal: Fora dos limites.\n");
        return false;
    }

    // 2. Validação de Sobreposição
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        i = linha_inicio + direcao_linha * k;
        j = col_inicio + direcao_col * k;
        
        if (tabuleiro[i][j] == NAVIO) {
            printf("Falha ao posicionar Navio Normal: Sobreposição detectada em (%d, %d).\n", i, j);
            return false;
        }
    }

    // 3. Posicionamento
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        i = linha_inicio + direcao_linha * k;
        j = col_inicio + direcao_col * k;
        tabuleiro[i][j] = NAVIO;
    }
    printf("Navio Normal posicionado com sucesso! (%s em %d,%d)\n", 
           orientacao == 0 ? "H" : "V", linha_inicio, col_inicio);
    return true;
}

bool posicionarNavioDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                             int linha_inicio, int col_inicio, int tipo_diagonal) {
    
    int direcao_col = (tipo_diagonal == 0) ? 1 : -1; 
    int nova_linha, nova_col;

    // 1. Validação de Limites
    nova_linha = linha_inicio + (TAMANHO_NAVIO - 1);
    nova_col = col_inicio + direcao_col * (TAMANHO_NAVIO - 1);

    if (linha_inicio < 0 || col_inicio < 0 || col_inicio >= TAMANHO_TABULEIRO ||
        nova_linha >= TAMANHO_TABULEIRO || nova_col < 0 || nova_col >= TAMANHO_TABULEIRO) {
        printf("Falha ao posicionar Navio Diagonal: Fora dos limites.\n");
        return false;
    }

    // 2. Validação de Sobreposição e 3. Posicionamento
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        nova_linha = linha_inicio + k;
        nova_col = col_inicio + direcao_col * k;
        
        if (tabuleiro[nova_linha][nova_col] == NAVIO) {
            printf("Falha ao posicionar Navio Diagonal: Sobreposição detectada em (%d, %d).\n", nova_linha, nova_col);
            return false;
        }
    }
    
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        nova_linha = linha_inicio + k;
        nova_col = col_inicio + direcao_col * k;
        tabuleiro[nova_linha][nova_col] = NAVIO;
    }
    printf("Navio Diagonal posicionado com sucesso! (%s em %d,%d)\n", 
           tipo_diagonal == 0 ? "Principal" : "Secundária", linha_inicio, col_inicio);
    return true;
}

void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int i, j;

    // Cabeçalho das Colunas (0-9)
    printf("   ");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf(" %2d", j);
    }
    printf("\n");

    // Linha separadora
    printf("  +-");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("---");
    }
    printf("\n");

    // Conteúdo
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Índice da Linha (0-9)
        printf("%d |", i);
        
        // Valores da linha
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %2d", tabuleiro[i][j]);
        }
        printf(" \n");
    }

    // rodapé
    printf("  +-");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("---");
    }
    printf("\n");
}

