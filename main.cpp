#include "raylib.h"

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Motion Planning Simulator");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Motion Planning Simulator", 440, 320, 28, DARKGRAY);
        DrawText("raylib configured successfully", 440, 360, 20, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
