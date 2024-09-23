### 1. Definições Iniciais

```c
#define PLAYER_X 1   // Jogador X (Maximiza)
#define PLAYER_O -1  // Jogador O (Minimiza)
#define EMPTY 0      // Espaço vazio no tabuleiro
```
- Usamos `#define` para definir constantes:
  - `PLAYER_X`: Representa o jogador X, o computador (maximizador), com valor `1`.
  - `PLAYER_O`: Representa o jogador O, o jogador humano (minimizador), com valor `-1`.
  - `EMPTY`: Representa uma célula vazia no tabuleiro, com valor `0`.

### 2. Função `printBoard`

```c
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
```
- **Objetivo**: Imprime o tabuleiro 3x3 na tela de forma legível.
  - Percorre a matriz `board` e imprime `X`, `O` ou `.` dependendo se a célula contém `PLAYER_X`, `PLAYER_O` ou `EMPTY`.
  - Usa dois loops aninhados: o primeiro (`i`) para as linhas e o segundo (`j`) para as colunas.

### 3. Função `checkWinner`

```c
int checkWinner(int board[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != EMPTY)
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != EMPTY)
            return board[0][i];
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != EMPTY)
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != EMPTY)
        return board[0][2];
    return 0;
}
```
- **Objetivo**: Verifica se há um vencedor (alguém fez uma linha, coluna ou diagonal).
  - O loop percorre todas as linhas e colunas, verificando se todas as células contêm o mesmo valor (`X` ou `O`).
  - Também verifica as duas diagonais.
  - Retorna `1` (X venceu), `-1` (O venceu) ou `0` (ninguém venceu ainda).

### 4. Função `isFull`

```c
int isFull(int board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                return 0;
    return 1;
}
```
- **Objetivo**: Verifica se o tabuleiro está cheio (empate).
  - O loop percorre todas as células do tabuleiro. Se encontrar algum espaço vazio (`EMPTY`), retorna `0` (ainda há espaço).
  - Se não houver espaços vazios, retorna `1` (tabuleiro cheio).

### 5. Função `minimax`

```c
int minimax(int board[3][3], int depth, int isMaximizing) {
    int winner = checkWinner(board);
    if (winner != 0) return winner;  // Se há um vencedor, retorna +1 ou -1
    if (isFull(board)) return 0;      // Se empate, retorna 0

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
```
- **Objetivo**: O coração do algoritmo Minimax. Simula todas as jogadas possíveis e avalia cada jogada para decidir a melhor.
  - **Base da Recursão**:
    - Se há um vencedor (`checkWinner`), retorna `1` ou `-1`.
    - Se o tabuleiro está cheio (empate), retorna `0`.
  - **Maximizar (jogador X)**:
    - O jogador X tenta maximizar sua pontuação. Inicializamos o melhor resultado com um valor muito baixo (`-2`).
    - Para cada célula vazia, faz a jogada, chama `minimax` recursivamente, desfaz a jogada, e compara o resultado.
  - **Minimizar (jogador O)**:
    - O jogador O tenta minimizar a pontuação do adversário. O processo é análogo ao de maximizar, mas inicializamos com um valor alto (`2`).

### 6. Função `bestMove`

```c
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
```
- **Objetivo**: Escolhe a melhor jogada para o jogador X (computador).
  - Simula todas as jogadas possíveis e usa a função `minimax` para encontrar a jogada com o maior valor (`bestScore`).
  - Depois, faz a melhor jogada no tabuleiro.

### 7. Função `main`

```c
int main() {
    int board[3][3] = {
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY}
    };

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
```
- **Objetivo**: Controla o fluxo do jogo.
  - Inicializa o tabuleiro vazio e alterna as jogadas entre o jogador humano (O

) e o computador (X).
  - O computador usa a função `bestMove` para decidir sua jogada.