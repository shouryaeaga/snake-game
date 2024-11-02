//
// Created by shourya on 30/10/24.
//

#include "Fruit.h"

#include <algorithm>

int GenerateRandomInt(int min, int max);

void Fruit::Draw() const {
    DrawRectangle(position.x, position.y, width, height, WHITE);
}

void Fruit::RandomisePosition() {
    std::vector<Vector2> fruitPositions;
    for (int x = 0; x < gridWidth * gridPointLength; x += gridPointLength) {
        for (int y = 0; y < gridHeight * gridPointLength; y += gridPointLength) {
            for (auto & point : player->points) {
                if (point.rect.x == x && point.rect.y == y) {
                    continue;
                }
                fruitPositions.push_back(Vector2 {static_cast<float>(x), static_cast<float>(y)});
            }
        }
    }

    // Generate 2 random numbers
    Vector2 point = fruitPositions[GenerateRandomInt(0, fruitPositions.size()-1)];
    position = Vector2 {point.x, point.y};
}

int GenerateRandomInt(const int min, const int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dist(min, max);
    return dist(gen);
}
