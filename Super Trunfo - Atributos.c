#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_NOME 50
#define NUM_ATRIBUTOS 7

typedef struct {
    char nome[MAX_NOME];
    unsigned long populacao;
    float area;
    float PIB; 
    int pontos_turisticos;
    float densidade;
    float pib_per_capita;
} Carta;

// Funcoes

void exibirMenuAtributos(bool disponiveis[]);
int escolherAtributo(bool disponiveis[], const char* mensagem);
void compararAtributo(const Carta *c1, const Carta *c2, int atributo);
float obterValorAtributo(const Carta *carta, int atributo);
const char* nomeAtributo(int atributo);
bool atributoMenorVence(int atributo);

int main() {
    // Cartas cadastradas 
    Carta carta1 = {
        .nome = "Brasil",
        .populacao = 213990000,
        .area = 8515767.0,
        .PIB = 1840.0,
        .pontos_turisticos = 250,
        .densidade = 25.12,
        .pib_per_capita = 8598.0
    };
    
    Carta carta2 = {
        .nome = "Estados Unidos",
        .populacao = 331000000,
        .area = 9833517.0,
        .PIB = 20930.0,
        .pontos_turisticos = 350,
        .densidade = 33.67,
        .pib_per_capita = 63400.0
    };

    printf("=== SUPER TRUNFO: COMPARAÇÃO AVANÇADA ===\n");
    printf("Comparando: %s vs %s\n\n", carta1.nome, carta2.nome);

    // Array para controlar quais atributos estão disponíveis para seleção
    bool atributosDisponiveis[NUM_ATRIBUTOS] = {true, true, true, true, true, true, true};

    // Escolher primeiro atributo
    exibirMenuAtributos(atributosDisponiveis);
    int atributo1 = escolherAtributo(atributosDisponiveis, "Escolha o primeiro atributo para comparação");
    
    // Marcar primeiro atributo como indisponivel
    atributosDisponiveis[atributo1] = false;

    // Escolher segundo atributo
    exibirMenuAtributos(atributosDisponiveis);
    int atributo2 = escolherAtributo(atributosDisponiveis, "Escolha o segundo atributo para comparação");

    printf("\n=== RESULTADOS DA COMPARAÇÃO ===\n");
    printf("Países: %s vs %s\n", carta1.nome, carta2.nome);
    printf("Atributos selecionados: %s e %s\n\n", 
           nomeAtributo(atributo1), nomeAtributo(atributo2));

    // Comparar primeiro atributo
    printf("[Atributo 1: %s]\n", nomeAtributo(atributo1));
    compararAtributo(&carta1, &carta2, atributo1);

    // Comparar segundo atributo
    printf("\n[Atributo 2: %s]\n", nomeAtributo(atributo2));
    compararAtributo(&carta1, &carta2, atributo2);

    // Calcular soma dos atributos para cada carta
    float soma1 = obterValorAtributo(&carta1, atributo1) + obterValorAtributo(&carta1, atributo2);
    float soma2 = obterValorAtributo(&carta2, atributo1) + obterValorAtributo(&carta2, atributo2);

    printf("\nSoma dos atributos:\n");
    printf("%s: %.2f\n", carta1.nome, soma1);
    printf("%s: %.2f\n", carta2.nome, soma2);

    // Determinar o vencedor
    if(soma1 > soma2) {
        printf("\nResultado final: %s vence!\n", carta1.nome);
    } else if(soma2 > soma1) {
        printf("\nResultado final: %s vence!\n", carta2.nome);
    } else {
        printf("\nResultado final: Empate!\n");
    }

    return 0;
}

void exibirMenuAtributos(bool disponiveis[]) {
    printf("\nAtributos disponíveis:\n");
    for(int i = 0; i < NUM_ATRIBUTOS; i++) {
        if(disponiveis[i]) {
            printf("%d - %s\n", i+1, nomeAtributo(i));
        }
    }
}

int escolherAtributo(bool disponiveis[], const char* mensagem) {
    int escolha;
    bool valido = false;
    
    while(!valido) {
        printf("\n%s (1-%d): ", mensagem, NUM_ATRIBUTOS);
        scanf("%d", &escolha);
        
        if(escolha < 1 || escolha > NUM_ATRIBUTOS) {
            printf("Opção inválida! Digite um número entre 1 e %d.\n", NUM_ATRIBUTOS);
        } else if(!disponiveis[escolha-1]) {
            printf("Atributo já selecionado! Escolha outro.\n");
        } else {
            valido = true;
        }
        
        // Limpar buffer de entrada
        while(getchar() != '\n');
    }
    
    return escolha - 1; // Retorna índice baseado em 0
}

void compararAtributo(const Carta *c1, const Carta *c2, int atributo) {
    float valor1 = obterValorAtributo(c1, atributo);
    float valor2 = obterValorAtributo(c2, atributo);
    
    printf("%s: %.2f\n", c1->nome, valor1);
    printf("%s: %.2f\n", c2->nome, valor2);
    
    bool c1_vence;
    if(atributoMenorVence(atributo)) {
        c1_vence = valor1 < valor2;
    } else {
        c1_vence = valor1 > valor2;
    }
    
    printf("Vencedor: %s (%s)\n", 
           c1_vence ? c1->nome : c2->nome,
           c1_vence ? "1" : "0");
}

float obterValorAtributo(const Carta *carta, int atributo) {
    switch(atributo) {
        case 0: return carta->populacao;
        case 1: return carta->area;
        case 2: return carta->PIB;
        case 3: return carta->pontos_turisticos;
        case 4: return carta->densidade;
        case 5: return carta->pib_per_capita;
        default: return 0;
    }
}

const char* nomeAtributo(int atributo) {
    const char* nomes[NUM_ATRIBUTOS] = {
        "População", "Área", "PIB", "Pontos Turísticos",
        "Densidade Demográfica", "PIB per Capita", "Super Poder"
    };
    return nomes[atributo];
}

bool atributoMenorVence(int atributo) {
    // Apenas Densidade Demográfica vence com menor valor
    return atributo == 4;
}