struct Vector2Int {
    int x, y;
};

struct Snake {
    struct Vector2Int* positions;
    int snakeLength;
    struct Vector2Int direction;
};

struct Food {
    struct Vector2Int position;
};

struct Snake* CreateSnake(int initialLength, int startX, int startY);
struct Food* CreateFood(int screenWidth, int screenHeight);
void MoveSnake(struct Snake* snake, int newX, int newY);
void DrawSnake(struct Snake* snake);
void DrawFood(struct Food* food);
void FreeSnake(struct Snake* snake);
void UpdateSnakeDirection(struct Snake* snake);
void UpdateSnakePosition(struct Snake* snake, struct Food* food);
void UpdateSnake(struct Snake* snake, struct Food* food);
void UpdateFood(struct Food* food, int screenWidth, int screenHeight);
void CheckCollision(struct Snake* snake, struct Food* food);
void EndGame(struct Snake* snake, struct Food* food);
int GetScore(struct Snake* snake);