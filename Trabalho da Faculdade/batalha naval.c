#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5
#define NUM_SHIPS 3

// Tabuleiros
char playerBoard[SIZE][SIZE];
char computerBoard[SIZE][SIZE];
char displayBoard[SIZE][SIZE]; // Mostra o progresso do jogador

// Funções
void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '-';
        }
    }
}

void printBoard(char board[SIZE][SIZE]) {
    printf("  ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void placeShips(char board[SIZE][SIZE], int isPlayer) {
    int placedShips = 0;
    while (placedShips < NUM_SHIPS) {
        int x, y;
        if (isPlayer) {
            printf("Digite as coordenadas para o navio %d (linha e coluna): ", placedShips + 1);
            scanf("%d %d", &x, &y);
        } else {
            x = rand() % SIZE;
            y = rand() % SIZE;
        }

        if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] == '-') {
            board[x][y] = 'S';
            placedShips++;
            if (isPlayer) {
                printf("Navio %d colocado em (%d, %d)\n", placedShips, x, y);
            }
        } else if (isPlayer) {
            printf("Coordenadas inválidas ou já ocupadas! Tente novamente.\n");
        }
    }
}

int isHit(char board[SIZE][SIZE], int x, int y) {
    if (board[x][y] == 'S') {
        board[x][y] = 'H';  // Acerto
        return 1;
    } else if (board[x][y] == '-') {
        board[x][y] = 'M';  // Erro
        return 0;
    }
    return 0;
}

int computerAttack(char board[SIZE][SIZE]) {
    int x, y;
    do {
        x = rand() % SIZE;
        y = rand() % SIZE;
    } while (board[x][y] == 'H' || board[x][y] == 'M');  // Evita ataques repetidos
    printf("Computador ataca (%d, %d)... ", x, y);
    if (isHit(board, x, y)) {
        printf("Acertou!\n");
        return 1;
    } else {
        printf("Errou!\n");
        return 0;
    }
}

int playerAttack(int x, int y) {
    if (displayBoard[x][y] == 'H' || displayBoard[x][y] == 'M') {
        printf("Você já tentou essa posição! Tente outra.\n");
        return -1;
    }
    if (isHit(computerBoard, x, y)) {
        printf("Acertou!\n");
        displayBoard[x][y] = 'H';
        return 1;
    } else {
        printf("Errou!\n");
        displayBoard[x][y] = 'M';
        return 0;
    }
}

int countHits(char board[SIZE][SIZE]) {
    int hits = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 'H') {
                hits++;
            }
        }
    }
    return hits;
}

int main() {
    srand(time(NULL));

    // Inicialização dos tabuleiros
    initializeBoard(playerBoard);
    initializeBoard(computerBoard);
    initializeBoard(displayBoard);

    printf("Bem-vindo ao jogo Batalha Naval!\n");

    // Posicionamento dos navios do jogador e do computador
    printf("Posicione seus navios:\n");
    placeShips(playerBoard, 1);
    printf("O computador está posicionando seus navios...\n");
    placeShips(computerBoard, 0);

    int playerHits = 0, computerHits = 0;

    // Loop do jogo
    while (playerHits < NUM_SHIPS && computerHits < NUM_SHIPS) {
        int x, y;

        // Turno do jogador
        printf("\nTabuleiro do computador:\n");
        printBoard(displayBoard);

        do {
            printf("Insira as coordenadas para atacar (linha e coluna): ");
            scanf("%d %d", &x, &y);
            if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
                printf("Coordenadas inválidas! Tente novamente.\n");
                continue;
            }
        } while (playerAttack(x, y) == -1);

        // Atualiza acertos do jogador
        if (displayBoard[x][y] == 'H') { // Foi substituido a linha de código if (playerAttack(x, y) == 1) {playerHits++;} para está linha de código atual, não dava certo antes pois chamava duas vezes a variavel playerAttack
            playerHits++;
        }

        // Verificação se o jogador venceu
        if (playerHits == NUM_SHIPS) {
            printf("Parabéns! Você destruiu todos os navios inimigos!\n");
            break;
        }

        // Turno do computador
        if (computerAttack(playerBoard)) {
            computerHits++;
        }

        // Verificação se o computador venceu
        if (computerHits == NUM_SHIPS) {
            printf("O computador destruiu todos os seus navios! Você perdeu.\n");
            break;
        }
    }

    return 0;
}
