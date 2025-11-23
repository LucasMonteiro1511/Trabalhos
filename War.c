#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Representacao de territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// atribuir missao aleatoria
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// missao foi cumprida
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // Missao 1: Conquistar pelo menos 3 territorios
    if (strstr(missao, "3 territorios")) {
        int territoriosConquistados = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Jogador") == 0) {
                territoriosConquistados++;
            }
        }
        return territoriosConquistados >= 3;
    }
    
    // Missao 2: Ter pelo menos 10 tropas no total
    if (strstr(missao, "10 tropas")) {
        int totalTropas = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Jogador") == 0) {
                totalTropas += mapa[i].tropas;
            }
        }
        return totalTropas >= 10;
    }
    
    // Missao 3: Conquistar territorio especifico
    if (strstr(missao, "territorio especifico")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].nome, "Europa") == 0 && strcmp(mapa[i].cor, "Jogador") == 0) {
                return 1;
            }
        }
        return 0;
    }
    
    // Missao 4: Eliminar todas as tropas de uma cor
    if (strstr(missao, "cor Vermelha")) {
        int tropasVermelhas = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0) {
                tropasVermelhas += mapa[i].tropas;
            }
        }
        return tropasVermelhas == 0;
    }
    
    // Missao 5: Conquistar 2 territorios consecutivos
    if (strstr(missao, "consecutivos")) {
        for (int i = 0; i < tamanho - 1; i++) {
            if (strcmp(mapa[i].cor, "Jogador") == 0 && 
                strcmp(mapa[i + 1].cor, "Jogador") == 0) {
                return 1;
            }
        }
        return 0;
    }
    
    return 0; // Missao nao reconhecida
}

// Funcao para exibir a missao do jogador
void exibirMissao(char* missao) {
    printf("Missao do Jogador: %s\n", missao);
}

// Funcao para simular um ataque entre territorios
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n=== ATAQUE ===\n");
    printf("%s (%s) ataca %s (%s)\n", 
           atacante->nome, atacante->cor, 
           defensor->nome, defensor->cor);
    
    // Simulacao de dados (1-6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);
    
    if (dadoAtacante > dadoDefensor) {
        printf("Atacante venceu!\n");
        // Conquista o territorio
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= atacante->tropas / 2;
    } else {
        printf("Defensor venceu!\n");
        atacante->tropas -= 1;
        if (atacante->tropas < 1) {
            atacante->tropas = 1; // Minimo de 1 tropa
        }
    }
}

// Funcao para exibir o estado atual do mapa
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n=== MAPA ATUAL ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Territorio: %-15s | Cor: %-10s | Tropas: %d\n", 
               mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Funcao para liberar memoria alocada
void liberarMemoria(Territorio* mapa, char** missoesJogadores, int numJogadores) {
    free(mapa);
    for (int i = 0; i < numJogadores; i++) {
        free(missoesJogadores[i]);
    }
    free(missoesJogadores);
}

int main() {
    srand(time(NULL)); // Inicializa gerador de números aleatórios
    
    // Vetor de missoes disponiveis
    char* missoes[] = {
        "Conquistar 3 territorios",
        "Acumular 10 tropas no total",
        "Conquistar o territorio especifico Europa",
        "Eliminar todas as tropas da cor Vermelha",
        "Conquistar 2 territorios consecutivos"
    };
    int totalMissoes = 5;
    
    // Configuracao inicial do mapa
    int numTerritorios = 6;
    Territorio* mapa = (Territorio*)malloc(numTerritorios * sizeof(Territorio));
    
    // Inicializa territorios
    strcpy(mapa[0].nome, "America");
    strcpy(mapa[0].cor, "Jogador");
    mapa[0].tropas = 5;
    
    strcpy(mapa[1].nome, "Europa");
    strcpy(mapa[1].cor, "Vermelho");
    mapa[1].tropas = 3;
    
    strcpy(mapa[2].nome, "Asia");
    strcpy(mapa[2].cor, "Azul");
    mapa[2].tropas = 4;
    
    strcpy(mapa[3].nome, "Africa");
    strcpy(mapa[3].cor, "Verde");
    mapa[3].tropas = 2;
    
    strcpy(mapa[4].nome, "Oceania");
    strcpy(mapa[4].cor, "Amarelo");
    mapa[4].tropas = 3;
    
    strcpy(mapa[5].nome, "Antartida");
    strcpy(mapa[5].cor, "Roxo");
    mapa[5].tropas = 1;
    
    // Aloca e atribui missao ao jogador
    char* missaoJogador = (char*)malloc(100 * sizeof(char));
    atribuirMissao(missaoJogador, missoes, totalMissoes);
    
    printf("=== WAR - MISSÕES ESTRATÉGICAS ===\n");
    exibirMissao(missaoJogador);
    printf("\n");
    
    // Simulacao de jogo
    int turno = 1;
    int jogoAtivo = 1;
    
    while (jogoAtivo && turno <= 10) { // Maximo de 10 turnos para demonstracao
        printf("\n=== TURNO %d ===\n", turno);
        exibirMapa(mapa, numTerritorios);
        
        // Simula um ataque aleatorio a cada turno
        int atacanteIndex = 0; // Jogador sempre ataca
        int defensorIndex;
        do {
            defensorIndex = rand() % numTerritorios;
        } while (strcmp(mapa[defensorIndex].cor, "Jogador") == 0);
        
        atacar(&mapa[atacanteIndex], &mapa[defensorIndex]);
        
        // Verifica se a missao foi cumprida
        if (verificarMissao(missaoJogador, mapa, numTerritorios)) {
            printf("\n PARABENS! Missao cumprida! \n");
            printf("Voce venceu o jogo!\n");
            jogoAtivo = 0;
        }
        
        turno++;
        
        // Pausa para visualizacao
        if (jogoAtivo) {
            printf("\nPressione Enter para continuar...");
            getchar();
        }
    }
    
    if (jogoAtivo) {
        printf("\nFim dos turnos. Jogo terminou sem vencedor.\n");
    }
    
    // Libera memoria alocada
    char** missoesArray = (char**)malloc(sizeof(char*));
    missoesArray[0] = missaoJogador;
    liberarMemoria(mapa, missoesArray, 1);
    
    return 0;
}