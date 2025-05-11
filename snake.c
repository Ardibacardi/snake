#include "snake.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

struct Snake* CreateSnake(int initialLength, int startX, int startY) {
    struct Snake* snake = (struct Snake*)malloc(sizeof(struct Snake));
    if (!snake) {
        fprintf(stderr, "Failed to allocate memory for snake\n");
        return NULL;
    }

    snake->positions = (struct Vector2Int*)malloc(sizeof(struct Vector2Int) * initialLength);
    if (!snake->positions) {
        fprintf(stderr, "Failed to allocate memory for snake positions\n");
        free(snake);
        return NULL;
    }

    for (int i = 0; i < initialLength; i++) {
        snake->positions[i].x = startX;
        snake->positions[i].y = startY;
    }
    snake->snakeLength = initialLength;
    snake->direction.x = 1; // Initial direction to the right
    snake->direction.y = 0;

    return snake;
}

struct Food* CreateFood(int screenWidth, int screenHeight) {
    struct Food* food = (struct Food*)malloc(sizeof(struct Food));
    if (!food) {
        fprintf(stderr, "Failed to allocate memory for food\n");
        return NULL;
    }

    food->position.x = GetRandomValue(0, screenWidth / 20 - 1);
    food->position.y = GetRandomValue(0, screenHeight / 20 - 1);

    return food;
}

void MoveSnake(struct Snake* snake, int newX, int newY) {
    // Move the snake by updating its head position
    for (int i = snake->snakeLength - 1; i > 0; i--) {
        snake->positions[i] = snake->positions[i - 1];
    }
    snake->positions[0].x = newX;
    snake->positions[0].y = newY;
}

void DrawSnake(struct Snake* snake) {
    for (int i = 0; i < snake->snakeLength; i++) {
        DrawRectangle(snake->positions[i].x * 20, snake->positions[i].y * 20, 20, 20, GREEN);
    }
}

void DrawFood(struct Food* food) {
    DrawRectangle(food->position.x * 20, food->position.y * 20, 20, 20, RED);
}

void FreeSnake(struct Snake* snake) {
    if (snake) {
        free(snake->positions);
        free(snake);
    }
}
void UpdateSnakeDirection(struct Snake* snake) {
    // Update the snake's direction based on user input
    if (IsKeyDown(KEY_UP) && snake->direction.y == 0) {
        snake->direction.x = 0;
        snake->direction.y = -1;
    } else if (IsKeyDown(KEY_DOWN) && snake->direction.y == 0) {
        snake->direction.x = 0;
        snake->direction.y = 1;
    } else if (IsKeyDown(KEY_LEFT) && snake->direction.x == 0) {
        snake->direction.x = -1;
        snake->direction.y = 0;
    } else if (IsKeyDown(KEY_RIGHT) && snake->direction.x == 0) {
        snake->direction.x = 1;
        snake->direction.y = 0;
    }
}
void UpdateSnakePosition(struct Snake* snake, struct Food* food) {
    // Update the snake's position based on its direction
    int newX = snake->positions[0].x + snake->direction.x;
    int newY = snake->positions[0].y + snake->direction.y;

    // Check for wall collisions
    if (newX < 0 || newX >= GetScreenWidth() / 20 || newY < 0 || newY >= GetScreenHeight() / 20) {
        // Handle collision (e.g., reset game or end game)
        printf("Game Over! Snake hit the wall.\n");
        ResetGame(&snake, food); 
        return;
    }
    // Check for self-collision
    for (int i = 1; i < snake->snakeLength; i++) {
        if (newX == snake->positions[i].x && newY == snake->positions[i].y) {
            // Handle collision (e.g., reset game or end game)
            printf("Game Over! Snake collided with itself.\n");
            ResetGame(&snake, food); 
            return;
        }
    }

    MoveSnake(snake, newX, newY);
}

void CheckCollision(struct Snake* snake, struct Food* food) {
    // Check if the snake's head collides with the food
    if (snake->positions[0].x == food->position.x && snake->positions[0].y == food->position.y) {
        // Increase the snake's length
        struct Vector2Int* newPositions = (struct Vector2Int*)realloc(snake->positions, sizeof(struct Vector2Int) * (snake->snakeLength + 1));
        if (!newPositions) {
            fprintf(stderr, "Failed to reallocate memory for snake positions\n");
            exit(1);
        }
        snake->positions = newPositions;

        // Add a new segment to the snake
        snake->positions[snake->snakeLength] = snake->positions[snake->snakeLength - 1];
        snake->snakeLength++;

        // Update the food position
        UpdateFood(food, GetScreenWidth(), GetScreenHeight());
    }
}

void UpdateFood(struct Food* food, int screenWidth, int screenHeight) {
    // Update the food's position randomly
    food->position.x = GetRandomValue(0, screenWidth / 20 - 1);
    food->position.y = GetRandomValue(0, screenHeight / 20 - 1);

}
void UpdateSnake(struct Snake* snake, struct Food* food) {
    UpdateSnakeDirection(snake);
    UpdateSnakePosition(snake, food);
    CheckCollision(snake, food);
}

void ResetGame(struct Snake** snake, struct Food* food) {
    printf("Resetting game...\n");
    printf("Old snake pointer: %p\n", (void*)*snake);

    FreeSnake(*snake);
    free(food);

    // Display restart screen
    while (!IsKeyPressed(KEY_SPACE)) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Press SPACE to restart", GetScreenWidth() / 2 - MeasureText("Press SPACE to restart", 20) / 2, GetScreenHeight() / 2, 20, WHITE);
        EndDrawing();
    }

    *snake = CreateSnake(5, 0, 10);
    if (!(*snake)) {
        fprintf(stderr, "Failed to create snake\n");
        exit(1);
    }

    printf("New snake pointer: %p\n", (void*)*snake);

    UpdateFood(food, GetScreenWidth(), GetScreenHeight());

}