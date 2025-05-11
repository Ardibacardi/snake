#include <stdio.h>
#include <raylib.h>

int main() {
    // Initialize a window to ensure raylib is working
    InitWindow(800, 600, "raylib Test");

    if (IsWindowReady()) {
        printf("raylib is installed and working!\n");
    } else {
        printf("raylib is not installed or not working!\n");
    }

    CloseWindow(); // Close the window and clean up resources
    return 0;
}