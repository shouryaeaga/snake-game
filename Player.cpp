//
// Created by shourya on 30/10/24.
//

#include "Player.h"

#include <iostream>

Player::Player(int x, int y, int speed, int gridWidth, float width, float height, Color snake_body_color, Color snake_outline_color) : x(x), y(y), speed(speed), gridWidth(gridWidth), pixel_width(width), pixel_height(height), snake_body_color(snake_body_color), snake_outline_color(snake_outline_color) {
    points.push_back(Point {{(float) x, (float) y, pixel_width, pixel_height}, RIGHT});
    for (int i = 0; i < 4; i++) {
        AddPoint();
    }
    timeLastUpdate = GetTime();
}

void Player::Update() {
    // Now check for inputs
    int key = GetKeyPressed();
    while (key != 0) {
        keyQueue.push_back(key);
        key = GetKeyPressed();
    }

    if (!keyQueue.empty()) {
        switch (keyQueue.front()) {
            case KEY_UP:
                if (points[0].dir != DOWN) {
                    points[0].dir = UP;
                }
                break;
            case KEY_DOWN:
                if (points[0].dir != UP) {
                    points[0].dir = DOWN;
                }
                break;
            case KEY_LEFT:
                if (points[0].dir != RIGHT) {
                    points[0].dir = LEFT;
                }
                break;
            case KEY_RIGHT:
                if (points[0].dir != LEFT) {
                    points[0].dir = RIGHT;
                }
                break;
            default: ;
        }

    }

    float time = GetTime();
    if (time - timeLastUpdate < 1.0/speed) {
        return;
    }

    if (!keyQueue.empty()) {
        keyQueue.erase(keyQueue.begin());
    }


    for (auto & point : points) {
        switch (point.dir) {
            case RIGHT:
                point.rect.x += gridWidth;
                break;
            case LEFT:
                point.rect.x -= gridWidth;
                break;
            case DOWN:
                point.rect.y += gridWidth;
                break;
            case UP:
                point.rect.y -= gridWidth;
                break;
        }
    }
    // Now set everything after the first point equal to the one before
    std::vector<Point> new_points;
    for (int i = 0; i < points.size(); i++) {
        if (i == 0) {
            new_points.push_back(points[i]);
            continue;
        }
        new_points.push_back(Point {points[i].rect, points[i-1].dir});
    }

    points = new_points;

    // Check whether the head is inside any of the body.
    for (int i = 1; i < points.size(); i++) {
        if (points[i].rect.y == points[0].rect.y && points[i].rect.x == points[0].rect.x) {
            // Colliding
            dead = true;
            std::cout << "Dead\n";
            break;
        }
    }

    // Check whether the head is out of the frame
    if (points[0].rect.x >= GetScreenWidth() || points[0].rect.x < 0 || points[0].rect.y >= GetScreenHeight() || points[0].rect.y < 0) {
        dead = true;
        std::cout << "Dead\n";
    }
    timeLastUpdate = GetTime();
}

void Player::Draw() {
    for (auto & point : points) {
        DrawRectangle(point.rect.x+2, point.rect.y+2, point.rect.width-2, point.rect.height-2, snake_body_color);
        DrawRectangleLinesEx({point.rect.x, point.rect.y, point.rect.width, point.rect.height}, 2.0, snake_outline_color);
    }
}

void Player::AddPoint() {
    // Last point
    switch (points.back().dir) {
        case RIGHT:
            points.push_back(Point {Rectangle {points.back().rect.x-pixel_width, points.back().rect.y, pixel_width, pixel_height}, RIGHT});
            break;
        case LEFT:
            points.push_back(Point {Rectangle {points.back().rect.x+pixel_width, points.back().rect.y, pixel_width, pixel_height}, LEFT});
            break;
        case UP:
            points.push_back(Point {Rectangle {points.back().rect.x, points.back().rect.y+pixel_height, pixel_width, pixel_height}, UP});
            break;
        case DOWN:
            points.push_back(Point {Rectangle {points.back().rect.x, points.back().rect.y-pixel_height, pixel_width, pixel_height}, DOWN});
            break;
    }
    std::cout << "Snake is now " << points.size() << "\n";

    PlaySound(pointSound);

}
