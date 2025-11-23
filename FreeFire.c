#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para representar um componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Contagem de comparacoes
int comparacoes_bubble = 0;
int comparacoes_insertion = 0;
int comparacoes_selection = 0;
int comparacoes_busca = 0;

// Limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Cadastrar componentes
void cadastrarComponentes(Componente componentes[], int *quantidade) {
    printf("=== CADASTRO DE COMPONENTES ===\n");
    printf("Quantos componentes deseja cadastrar? (max 20): ");
    scanf("%d", quantidade);
    limparBuffer();
    
    if (*quantidade > 20) {
        printf("Quantidade reduzida para 20 (máximo permitido)\n");
        *quantidade = 20;
    }
    
    for (int i = 0; i < *quantidade; i++) {
        printf("\nComponente %d:\n", i + 1);
        
        printf("Nome: ");
        fgets(componentes[i].nome, 30, stdin);
        componentes[i].nome[strcspn(componentes[i].nome, "\n")] = 0;
        
        printf("Tipo (controle/suporte/propulsao): ");
        fgets(componentes[i].tipo, 20, stdin);
        componentes[i].tipo[strcspn(componentes[i].tipo, "\n")] = 0;
        
        printf("Prioridade (1-10): ");
        scanf("%d", &componentes[i].prioridade);
        limparBuffer();
        
        // Validacao da prioridade
        if (componentes[i].prioridade < 1) componentes[i].prioridade = 1;
        if (componentes[i].prioridade > 10) componentes[i].prioridade = 10;
    }
}

// Bubble Sort por nome
void bubbleSortNome(Componente componentes[], int n) {
    comparacoes_bubble = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes_bubble++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                // Troca os componentes
                Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort por tipo
void insertionSortTipo(Componente componentes[], int n) {
    comparacoes_insertion = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = componentes[i];
        int j = i - 1;
        
        while (j >= 0) {
            comparacoes_insertion++;
            if (strcmp(componentes[j].tipo, chave.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                j--;
            } else {
                break;
            }
        }
        componentes[j + 1] = chave;
    }
}

// Selection Sort por prioridade
void selectionSortPrioridade(Componente componentes[], int n) {
    comparacoes_selection = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes_selection++;
            if (componentes[j].prioridade < componentes[min_idx].prioridade) {
                min_idx = j;
            }
        }
        // Troca o elemento mínimo com o primeiro elemento
        Componente temp = componentes[min_idx];
        componentes[min_idx] = componentes[i];
        componentes[i] = temp;
    }
}

