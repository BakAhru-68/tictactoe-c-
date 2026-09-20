#include "raylib.h"
#include "game.h"

#include <string>

// ==========================================
// WINDOW SETTINGS
// ==========================================

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 700;

const int BOARD_SIZE = 600;
const int CELL_SIZE = BOARD_SIZE / 3;

// ==========================================
// GAME DELAYS
// ==========================================

const float BOT_DELAY = 0.5f;
const float PLAYER_DELAY = 0.15f;

float botTimer = 0.0f;
float playerTimer = 0.0f;

// ==========================================
// DRAW BOARD
// ==========================================

void DrawBoard(const TicTacToe& game) {

    ClearBackground(RAYWHITE);

    // ==========================================
    // DRAW GRID
    // ==========================================

    for (int i = 1; i < 3; i++) {

        DrawLine(
            i * CELL_SIZE,
            0,
            i * CELL_SIZE,
            BOARD_SIZE,
            BLACK
        );

        DrawLine(
            0,
            i * CELL_SIZE,
            BOARD_SIZE,
            i * CELL_SIZE,
            BLACK
        );
    }

    // ==========================================
    // DRAW X AND O
    // ==========================================

    for (int row = 0; row < 3; row++) {

        for (int col = 0; col < 3; col++) {

            char cell = game.getCell(row, col);

            int centerX =
                col * CELL_SIZE + CELL_SIZE / 2;

            int centerY =
                row * CELL_SIZE + CELL_SIZE / 2;

            // ==========================================
            // X - THICK
            // ==========================================

            if (cell == 'X') {

                int padding = 35;

                int x1 =
                    col * CELL_SIZE + padding;

                int y1 =
                    row * CELL_SIZE + padding;

                int x2 =
                    (col + 1) * CELL_SIZE - padding;

                int y2 =
                    (row + 1) * CELL_SIZE - padding;

                // Membuat X lebih tebal
                for (int thickness = -3;
                     thickness <= 3;
                     thickness++) {

                    DrawLine(
                        x1 + thickness,
                        y1,
                        x2 + thickness,
                        y2,
                        RED
                    );

                    DrawLine(
                        x2 + thickness,
                        y1,
                        x1 + thickness,
                        y2,
                        RED
                    );
                }
            }

            // ==========================================
            // O - THICK
            // ==========================================

            else if (cell == 'O') {

                // Beberapa lingkaran dengan radius berbeda
                // membuat O terlihat lebih tebal
                for (int radius = 42;
                     radius <= 48;
                     radius++) {

                    DrawCircleLines(
                        centerX,
                        centerY,
                        radius,
                        BLUE
                    );
                }
            }
        }
    }
}

// ==========================================
// DRAW STATUS
// ==========================================

void DrawStatus(const TicTacToe& game) {

    // ==========================================
    // GAME STILL RUNNING
    // ==========================================

    if (!game.isGameOver()) {

        std::string text = "Your turn: ";

        text += game.getCurrentSymbol();

        DrawText(
            text.c_str(),
            20,
            620,
            30,
            BLACK
        );

        return;
    }

    // ==========================================
    // PLAYER WINS
    // ==========================================

    if (game.getWinner() == 'X') {

        DrawText(
            "YOU WIN!",
            210,
            615,
            35,
            RED
        );
    }

    // ==========================================
    // BOT WINS
    // ==========================================

    else if (game.getWinner() == 'O') {

        DrawText(
            "BOT WINS!",
            205,
            615,
            35,
            BLUE
        );
    }

    // ==========================================
    // DRAW
    // ==========================================

    else {

        DrawText(
            "DRAW!",
            250,
            615,
            35,
            BLACK
        );
    }
}

// ==========================================
// DRAW GAME OVER MENU
// ==========================================

void DrawGameOverMenu() {

    // ==========================================
    // MENU BACKGROUND
    // ==========================================

    DrawRectangle(
        150,
        300,
        300,
        160,
        Fade(LIGHTGRAY, 0.95f)
    );

    // ==========================================
    // MENU BORDER
    // ==========================================

    DrawRectangleLines(
        150,
        300,
        300,
        160,
        BLACK
    );

    // ==========================================
    // TITLE
    // ==========================================

    DrawText(
        "PLAY AGAIN?",
        210,
        325,
        30,
        BLACK
    );

    // ==========================================
    // YES BUTTON
    // ==========================================

    DrawRectangle(
        185,
        380,
        90,
        45,
        GREEN
    );

    DrawText(
        "YES",
        207,
        391,
        20,
        BLACK
    );

    // ==========================================
    // EXIT BUTTON
    // ==========================================

    DrawRectangle(
        325,
        380,
        90,
        45,
        RED
    );

    DrawText(
        "EXIT",
        347,
        391,
        20,
        WHITE
    );
}

// ==========================================
// MAIN
// ==========================================

int main() {

    // ==========================================
    // INITIALIZE WINDOW
    // ==========================================

    InitWindow(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        "Tic Tac Toe"
    );

    SetTargetFPS(60);

    TicTacToe game;

    // ==========================================
    // GAME LOOP
    // ==========================================

    while (!WindowShouldClose()) {

        // ==========================================
        // UPDATE TIMERS
        // ==========================================

        float deltaTime = GetFrameTime();

        botTimer += deltaTime;
        playerTimer += deltaTime;

        // ==========================================
        // PLAYER TURN
        // ==========================================

        if (!game.isGameOver() &&
            game.getCurrentSymbol() == 'X' &&
            playerTimer >= PLAYER_DELAY &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            Vector2 mouse = GetMousePosition();

            int col =
                static_cast<int>(mouse.x) / CELL_SIZE;

            int row =
                static_cast<int>(mouse.y) / CELL_SIZE;

            // Pastikan klik berada di dalam board
            if (row >= 0 &&
                row < 3 &&
                col >= 0 &&
                col < 3) {

                if (game.makePlayerMove(row, col)) {

                    playerTimer = 0.0f;
                    botTimer = 0.0f;
                }
            }
        }

        // ==========================================
        // BOT TURN
        // ==========================================

        if (!game.isGameOver() &&
            game.getCurrentSymbol() == 'O' &&
            botTimer >= BOT_DELAY) {

            game.makeBotMove();

            botTimer = 0.0f;
            playerTimer = 0.0f;
        }

        // ==========================================
        // DRAW
        // ==========================================

        BeginDrawing();

        DrawBoard(game);

        DrawStatus(game);

        // ==========================================
        // GAME OVER
        // ==========================================

        if (game.isGameOver()) {

            DrawGameOverMenu();

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

                Vector2 mouse = GetMousePosition();

                // ==========================================
                // YES
                // ==========================================

                if (mouse.x >= 185 &&
                    mouse.x <= 275 &&
                    mouse.y >= 380 &&
                    mouse.y <= 425) {

                    game.reset();

                    botTimer = 0.0f;
                    playerTimer = 0.0f;
                }

                // ==========================================
                // EXIT
                // ==========================================

                else if (mouse.x >= 325 &&
                         mouse.x <= 415 &&
                         mouse.y >= 380 &&
                         mouse.y <= 425) {

                    break;
                }
            }
        }

        EndDrawing();
    }

    // ==========================================
    // CLOSE WINDOW
    // ==========================================

    CloseWindow();

    return 0;
}