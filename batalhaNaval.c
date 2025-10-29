#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definições de tamanho
#define TAMANHO_TABULEIRO 10
#define TAMANHO_HABILIDADE 5 // Tamanho da matriz de habilidade (fixo, por exemplo, 5x5)
#define CENTRO_HABILIDADE (TAMANHO_HABILIDADE / 2) // Posição do centro (2 para matriz 5x5)

// Definições de valores no tabuleiro
#define AGUA 0
#define NAVIO 3
#define AFETADO 5 // Valor para representar a área afetada pela habilidade

// Protótipos de funções
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void posicionar_navios(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void criar_habilidade_cone(int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void criar_habilidade_cruz(int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void criar_habilidade_octaedro(int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void sobrepor_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                         int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                         int origem_linha, int origem_coluna);
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);


int main() {
    // 1. Definição do Tabuleiro e Matrizes de Habilidade
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int habilidade_cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidade_cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidade_octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // Inicialização do tabuleiro e posicionamento de navios
    inicializar_tabuleiro(tabuleiro);
    posicionar_navios(tabuleiro);

    // 2. Criação das áreas de efeito (matrizes 0 e 1)
    criar_habilidade_cone(habilidade_cone);
    criar_habilidade_cruz(habilidade_cruz);
    criar_habilidade_octaedro(habilidade_octaedro);


    // 3. Integração das Habilidades ao Tabuleiro

    // Definição dos pontos de origem (centro) de cada habilidade no tabuleiro
    int origem_cone_l = 2; // Linha 2
    int origem_cone_c = 2; // Coluna 2

    int origem_cruz_l = 6; // Linha 6
    int origem_cruz_c = 7; // Coluna 7

    int origem_octaedro_l = 8; // Linha 8
    int origem_octaedro_c = 3; // Coluna 3

    // Sobreposição das habilidades no tabuleiro
    sobrepor_habilidade(tabuleiro, habilidade_cone, origem_cone_l, origem_cone_c);
    sobrepor_habilidade(tabuleiro, habilidade_cruz, origem_cruz_l, origem_cruz_c);
    sobrepor_habilidade(tabuleiro, habilidade_octaedro, origem_octaedro_l, origem_octaedro_c);

    // 4. Exibição do Tabuleiro com Habilidades
    printf("--- Tabuleiro Final de Batalha Naval com Habilidades ---\n");
    exibir_tabuleiro(tabuleiro);
    printf("\nLegenda:\n");
    printf("  . : Água (0)\n");
    printf("  N : Navio (3)\n");
    printf("  X : Área Afetada pela Habilidade (5)\n");
    
    return 0;
}

// Inicializa o tabuleiro com AGUA (0).
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Posiciona navios (valor NAVIO = 3) para visualização.
void posicionar_navios(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Navio horizontal
    tabuleiro[0][0] = NAVIO;
    tabuleiro[0][1] = NAVIO;
    tabuleiro[0][2] = NAVIO;

    // Navio vertical na área da Cruz
    tabuleiro[6][7] = NAVIO; 
    tabuleiro[7][7] = NAVIO;

    // Navio atingido pelo Cone
    tabuleiro[3][2] = NAVIO;
    tabuleiro[4][2] = NAVIO;

    // Navio atingido pelo Octaedro
    tabuleiro[8][3] = NAVIO;
}

// Cria a matriz de habilidade em forma de CONE.
// Lógica: O cone aponta para baixo. A largura (distância do centro) aumenta a cada linha (i).
void criar_habilidade_cone(int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    // Loops aninhados para percorrer a matriz
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int distancia_do_centro = abs(j - CENTRO_HABILIDADE);
            
            // Condicional: Se a distância horizontal for menor ou igual à linha atual (i)
            if (distancia_do_centro <= i) { 
                matriz_habilidade[i][j] = 1; // Afetado
            } else {
                matriz_habilidade[i][j] = 0; // Não Afetado
            }
        }
    }
}

// Cria a matriz de habilidade em forma de CRUZ.
// Lógica: Afeta a linha central E a coluna central da matriz.
void criar_habilidade_cruz(int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    // Loops aninhados para percorrer a matriz
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Condicional: Se estiver na linha central OU na coluna central
            if (i == CENTRO_HABILIDADE || j == CENTRO_HABILIDADE) {
                matriz_habilidade[i][j] = 1; // Afetado
            } else {
                matriz_habilidade[i][j] = 0; // Não Afetado
            }
        }
    }
}

// Cria a matriz de habilidade em forma de OCTAEDRO (Losango/Diamante).
// Lógica: Afeta a área onde a soma das distâncias do centro (Manhattan distance) 
// é menor ou igual ao raio (CENTRO_HABILIDADE).
void criar_habilidade_octaedro(int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    // Loops aninhados para percorrer a matriz
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int dist_vertical = abs(i - CENTRO_HABILIDADE);
            int dist_horizontal = abs(j - CENTRO_HABILIDADE);
            
            // Condicional: Fórmula do losango
            if (dist_vertical + dist_horizontal <= CENTRO_HABILIDADE) {
                matriz_habilidade[i][j] = 1; // Afetado
            } else {
                matriz_habilidade[i][j] = 0; // Não Afetado
            }
        }
    }
}

// Sobrepõe a matriz de habilidade (5x5) ao tabuleiro (10x10), centralizando no ponto de origem.
void sobrepor_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                         int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                         int origem_linha, int origem_coluna) {
    
    // Loops aninhados para percorrer a matriz de habilidade
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            
            // Se a posição da matriz de habilidade for afetada (valor 1)
            if (matriz_habilidade[i][j] == 1) {
                
                // Cálculo de centralização: Ajusta a coordenada da habilidade 
                // para o centro do ponto de origem no tabuleiro.
                int tabuleiro_l = origem_linha + (i - CENTRO_HABILIDADE);
                int tabuleiro_c = origem_coluna + (j - CENTRO_HABILIDADE);
                
                // Condicional para garantir que a área de efeito permaneça dentro dos limites do tabuleiro
                if (tabuleiro_l >= 0 && tabuleiro_l < TAMANHO_TABULEIRO &&
                    tabuleiro_c >= 0 && tabuleiro_c < TAMANHO_TABULEIRO) {
                    
                    // Marca a posição no tabuleiro com o valor AFETADO (5)
                    tabuleiro[tabuleiro_l][tabuleiro_c] = AFETADO;
                }
            }
        }
    }
}

// Exibe o tabuleiro no console, usando caracteres para cada elemento.
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Exibir cabeçalho de colunas (0 a 9)
    printf("  ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf(" %d", j);
    }
    printf("\n");
    
    // Loops aninhados para exibir as linhas e colunas
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i); // Exibir índice de linha
        
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" ");
            // Condicionais para mapear o valor para o caractere visual
            if (tabuleiro[i][j] == AGUA) {
                printf("."); // Água
            } else if (tabuleiro[i][j] == NAVIO) {
                printf("N"); // Navio
            } else if (tabuleiro[i][j] == AFETADO) {
                printf("X"); // Área Afetada (prioridade visual)
            } else {
                printf("?"); // Caso inesperado
            }
        }
        printf("\n");
    }
}