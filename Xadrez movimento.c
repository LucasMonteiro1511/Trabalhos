#include <stdio.h>

// Direções

#define CIMA 0
#define BAIXO 1
#define ESQUERDA 2
#define DIREITA 3

// Ideia das funções

void moverTorre(int casas, int direcao);
void moverBispo(int casas, int direcaoVertical, int direcaoHorizontal);
void moverRainha(int casas, int direcaoVertical, int direcaoHorizontal);
void moverCavalo();
void imprimirDirecao(int direcao);

int main() {
    printf("=== SIMULADOR DE MOVIMENTOS DE XADREZ ===\n\n");
    
    // Movimento da Torre (recursivo)
    printf("Movimento da Torre (4 casas para cima):\n");
    moverTorre(4, CIMA);
    printf("\n");
    
    // Movimento do Bispo (recursivo e com loops aninhados)
    printf("Movimento do Bispo (3 casas na diagonal superior direita):\n");
    moverBispo(3, CIMA, DIREITA);
    printf("\n");
    
    // Movimento da Rainha (recursivo)
    printf("Movimento da Rainha (2 casas na diagonal inferior esquerda):\n");
    moverRainha(2, BAIXO, ESQUERDA);
    printf("\n");
    
    // Movimento do Cavalo (loops complexos)
    printf("Movimento do Cavalo (em L para cima e direita):\n");
    moverCavalo();
    printf("\n");
    
    return 0;
}

// Função pra imprimir a direção

void imprimirDirecao(int direcao) {
    switch(direcao) {
        case CIMA: printf("Cima\n"); break;
        case BAIXO: printf("Baixo\n"); break;
        case ESQUERDA: printf("Esquerda\n"); break;
        case DIREITA: printf("Direita\n"); break;
    }
}

// Função pra mover a Torre
void moverTorre(int casas, int direcao) {
    if (casas <= 0) return; // Caso base
    
    imprimirDirecao(direcao);
    moverTorre(casas - 1, direcao); // Chamada recursiva
}

// Função pra mover o Bispo 
void moverBispo(int casas, int direcaoVertical, int direcaoHorizontal) {
    if (casas <= 0) return; // Caso base
    
    // Vertical ou Horizontal
    imprimirDirecao(direcaoVertical);
    imprimirDirecao(direcaoHorizontal);
    
    // Teste de loop
    for (int i = 0; i < 1; i++) { // Loop externo (vertical)
        for (int j = 0; j < 1; j++) { // Loop interno (horizontal)
            printf("Diagonal: ");
            imprimirDirecao(direcaoVertical);
            imprimirDirecao(direcaoHorizontal);
        }
    }
    
    moverBispo(casas - 1, direcaoVertical, direcaoHorizontal); 
}

// Função pra mover a Rainha
void moverRainha(int casas, int direcaoVertical, int direcaoHorizontal) {
    if (casas <= 0) return; // Caso base
    
    // Rainha vertical ou horizontal
    imprimirDirecao(direcaoVertical);
    imprimirDirecao(direcaoHorizontal);
    
    moverRainha(casas - 1, direcaoVertical, direcaoHorizontal); 
}

// Função pra mover o Cavalo (o movimento em L)
void moverCavalo() {
    // Ideia para o L
    for (int i = 1; i <= 2; i++) {
        if (i > 2) break; // Nunca deve acontecer, apenas para demonstração
        
        for (int j = 1; j <= 1; j++) {
            if (i == 1 && j == 1) {
                printf("Primeira parte do L:\n");
            }
            
            // Os movimentos para cima
            if (i <= 2) {
                printf("Cima\n");
                continue; // Continua para o próximo passo do loop
            }
            
            // O movimento para a direita
            printf("Direita\n");
        }
    }
    
    // Movimento final pra direita
    printf("Direita\n");
    
    // Loop de teste
    for (int x = 0, y = 0; x < 1 && y < 1; x++, y++) {
        printf("Posição final do cavalo: %d,%d\n", x, y);
    }
}