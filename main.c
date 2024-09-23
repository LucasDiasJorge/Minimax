#include <stdio.h>

#define PLAYER_X 1   // Jogador X (Maximiza)
#define PLAYER_O -1  // Jogador O (Minimiza)
#define EMPTY 0

// Função para mostrar o tabuleiro
void printBoard(int board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == PLAYER_X) printf(" X ");
            else if (board[i][j] == PLAYER_O) printf(" O ");
            else printf(" . ");
        }
        printf("\n");
    }
}

// Verifica se alguém ganhou o jogo
int checkWinner(int board[3][3]) {
    for (int i = 0; i < 3; i++) {
        // Verifica as linhas e colunas
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != EMPTY)
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != EMPTY)
            return board[0][i];
    }
    // Verifica as diagonais
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != EMPTY)
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != EMPTY)
        return board[0][2];

    // Se ninguém ganhou, retorna 0
    return 0;
}

// Verifica se o tabuleiro está cheio
int isFull(int board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                return 0;
    return 1;
}

// Função Minimax para escolher a melhor jogada
int minimax(int board[3][3], int depth, int isMaximizing) {
    int winner = checkWinner(board);
    if (winner != 0) return winner;  // Retorna +1 para vitória do X, -1 para vitória do O
    if (isFull(board)) return 0;      // Empate

    if (isMaximizing) {
        int bestScore = -2;  // Inicializa com um valor baixo
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_X;
                    int score = minimax(board, depth + 1, 0);  // Alterna para minimizar
                    board[i][j] = EMPTY;
                    if (score > bestScore) {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 2;  // Inicializa com um valor alto
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_O;
                    int score = minimax(board, depth + 1, 1);  // Alterna para maximizar
                    board[i][j] = EMPTY;
                    if (score < bestScore) {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
}

// Escolhe a melhor jogada para o jogador X (Maximiza)
void bestMove(int board[3][3]) {
    int bestScore = -2;
    int move[2] = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = PLAYER_X;
                int score = minimax(board, 0, 0);  // Avalia o tabuleiro com minimax
                board[i][j] = EMPTY;
                if (score > bestScore) {
                    bestScore = score;
                    move[0] = i;
                    move[1] = j;
                }
            }
        }
    }

    board[move[0]][move[1]] = PLAYER_X;  // Faz a melhor jogada
}

int main() {
    int board[3][3] = {
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY}
    };

    // Jogador humano é o O, computador (X) usa Minimax
    int player = PLAYER_O;

    while (1) {
        printBoard(board);
        if (checkWinner(board) != 0) {
            printf("Jogador %d venceu!\n", checkWinner(board));
            break;
        }
        if (isFull(board)) {
            printf("Empate!\n");
            break;
        }

        if (player == PLAYER_X) {
            printf("Computador está fazendo sua jogada...\n");
            bestMove(board);
            player = PLAYER_O;
        } else {
            int row, col;
            printf("Sua vez (jogador O). Informe a linha e coluna: ");
            scanf("%d %d", &row, &col);
            if (board[row][col] == EMPTY) {
                board[row][col] = PLAYER_O;
                player = PLAYER_X;
            } else {
                printf("Posição inválida! Tente novamente.\n");
            }
        }
    }

    return 0;
}
