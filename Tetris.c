#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO_FILA 5
#define TAMANHO_PILHA 3

// Estrutura para representar uma peca
typedef struct {
    char nome;
    int id;
} Peca;

// Estrutura para a fila circular
typedef struct {
    Peca pecas[TAMANHO_FILA];
    int inicio;
    int fim;
    int quantidade;
} FilaCircular;

// Estrutura para a pilha
typedef struct {
    Peca pecas[TAMANHO_PILHA];
    int topo;
} Pilha;

// Variavel global para gerar IDs unicos
int proximo_id = 0;

// Gerar uma nova peca aleatoria
Peca gerarPeca() {
    Peca nova_peca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    
    nova_peca.nome = tipos[rand() % 4];
    nova_peca.id = proximo_id++;
    
    return nova_peca;
}

// Funcao para inicializar a fila circular
void inicializarFila(FilaCircular *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->quantidade = 0;
    
    // Preenche a fila com pecas iniciais
    for (int i = 0; i < TAMANHO_FILA; i++) {
        fila->pecas[fila->fim] = gerarPeca();
        fila->fim = (fila->fim + 1) % TAMANHO_FILA;
        fila->quantidade++;
    }
}

// Inicializar a pilha
void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1; // Pilha vazia
}

// Adicionar peca na fila (enqueue)
void adicionarNaFila(FilaCircular *fila, Peca peca) {
    if (fila->quantidade < TAMANHO_FILA) {
        fila->pecas[fila->fim] = peca;
        fila->fim = (fila->fim + 1) % TAMANHO_FILA;
        fila->quantidade++;
    }
}

// Remover peca da fila (dequeue)
Peca removerDaFila(FilaCircular *fila) {
    Peca peca_removida;
    
    if (fila->quantidade > 0) {
        peca_removida = fila->pecas[fila->inicio];
        fila->inicio = (fila->inicio + 1) % TAMANHO_FILA;
        fila->quantidade--;
    }
    
    return peca_removida;
}

// Ver peCa da frente da fila sem remover
Peca verFrenteFila(FilaCircular *fila) {
    return fila->pecas[fila->inicio];
}

// Empilhar peca (push)
int empilhar(Pilha *pilha, Peca peca) {
    if (pilha->topo < TAMANHO_PILHA - 1) {
        pilha->topo++;
        pilha->pecas[pilha->topo] = peca;
        return 1; // Sucesso
    }
    return 0; // Pilha cheia
}

// Desempilhar peca (pop)
Peca desempilhar(Pilha *pilha) {
    Peca peca_removida;
    
    if (pilha->topo >= 0) {
        peca_removida = pilha->pecas[pilha->topo];
        pilha->topo--;
    }
    
    return peca_removida;
}

// Exibir o estado atual do jogo
void exibirEstado(FilaCircular *fila, Pilha *pilha) {
    printf("\n=== ESTADO ATUAL ===\n");
    
    // Exibe a fila de pecas
    printf("Fila de pecas:\t");
    if (fila->quantidade == 0) {
        printf("Vazia");
    } else {
        int indice = fila->inicio;
        for (int i = 0; i < fila->quantidade; i++) {
            printf("[%c %d] ", fila->pecas[indice].nome, fila->pecas[indice].id);
            indice = (indice + 1) % TAMANHO_FILA;
        }
    }
    printf("\n");
    
    // Exibe a pilha de reserva
    printf("Pilha de reserva:\t(Topo -> Base): ");
    if (pilha->topo == -1) {
        printf("Vazia");
    } else {
        for (int i = pilha->topo; i >= 0; i--) {
            printf("[%c %d] ", pilha->pecas[i].nome, pilha->pecas[i].id);
        }
    }
    printf("\n");
}

// Jogar uma peca (remover da frente da fila)
void jogarPeca(FilaCircular *fila) {
    if (fila->quantidade > 0) {
        Peca peca_jogada = removerDaFila(fila);
        printf(">>> Peca [%c %d] jogada!\n", peca_jogada.nome, peca_jogada.id);
        
        // Adiciona nova peca para manter a fila cheia
        adicionarNaFila(fila, gerarPeca());
    } else {
        printf(">>> Erro: Fila vazia!\n");
    }
}

// Reservar uma peca 
void reservarPeca(FilaCircular *fila, Pilha *pilha) {
    if (fila->quantidade > 0) {
        if (pilha->topo < TAMANHO_PILHA - 1) {
            Peca peca_reservada = removerDaFila(fila);
            
            if (empilhar(pilha, peca_reservada)) {
                printf(">>> Peca [%c %d] reservada!\n", peca_reservada.nome, peca_reservada.id);
                
                // Adiciona nova peça para manter a fila cheia
                adicionarNaFila(fila, gerarPeca());
            }
        } else {
            printf(">>> Erro: Pilha de reserva cheia!\n");
        }
    } else {
        printf(">>> Erro: Fila vazia!\n");
    }
}

// Peca reservada 
void usarPecaReservada(Pilha *pilha) {
    if (pilha->topo >= 0) {
        Peca peca_usada = desempilhar(pilha);
        printf(">>> Peca reservada [%c %d] usada!\n", peca_usada.nome, peca_usada.id);
    } else {
        printf(">>> Erro: Pilha de reserva vazia!\n");
    }
}

// Exibir o menu
void exibirMenu() {
    printf("\n=== OPCOES DE ACAO ===\n");
    printf("Codigo\tAcao\n");
    printf("1\tJogar peca\n");
    printf("2\tReservar peca\n");
    printf("3\tUsar peca reservada\n");
    printf("0\tSair\n");
    printf("Opcao: ");
}

int main() {
    srand(time(NULL)); // Inicializa o gerador de numeros aleatorios
    
    FilaCircular fila;
    Pilha pilha;
    
    // Inicializa as estruturas
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    
    printf("=== TETRIS STACK - GERENCIADOR DE PECAS ===\n");
    printf("Fila: %d pecas | Pilha de reserva: %d espacos\n", TAMANHO_FILA, TAMANHO_PILHA);
    
    int opcao;
    
    do {
        exibirEstado(&fila, &pilha);
        exibirMenu();
        
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                jogarPeca(&fila);
                break;
                
            case 2:
                reservarPeca(&fila, &pilha);
                break;
                
            case 3:
                usarPecaReservada(&pilha);
                break;
                
            case 0:
                printf(">>> Saindo do jogo...\n");
                break;
                
            default:
                printf(">>> Opcao invalida! Tente novamente.\n");
        }
        
    } while (opcao != 0);
    
    printf("=== FIM DO JOGO ===\n");
    
    return 0;
}