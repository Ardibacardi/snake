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
    if (snake->snakeLength <= 0) {
        break;
    }
    
    BeginDrawing();
    ClearBackground(RAYWHITE);
    UpdateSnake(snake, food);
    DrawSnake(snake);
    DrawFood(food);
    DrawText(TextFormat("Score: %d", GetScore(snake)), 10, 10, 20, BLACK);

    EndDrawing();
}
}