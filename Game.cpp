//
// Created by shourya on 31/10/24.
//

#include "Game.h"

#include <raylib.h>

Game::Game() {
    GRID_WIDTH = 60;
    GRID_HEIGHT = 40;
    GRID_POINT_SIZE = 20;
    GRID_PIXEL_WIDTH = GRID_WIDTH * GRID_POINT_SIZE;
    GRID_PIXEL_HEIGHT = GRID_HEIGHT * GRID_POINT_SIZE;

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(GRID_PIXEL_WIDTH, GRID_PIXEL_HEIGHT, "SNAKE");
    InitAudioDevice();
    if (IsAudioDeviceReady()) {
        audioInitialised = true;
    }
    InitSnake();
    fruit = new Fruit(GRID_POINT_SIZE, GRID_POINT_SIZE, GRID_WIDTH, GRID_HEIGHT, GRID_POINT_SIZE, snake);

    fruit->RandomisePosition();
}

Game::~Game() {
    CloseAudioDevice();
    CloseWindow();
}

void Game::Loop() {
    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }
}

void Game::UpdateDrawFrame() {
    if (!audioInitialised) {
        InitAudioDevice();
        if (IsAudioDeviceReady()) {
            audioInitialised = true;
        } else {
            audioInitialised = false;
        }
    }

    if (!snake->dead) {
        snake->Update();
    }

    if (snake->dead) {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        std::string message = "SCORE: " + std::to_string(score);
        int fontSize = 40;
        int length = MeasureText(message.c_str(), 40);
        DrawText(message.c_str(), GRID_PIXEL_WIDTH/2 - length/2, GRID_PIXEL_HEIGHT/2 - 20, fontSize, WHITE);
        message = "PRESS ENTER TO PLAY AGAIN";
        length = MeasureText(message.c_str(), 40);
        DrawText(message.c_str(), GRID_PIXEL_WIDTH/2 - length/2, GRID_PIXEL_HEIGHT/2 + 30, fontSize, WHITE);
        message = "OR ESCAPE TO QUIT";
        length = MeasureText(message.c_str(), 40);
        DrawText(message.c_str(), GRID_PIXEL_WIDTH/2 - length/2, GRID_PIXEL_HEIGHT/2 + 80, fontSize, WHITE);
        // Get input
        if (IsKeyDown(KEY_ENTER)) {
            InitSnake();
            score = 0;
        }
        EndDrawing();
        return;
    }

    BeginDrawing();
    ClearBackground(BACKGROUND_COLOR);
    // Now draw grid lines
    for (int y = 0; y <= GRID_PIXEL_HEIGHT; y += GRID_POINT_SIZE) {
        DrawLine(0, y, GRID_PIXEL_WIDTH, y-1, BACKGROUND_LINES_COLOR);
    };
    for (int x = 0; x <= GRID_PIXEL_WIDTH; x += GRID_POINT_SIZE) {
        DrawLine(x, 0, x, GRID_PIXEL_HEIGHT, BACKGROUND_LINES_COLOR);
    };

    // Check for collisions
    if (CheckCollisionRecs(snake->points[0].rect, Rectangle {fruit->position.x, fruit->position.y, static_cast<float>(fruit->width), static_cast<float>(fruit->height)})) {
        // Update fruit position
        fruit->RandomisePosition();
        snake->AddPoint();
        score++;
    }

    // DRAWING
    snake->Draw();
    fruit->Draw();

    EndDrawing();
}

void Game::InitSnake() {
    snake = new Player(GRID_POINT_SIZE * std::round(static_cast<float>(GRID_WIDTH) / 2), GRID_POINT_SIZE * std::round(static_cast<float>(GRID_HEIGHT) / 2), 15, GRID_POINT_SIZE,
                                       GRID_POINT_SIZE, GRID_POINT_SIZE, SNAKE_COLOR, SNAKE_COLOR_OUTLINE);
}
