//
// Created by shourya on 30/10/24.
//

#pragma once
#include <raylib.h>
#include <vector>

class Player {
public:

    int x, y;
    float timeLastUpdate;
    int speed;
    float pixel_width, pixel_height;
    Color snake_body_color;
    Color snake_outline_color;
    int gridWidth;

    bool dead = false;

    enum Direction {
        UP = 0,
        LEFT = 1,
        RIGHT = 2,
        DOWN = 3
    };

    struct Point {
        Rectangle rect;
        Direction dir;
    };

    std::vector<int> keyQueue;

    std::vector<Point> points;

    Player(int x, int y, int speed, int gridWidth, float width, float height, Color snake_body_color, Color snake_outline_color);
    ~Player() {
        UnloadSound(pointSound);
    }

    void Update();
    void Draw();
    void AddPoint();

    Sound pointSound = LoadSound("../assets/point.mp3");
};