// Busca por nome 
int buscaBinariaPorNome(Componente componentes[], int n, char nome[]) {
    comparacoes_busca = 0;
    int esquerda = 0;
    int direita = n - 1;
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        comparacoes_busca++;
        
        int comparacao = strcmp(componentes[meio].nome, nome);
        
        if (comparacao == 0) {
            return meio; // Componente encontrado
        } else if (comparacao < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    return -1; // Componente nao encontrado
}

// Mostrar componentes
void mostrarComponentes(Componente componentes[], int n) {
    printf("\n=== COMPONENTES DA TORRE ===\n");
    printf("%-20s %-15s %-10s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("------------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("%-20s %-15s %-10d\n", 
               componentes[i].nome, 
               componentes[i].tipo, 
               componentes[i].prioridade);
    }
}

// Medir tempo de execucao
void medirTempo(void (*algoritmo)(Componente[], int), Componente componentes[], int n, char* nomeAlgoritmo) {
    // Cria uma copia do array para nao modificar o original
    Componente* copia = malloc(n * sizeof(Componente));
    memcpy(copia, componentes, n * sizeof(Componente));
    
    clock_t inicio = clock();
    algoritmo(copia, n);
    clock_t fim = clock();
    
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("Tempo de execucao do %s: %.6f segundos\n", nomeAlgoritmo, tempo);
    
    free(copia);
}

// Mostrar estatisticas de comparacoes
void mostrarEstatisticas() {
    printf("\n=== ESTATISTICAS DE COMPARACOES ===\n");
    printf("Bubble Sort (nome): %d comparacoes\n", comparacoes_bubble);
    printf("Insertion Sort (tipo): %d comparacoes\n", comparacoes_insertion);
    printf("Selection Sort (prioridade): %d comparacoes\n", comparacoes_selection);
    printf("Busca Binaria: %d comparacoes\n", comparacoes_busca);
}

int main() {
    Componente componentes[20];
    int quantidade = 0;
    int opcao;
    int ordenado_por_nome = 0; // Flag para verificar se esta ordenado por nome
    
    printf("=== SISTEMA DE MONTAGEM DA TORRE DE FUGA ===\n");
    printf("A safe zone esta se fechando! Organize seus componentes!\n\n");
    
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Cadastrar componentes\n");
        printf("2. Ordenar por nome (Bubble Sort)\n");
        printf("3. Ordenar por tipo (Insertion Sort)\n");
        printf("4. Ordenar por prioridade (Selection Sort)\n");
        printf("5. Buscar componente por nome (Busca Binaria)\n");
        printf("6. Mostrar componentes\n");
        printf("7. Mostrar estatisticas de desempenho\n");
        printf("8. Medir tempos de execucao\n");
        printf("0. Sair e ativar torre\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                cadastrarComponentes(componentes, &quantidade);
                ordenado_por_nome = 0; // Reset da flag ao cadastrar novos
                break;
                
            case 2:
                if (quantidade > 0) {
                    bubbleSortNome(componentes, quantidade);
                    printf("Componentes ordenados por nome!\n");
                    mostrarComponentes(componentes, quantidade);
                    ordenado_por_nome = 1;
                } else {
                    printf("Nenhum componente cadastrado!\n");
                }
                break;
                
            case 3:
                if (quantidade > 0) {
                    insertionSortTipo(componentes, quantidade);
                    printf("Componentes ordenados por tipo!\n");
                    mostrarComponentes(componentes, quantidade);
                    ordenado_por_nome = 0;
                } else {
                    printf("Nenhum componente cadastrado!\n");
                }
                break;
                
            case 4:
                if (quantidade > 0) {
                    selectionSortPrioridade(componentes, quantidade);
                    printf("Componentes ordenados por prioridade!\n");
                    mostrarComponentes(componentes, quantidade);
                    ordenado_por_nome = 0;
                } else {
                    printf("Nenhum componente cadastrado!\n");
                }
                break;
                
            case 5:
                if (quantidade > 0) {
                    if (!ordenado_por_nome) {
                        printf("AVISO: Para busca binaria, e necessario ordenar por nome primeiro!\n");
                        printf("Deseja ordenar agora? (s/n): ");
                        char resposta;
                        scanf("%c", &resposta);
                        limparBuffer();
                        
                        if (resposta == 's' || resposta == 'S') {
                            bubbleSortNome(componentes, quantidade);
                            ordenado_por_nome = 1;
                        } else {
                            break;
                        }
                    }
                    
                    printf("Digite o nome do componente a buscar: ");
                    char nomeBusca[30];
                    fgets(nomeBusca, 30, stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = 0;
                    
                    int posicao = buscaBinariaPorNome(componentes, quantidade, nomeBusca);
                    
                    if (posicao != -1) {
                        printf("\n COMPONENTE ENCONTRADO! \n");
                        printf("Nome: %s\n", componentes[posicao].nome);
                        printf("Tipo: %s\n", componentes[posicao].tipo);
                        printf("Prioridade: %d\n", componentes[posicao].prioridade);
                        printf("\nTorre destravada! Preparando ativacao...\n");
                    } else {
                        printf("Componente '%s' nao encontrado!\n", nomeBusca);
                    }
                } else {
                    printf("Nenhum componente cadastrado!\n");
                }
                break;
                
            case 6:
                if (quantidade > 0) {
                    mostrarComponentes(componentes, quantidade);
                } else {
                    printf("Nenhum componente cadastrado!\n");
                }
                break;
                
            case 7:
                mostrarEstatisticas();
                break;
                
            case 8:
                if (quantidade > 0) {
                    printf("\n=== MEDICAO DE TEMPOS ===\n");
                    medirTempo(bubbleSortNome, componentes, quantidade, "Bubble Sort");
                    medirTempo(insertionSortTipo, componentes, quantidade, "Insertion Sort");
                    medirTempo(selectionSortPrioridade, componentes, quantidade, "Selection Sort");
                } else {
                    printf("Nenhum componente cadastrado!\n");
                }
                break;
                
            case 0:
                printf("\n=== ATIVACAO DA TORRE ===\n");
                if (quantidade > 0) {
                    printf("Componentes organizados: %d\n", quantidade);
                    printf("Iniciando sequencia de fuga...\n");
                    printf(" FOGUETE ATIVADO! ESCAPE BEM-SUCEDIDO! \n");
                } else {
                    printf("Nenhum componente disponivel. Missao fracassada!\n");
                }
                break;
                
            default:
                printf("Opcao invalida!\n");
        }
        
    } while (opcao != 0);
    
    return 0;
}