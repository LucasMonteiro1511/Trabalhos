#include <stdio.h>
#include <stdlib.h>

#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5

// Ideias de funções
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]);
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]);
void criarHabilidadeCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]);
void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]);
void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]);
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], 
                      int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], 
                      int linha_origem, int coluna_origem);

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    
    // Tabuleiro com águas e navios
    inicializarTabuleiro(tabuleiro);
    
    // Adicionar alguns navios
    tabuleiro[2][3] = 3;
    tabuleiro[5][7] = 3;
    tabuleiro[8][1] = 3;
    tabuleiro[3][8] = 3;
    tabuleiro[7][4] = 3;
    
    // Matrizes para as habilidades
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];
    
    // Criar padrões das habilidades
    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);
    
    // Aplicar habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, cone, 2, 2);      // Cone na posição (2,2)
    aplicarHabilidade(tabuleiro, cruz, 6, 6);      // Cruz na posição (6,6)
    aplicarHabilidade(tabuleiro, octaedro, 4, 8);  // Octaedro na posição (4,8)
    
    // Exibir tabuleiro com habilidades 
    printf("=== BATALHA NAVAL COM HABILIDADES ESPECIAIS ===\n");
    printf("Legenda:\n");
    printf("0 - Agua | 3 - Navio | 5 - Area de habilidade\n\n");
    exibirTabuleiro(tabuleiro);
    
    return 0;
}

// Inicializa o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Exibe o tabuleiro bonito
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Cria o padrão de habilidade com formato de cone
void criarHabilidadeCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Cone: forma triangular apontando para baixo
            if (j >= i && j < TAM_HABILIDADE - i) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Cria o padrão de habilidade com formato de cruz
void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Cruz: linha central + coluna central
            if (i == centro || j == centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Cria o padrão de habilidade em losango
void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Forma de losango
            int dist_vertical = abs(i - centro);
            int dist_horizontal = abs(j - centro);
            if (dist_vertical + dist_horizontal <= centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Aplica uma habilidade ao tabuleiro na posição especificada
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], 
                      int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], 
                      int linha_origem, int coluna_origem) {
    int offset = TAM_HABILIDADE / 2;
    
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int linha_tab = linha_origem - offset + i;
            int coluna_tab = coluna_origem - offset + j;
            
            // Verifica se está dentro dos limites do tabuleiro
            if (linha_tab >= 0 && linha_tab < TAM_TABULEIRO && 
                coluna_tab >= 0 && coluna_tab < TAM_TABULEIRO) {
                
                // Se a posição na matriz de habilidade estiver ativa
                if (habilidade[i][j] == 1) {
                    // Marca como área de habilidade, preservando navios
                    if (tabuleiro[linha_tab][coluna_tab] != 3) {
                        tabuleiro[linha_tab][coluna_tab] = 5;
                    }
                }
            }
        }
    }
}