#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5  // Capacidade máxima da fila

// Estrutura que representa uma peça do Tetris
typedef struct {
    char nome; // Tipo da peça ('I', 'O', 'T', 'L')
    int id;    // Identificador único
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// ---------------- Funções da fila ----------------

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->total == MAX;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Insere uma peça no final da fila
int inserir(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia! Não é possível inserir nova peça.\n");
        return 0;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
    return 1;
}

// Remove a peça da frente da fila
int remover(Fila *f, Peca *p) {
    if (filaVazia(f)) {
        printf("Fila vazia! Não há peça para jogar.\n");
        return 0;
    }
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    return 1;
}

// Mostra o estado atual da fila
void mostrarFila(Fila *f) {
    printf("Fila de peças: ");
    if (filaVazia(f)) {
        printf("[vazia]");
    } else {
        int idx = f->inicio;
        for (int i = 0; i < f->total; i++) {
            printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
            idx = (idx + 1) % MAX;
        }
    }
    printf("\n");
}

// ---------------- Funções auxiliares ----------------

// Gera automaticamente uma nova peça
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    int sorteio = rand() % 4; // Sorteia uma das 4 peças
    Peca nova = {tipos[sorteio], id};
    return nova;
}

// ---------------- Programa principal ----------------
int main() {
    Fila f;
    inicializarFila(&f);

    srand(time(NULL)); // Inicializa a semente do rand()

    int contadorID = 0; // Controla os ids únicos das peças

    // Inicializa a fila com 5 peças
    for (int i = 0; i < MAX; i++) {
        inserir(&f, gerarPeca(contadorID++));
    }

    int opcao;
    do {
        mostrarFila(&f);

        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Peca jogada;
            if (remover(&f, &jogada)) {
                printf("Peça jogada: [%c %d]\n", jogada.nome, jogada.id);
            }
        } else if (opcao == 2) {
            if (inserir(&f, gerarPeca(contadorID))) {
                printf("Nova peça inserida com id %d.\n", contadorID);
                contadorID++;
            }
        } else if (opcao != 0) {
            printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    printf("Encerrando o jogo...\n");
    return 0;
}
