#include "raylib.h"
#include "bot.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int CELL_SIZE = 150;

enum GameState {
    PLAYER_TURN,
    BOT_TURN,
    GAME_OVER
};

bool CheckWinner(char board[3][3], char symbol) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {

        // Row
        if (board[i][0] == symbol &&
            board[i][1] == symbol &&
            board[i][2] == symbol) {
            return true;
        }

        // Column
        if (board[0][i] == symbol &&
            board[1][i] == symbol &&
            board[2][i] == symbol) {
            return true;
        }
    }

    // Main diagonal
    if (board[0][0] == symbol &&
        board[1][1] == symbol &&
        board[2][2] == symbol) {
        return true;
    }

    // Anti-diagonal
    if (board[0][2] == symbol &&
        board[1][1] == symbol &&
        board[2][0] == symbol) {
        return true;
    }

    return false;
}

bool IsDraw(char board[3][3]) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {

            if (board[row][col] == ' ') {
                return false;
            }
        }
    }

    return true;
}

void ResetBoard(char board[3][3]) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            board[row][col] = ' ';
        }
    }
}

int main() {

    InitWindow(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        "Tic-Tac-Toe"
    );

    SetTargetFPS(60);

    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    Bot bot;

    GameState gameState = PLAYER_TURN;

    char winner = ' ';
    bool draw = false;

    // Bot delay
    float botTimer = 0.0f;
    const float BOT_DELAY = 0.5f; // 500 milliseconds

    while (!WindowShouldClose()) {

        // =====================================================
        // PLAYER TURN
        // =====================================================

        if (gameState == PLAYER_TURN &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            Vector2 mouse = GetMousePosition();

            int col = (mouse.x - 75) / CELL_SIZE;
            int row = (mouse.y - 75) / CELL_SIZE;

            // Check whether click is inside the board
            if (row >= 0 && row < 3 &&
                col >= 0 && col < 3) {

                // Check whether cell is empty
                if (board[row][col] == ' ') {

                    // Player places X
                    board[row][col] = 'X';

                    // Check player win
                    if (CheckWinner(board, 'X')) {

                        winner = 'X';
                        gameState = GAME_OVER;
                    }

                    // Check draw
                    else if (IsDraw(board)) {

                        draw = true;
                        gameState = GAME_OVER;
                    }

                    // Bot's turn
                    else {

                        gameState = BOT_TURN;
                        botTimer = 0.0f;
                    }
                }
            }
        }


        // =====================================================
        // BOT TURN
        // =====================================================

        if (gameState == BOT_TURN) {

            // Increase timer every frame
            botTimer += GetFrameTime();

            // Wait 500 ms before bot moves
            if (botTimer >= BOT_DELAY) {

                bot.makeMove(board);

                // Check bot win
                if (CheckWinner(board, 'O')) {

                    winner = 'O';
                    gameState = GAME_OVER;
                }

                // Check draw
                else if (IsDraw(board)) {

                    draw = true;
                    gameState = GAME_OVER;
                }

                // Back to player
                else {

                    gameState = PLAYER_TURN;
                }

                botTimer = 0.0f;
            }
        }


        // =====================================================
        // GAME OVER MENU
        // =====================================================

        if (gameState == GAME_OVER &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            Vector2 mouse = GetMousePosition();

            // -------------------------
            // TRY AGAIN
            // -------------------------

            if (mouse.x >= 180 &&
                mouse.x <= 280 &&
                mouse.y >= 400 &&
                mouse.y <= 450) {

                ResetBoard(board);

                winner = ' ';
                draw = false;

                gameState = PLAYER_TURN;

                botTimer = 0.0f;
            }


            // -------------------------
            // EXIT
            // -------------------------

            if (mouse.x >= 320 &&
                mouse.x <= 420 &&
                mouse.y >= 400 &&
                mouse.y <= 450) {

                break;
            }
        }


        // =====================================================
        // DRAW
        // =====================================================

        BeginDrawing();

        ClearBackground(RAYWHITE);


        // =====================================================
        // BOARD LINES
        // =====================================================

        for (int i = 1; i < 3; i++) {

            // Horizontal lines
            DrawLine(
                75,
                75 + i * CELL_SIZE,
                525,
                75 + i * CELL_SIZE,
                BLACK
            );

            // Vertical lines
            DrawLine(
                75 + i * CELL_SIZE,
                75,
                75 + i * CELL_SIZE,
                525,
                BLACK
            );
        }


        // =====================================================
        // X / O
        // =====================================================

        for (int row = 0; row < 3; row++) {

            for (int col = 0; col < 3; col++) {

                int centerX =
                    75 +
                    col * CELL_SIZE +
                    CELL_SIZE / 2;

                int centerY =
                    75 +
                    row * CELL_SIZE +
                    CELL_SIZE / 2;


                // =================================================
                // X
                // =================================================

                if (board[row][col] == 'X') {

                    DrawLineEx(
                        {
                            static_cast<float>(centerX - 50),
                            static_cast<float>(centerY - 50)
                        },

                        {
                            static_cast<float>(centerX + 50),
                            static_cast<float>(centerY + 50)
                        },

                        10.0f,
                        RED
                    );


                    DrawLineEx(
                        {
                            static_cast<float>(centerX + 50),
                            static_cast<float>(centerY - 50)
                        },

                        {
                            static_cast<float>(centerX - 50),
                            static_cast<float>(centerY + 50)
                        },

                        10.0f,
                        RED
                    );
                }


                // =================================================
                // O
                // =================================================

                else if (board[row][col] == 'O') {

                    DrawRing(
                        {
                            static_cast<float>(centerX),
                            static_cast<float>(centerY)
                        },

                        45.0f,
                        55.0f,

                        0.0f,
                        360.0f,

                        32,

                        BLUE
                    );
                }
            }
        }


        // =====================================================
        // PLAYER / BOT TEXT
        // =====================================================

        if (gameState != GAME_OVER) {

            DrawText(
                "You: X",
                100,
                550,
                25,
                RED
            );

            DrawText(
                "Bot: O",
                400,
                550,
                25,
                BLUE
            );
        }


        // =====================================================
        // BOT THINKING
        // =====================================================

        if (gameState == BOT_TURN) {

            DrawText(
                "Bot is thinking...",
                195,
                550,
                25,
                BLACK
            );
        }


        // =====================================================
        // GAME OVER
        // =====================================================

        if (gameState == GAME_OVER) {

            // Dark overlay
            DrawRectangle(
                0,
                0,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                Fade(BLACK, 0.5f)
            );


            // Menu box
            DrawRectangle(
                120,
                170,
                360,
                300,
                RAYWHITE
            );


            // =================================================
            // RESULT
            // =================================================

            if (draw) {

                DrawText(
                    "Draw!",
                    255,
                    210,
                    40,
                    BLACK
                );
            }

            else {

                DrawText(
                    TextFormat(
                        "%s Wins!",
                        winner == 'X'
                            ? "You"
                            : "Bot"
                    ),

                    210,
                    210,
                    40,
                    BLACK
                );
            }


            // =================================================
            // TRY AGAIN
            // =================================================

            DrawText(
                "Try again?",
                225,
                280,
                30,
                BLACK
            );


            // YES button
            DrawRectangle(
                180,
                400,
                100,
                50,
                GREEN
            );

            DrawText(
                "YES",
                210,
                415,
                20,
                WHITE
            );


            // EXIT button
            DrawRectangle(
                320,
                400,
                100,
                50,
                RED
            );

            DrawText(
                "EXIT",
                345,
                415,
                20,
                WHITE
            );
        }


        EndDrawing();
    }


    // =====================================================
    // CLOSE
    // =====================================================

    CloseWindow();

    return 0;
}