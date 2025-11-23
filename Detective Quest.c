#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAMANHO_HASH 10

// Comodo da mansao
typedef struct Sala {
    char nome[30];
    char pista[100];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Estrutura para uma pista na BST
typedef struct Pista {
    char descricao[100];
    struct Pista *esquerda;
    struct Pista *direita;
} Pista;

// Estrutura para a tabela hash (pista -> suspeito)
typedef struct EntradaHash {
    char pista[100];
    char suspeito[30];
    struct EntradaHash *proximo;
} EntradaHash;

// Estrutura para a tabela hash
typedef struct {
    EntradaHash *tabela[TAMANHO_HASH];
} TabelaHash;

// Criar um novo comodo
Sala* criarSala(char nome[], char pista[]) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    strcpy(novaSala->nome, nome);
    strcpy(novaSala->pista, pista);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

// Hash simples para mapear pistas para indices
int funcaoHash(char pista[]) {
    int soma = 0;
    for (int i = 0; pista[i] != '\0'; i++) {
        soma += pista[i];
    }
    return soma % TAMANHO_HASH;
}

// Inserir na tabela hash
void inserirNaHash(TabelaHash *hash, char pista[], char suspeito[]) {
    int indice = funcaoHash(pista);
    
    EntradaHash *novaEntrada = (EntradaHash*)malloc(sizeof(EntradaHash));
    strcpy(novaEntrada->pista, pista);
    strcpy(novaEntrada->suspeito, suspeito);
    novaEntrada->proximo = NULL;
    
    // Insercao no inicio da lista encadeada
    if (hash->tabela[indice] == NULL) {
        hash->tabela[indice] = novaEntrada;
    } else {
        novaEntrada->proximo = hash->tabela[indice];
        hash->tabela[indice] = novaEntrada;
    }
}

// Encontrar suspeito baseado em uma pista
char* encontrarSuspeito(TabelaHash *hash, char pista[]) {
    int indice = funcaoHash(pista);
    EntradaHash *atual = hash->tabela[indice];
    
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->proximo;
    }
    return "Desconhecido";
}

// Inserir pista na BST
Pista* inserirPista(Pista *raiz, char pista[]) {
    if (raiz == NULL) {
        Pista *novaPista = (Pista*)malloc(sizeof(Pista));
        strcpy(novaPista->descricao, pista);
        novaPista->esquerda = NULL;
        novaPista->direita = NULL;
        return novaPista;
    }
    
    int comparacao = strcmp(pista, raiz->descricao);
    
    if (comparacao < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if (comparacao > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }
    
    return raiz;
}

// Percorrer a BST em ordem (pistas ordenadas)
void percorrerPistas(Pista *raiz) {
    if (raiz != NULL) {
        percorrerPistas(raiz->esquerda);
        printf("  - %s\n", raiz->descricao);
        percorrerPistas(raiz->direita);
    }
}

// Contar pistas que apontam para um suspeito
int contarPistasSuspeito(TabelaHash *hash, Pista *raiz, char suspeito[]) {
    if (raiz == NULL) return 0;
    
    int count = 0;
    
    // Conta da subarvore esquerda
    count += contarPistasSuspeito(hash, raiz->esquerda, suspeito);
    
    // Conta o no atual
    if (strcmp(encontrarSuspeito(hash, raiz->descricao), suspeito) == 0) {
        count++;
    }
    
    // Conta da subarvore direita
    count += contarPistasSuspeito(hash, raiz->direita, suspeito);
    
    return count;
}

// Explorar salas
void explorarSalas(Sala *raiz, Pista **pistasColetadas, TabelaHash *hash) {
    Sala *atual = raiz;
    char comando;
    
    printf("\n=== EXPLORACAO DA MANSAO ===\n");
    printf("Comandos: e (esquerda), d (direita), s (sair)\n\n");
    
    while (atual != NULL) {
        printf("Voce esta no: %s\n", atual->nome);
        
        if (strlen(atual->pista) > 0) {
            printf(" Pista encontrada: %s\n", atual->pista);
            
            // Adiciona pista a BST
            *pistasColetadas = inserirPista(*pistasColetadas, atual->pista);
            
            // Mostra suspeito associado
            char* suspeito = encontrarSuspeito(hash, atual->pista);
            printf("   Suspeito relacionado: %s\n", suspeito);
        } else {
            printf("Nenhuma pista encontrada aqui.\n");
        }
        
        printf("\nPara onde deseja ir? (e/d/s): ");
        scanf(" %c", &comando);
        comando = tolower(comando);
        
        if (comando == 's') {
            printf("Saindo da exploracao...\n");
            break;
        } else if (comando == 'e') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Nao ha sala a esquerda!\n");
            }
        } else if (comando == 'd') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Nao ha sala a direita!\n");
            }
        } else {
            printf("Comando invalido!\n");
        }
        printf("\n");
    }
}

