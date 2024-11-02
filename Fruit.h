//
// Created by shourya on 30/10/24.
//

#pragma once
#include <memory>
#include <raylib.h>
#include <random>
#include "Player.h"

class Fruit {
public:
    Vector2 position{};

    Fruit(int width, int height, int gridWidth, int gridHeight, int gridPointLength, Player* player)
        : width(width),
          height(height),
          gridWidth(gridWidth),
          gridHeight(gridHeight),
          gridPointLength(gridPointLength),
          player(player)
    {
        RandomisePosition();
    }

    void Draw() const;
    void RandomisePosition();

    int width, height;
private:
    int gridWidth, gridHeight, gridPointLength;

    Player* player;
};
