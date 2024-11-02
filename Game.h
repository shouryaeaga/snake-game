//
// Created by shourya on 31/10/24.
//

#pragma once
#include "Fruit.h"
#include "Player.h"

class Game {
public:
    Game();

    ~Game();

    void Loop();

private:
    void UpdateDrawFrame();

    bool audioInitialised = false;

    int GRID_WIDTH;
    int GRID_HEIGHT;
    int GRID_POINT_SIZE;
    int GRID_PIXEL_WIDTH;
    int GRID_PIXEL_HEIGHT;

    int score = 0;

    Player* snake;
    Fruit* fruit;

    void InitSnake();

    Color BACKGROUND_LINES_COLOR {
        79,
        170,
        105,
        255
    };

    Color BACKGROUND_COLOR {
        33,
        255,
        96,
        255
    };

    Color SNAKE_COLOR {
        214,
        64,
        64,
        255
    };

    Color SNAKE_COLOR_OUTLINE {
        255,
        140,
        140,
        255
    };
};
