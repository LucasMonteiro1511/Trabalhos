#include <stdio.h>
#include <string.h> 

// Estrutura para representar uma carta do Super Trunfo
typedef struct {
    char estado[50];
    char codigo[10];
    char nome[100];
    unsigned long int populacao; // Acomodar números maiores
    float area;
    double pib; // PIB para maior precisão
    int pontos_turisticos;
    float densidade_populacional;
    float pib_per_capita;
    float super_poder;
} Carta;

// Função para ler os dados de uma carta
void lerDadosCarta(Carta *carta, int numero_carta) {
    printf("--- Dados da Carta %d ---\n", numero_carta);
    printf("Estado: ");
    scanf(" %[^\n]", carta->estado); // Leitura com espaços
    printf("Codigo: ");
    scanf(" %[^\n]", carta->codigo);
    printf("Nome: ");
    scanf(" %[^\n]", carta->nome);
    printf("Populacao: ");
    scanf("%lu", &carta->populacao);
    printf("Area (km2, float): ");
    scanf("%f", &carta->area);
    printf("PIB (double): ");
    scanf("%lf", &carta->pib);
    printf("Numero de Pontos Turisticos: ");
    scanf("%d", &carta->pontos_turisticos);
    printf("\n");
}

// Função para calcular Densidade Populacional e PIB per Capita
void calcularAtributosBasicos(Carta *carta) {
    if (carta->area > 0) {
        carta->densidade_populacional = (float)carta->populacao / carta->area;
    } else {
        carta->densidade_populacional = 0.0f; // Evita divisão por zero
    }

    if (carta->populacao > 0) {
        carta->pib_per_capita = (float)carta->pib / carta->populacao;
    } else {
        carta->pib_per_capita = 0.0f; // Evita divisão por zero
    }
}

// Função para calcular o Super Poder
void calcularSuperPoder(Carta *carta) {
    float inverso_densidade_populacional = 0.0f;
    if (carta->densidade_populacional > 0) {
        inverso_densidade_populacional = 1.0f / carta->densidade_populacional;
    }

    carta->super_poder = (float)carta->populacao +
                          carta->area +
                          (float)carta->pib +
                          (float)carta->pontos_turisticos +
                          carta->pib_per_capita +
                          inverso_densidade_populacional;
    // Atenção na conversão de tipos ao somar valores de tipos diferentes
}

// Função para exibir os dados de uma carta
void exibirDadosCarta(const Carta *carta, int numero_carta) {
    printf("--- Dados da Carta %d ---\n", numero_carta);
    printf("Estado: %s\n", carta->estado);
    printf("Codigo: %s\n", carta->codigo);
    printf("Nome: %s\n", carta->nome);
    printf("Populacao: %lu\n", carta->populacao);
    printf("Area: %.2f km2\n", carta->area);
    printf("PIB: %.2lf\n", carta->pib);
    printf("Pontos Turisticos: %d\n", carta->pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km2\n", carta->densidade_populacional);
    printf("PIB per Capita: %.2f\n", carta->pib_per_capita);
    printf("Super Poder: %.2f\n", carta->super_poder);
    printf("\n");
}

// Função para comparar as duas cartas e exibir os resultados
void compararCartas(const Carta *carta1, const Carta *carta2) {
    printf("Comparacao de Cartas:\n");

    // População
    printf("Populacao: ");
    if (carta1->populacao > carta2->populacao) {
        printf("Carta 1 venceu (1)\n");
    } else {
        printf("Carta 2 venceu (0)\n");
    }

    // Área
    printf("Area: ");
    if (carta1->area > carta2->area) {
        printf("Carta 1 venceu (1)\n");
    } else {
        printf("Carta 2 venceu (0)\n");
    }

    // PIB
    printf("PIB: ");
    if (carta1->pib > carta2->pib) {
        printf("Carta 1 venceu (1)\n");
    } else {
        printf("Carta 2 venceu (0)\n");
    }

    // Pontos Turísticos
    printf("Pontos Turisticos: ");
    if (carta1->pontos_turisticos > carta2->pontos_turisticos) {
        printf("Carta 1 venceu (1)\n");
    } else {
        printf("Carta 2 venceu (0)\n");
    }

    // Densidade Populacional (menor valor vence)
    printf("Densidade Populacional: ");
    if (carta1->densidade_populacional < carta2->densidade_populacional) {
        printf("Carta 1 venceu (1)\n");
    } else {
        printf("Carta 2 venceu (0)\n");
    }

    // PIB per Capita
    printf("PIB per Capita: ");
    if (carta1->pib_per_capita > carta2->pib_per_capita) {
        printf("Carta 1 venceu (1)\n");
    } else {
        printf("Carta 2 venceu (0)\n");
    }

    // Super Poder
    printf("Super Poder: ");
    if (carta1->super_poder > carta2->super_poder) {
        printf("Carta 1 venceu (1)\n");
    } else {
        printf("Carta 2 venceu (0)\n");
    }
}

int main() {
    Carta carta1, carta2;

    // Leitura dos dados da Carta 1
    lerDadosCarta(&carta1, 1);
    calcularAtributosBasicos(&carta1);
    calcularSuperPoder(&carta1);

    // Leitura dos dados da Carta 2
    lerDadosCarta(&carta2, 2);
    calcularAtributosBasicos(&carta2);
    calcularSuperPoder(&carta2);

    // Exibição dos dados de ambas as cartas (opcional, mas bom para verificação)
    exibirDadosCarta(&carta1, 1);
    exibirDadosCarta(&carta2, 2);

    // Comparação das cartas
    compararCartas(&carta1, &carta2);

    return 0;
}