// Funcao para verificar suspeito final
void verificarSuspeitoFinal(TabelaHash *hash, Pista *pistasColetadas) {
    char suspeito[30];
    
    printf("\n=== FASE DE JULGAMENTO ===\n");
    printf("Pistas coletadas (em ordem):\n");
    percorrerPistas(pistasColetadas);
    
    printf("\nSuspeitos disponíveis:\n");
    printf("- Joao (Mordomo)\n");
    printf("- Maria (Herdeira)\n"); 
    printf("- Carlos (Empresario)\n");
    printf("- Ana (Amiga da Vitima)\n");
    
    printf("\nQuem voce acusa como culpado? ");
    scanf(" %[^\n]", suspeito);
    
    int pistasConfirmadas = contarPistasSuspeito(hash, pistasColetadas, suspeito);
    
    printf("\n=== RESULTADO FINAL ===\n");
    printf("Suspeito acusado: %s\n", suspeito);
    printf("Pistas que apontam para %s: %d\n", suspeito, pistasConfirmadas);
    
    if (pistasConfirmadas >= 2) {
        printf(" PARABENS! Voce prendeu o culpado!\n");
        printf("Ha evidencias suficientes para condenar %s!\n", suspeito);
    } else {
        printf(" INSUFICIENTE! Nao ha pistas suficientes.\n");
        printf("%s foi liberado por falta de provas.\n", suspeito);
    }
}

// Liberar memoria da arvore de salas
void liberarSalas(Sala *raiz) {
    if (raiz != NULL) {
        liberarSalas(raiz->esquerda);
        liberarSalas(raiz->direita);
        free(raiz);
    }
}

// Liberar memoria da BST de pistas
void liberarPistas(Pista *raiz) {
    if (raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}

// Liberar memoria da tabela hash
void liberarHash(TabelaHash *hash) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        EntradaHash *atual = hash->tabela[i];
        while (atual != NULL) {
            EntradaHash *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
}

int main() {
    // Inicializa estruturas
    Pista *pistasColetadas = NULL;
    TabelaHash hash;
    for (int i = 0; i < TAMANHO_HASH; i++) {
        hash.tabela[i] = NULL;
    }
    
    // Cria o mapa da mansao (arvore binaria fixa)
    Sala *salaEntrada = criarSala("Entrada Principal", "Cartao de visita com inicial 'J'");
    Sala *salaBiblioteca = criarSala("Biblioteca", "Livro sobre venenos aberto");
    Sala *salaEscritorio = criarSala("Escritorio", "Extrato bancario com valor suspeito");
    Sala *salaJardim = criarSala("Jardim", "Pegadas de salto alto na terra");
    Sala *salaQuarto = criarSala("Quarto Principal", "Carta de ameaca rasgada");
    Sala *salaCozinha = criarSala("Cozinha", "Mancha vermelha no pano");
    Sala *salaPorao = criarSala("Porao", "Fio de cabelo loiro preso");
    
    // Monta a arvore da mansao
    salaEntrada->esquerda = salaBiblioteca;
    salaEntrada->direita = salaJardim;
    
    salaBiblioteca->esquerda = salaEscritorio;
    salaBiblioteca->direita = salaQuarto;
    
    salaJardim->esquerda = salaCozinha;
    salaJardim->direita = salaPorao;
    
    // Configura tabela hash com associacoes pista->suspeito
    inserirNaHash(&hash, "Cartao de visita com inicial 'J'", "Joao");
    inserirNaHash(&hash, "Livro sobre venenos aberto", "Maria");
    inserirNaHash(&hash, "Extrato bancario com valor suspeito", "Carlos");
    inserirNaHash(&hash, "Pegadas de salto alto na terra", "Ana");
    inserirNaHash(&hash, "Carta de ameaca rasgada", "Joao");
    inserirNaHash(&hash, "Mancha vermelha no pano", "Maria");
    inserirNaHash(&hash, "Fio de cabelo loiro preso", "Ana");
    
    printf("=== DETECTIVE QUEST - O MISTERIO DA MANSAO ===\n");
    printf("Um crime foi cometido! Explore a mansao, colete pistas\n");
    printf("e descubra quem e o verdadeiro culpado!\n");
    
    // Exploracao interativa
    explorarSalas(salaEntrada, &pistasColetadas, &hash);
    
    // Fase de julgamento
    verificarSuspeitoFinal(&hash, pistasColetadas);
    
    // Libera memoria
    liberarSalas(salaEntrada);
    liberarPistas(pistasColetadas);
    liberarHash(&hash);
    
    printf("\n=== FIM DO JOGO ===\n");
    
    return 0;
}