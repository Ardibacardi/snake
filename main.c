#include "snake.h"
#include <raylib.h>
#include <stdio.h>

int main(void) {
InitWindow(800, 600, "snake");
SetTargetFPS(15);

struct Snake* snake = CreateSnake(5, 0, 10);
if (!snake) {
    fprintf(stderr, "Failed to create snake\n");
    return 1;
}
struct Food* food = CreateFood(GetScreenWidth(), GetScreenHeight());
if (!food) {
    fprintf(stderr, "Failed to create food\n");
    FreeSnake(snake);
    return 1;
}

while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    UpdateSnake(snake, food);
    DrawSnake(snake);
    DrawFood(food);

    EndDrawing();
}
}