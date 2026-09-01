#include "raylib.h"
#include <math.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f }; // The object
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    float distance = 10.0f;
    float angleX = 0.0f;
    float angleY = 45.0f;
    

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 delta = GetMouseDelta();
            angleX -= delta.x * 0.005f;
            angleY += delta.y * 0.005f;

            // Limit vertical angle to avoid flipping
            if (angleY > 1.5f) angleY = 1.5f;
            if (angleY < -1.5f) angleY = -1.5f;
        }
        if (IsKeyPressed(KEY_SPACE)){
            distance += 0.5f;
            if (distance < 1.0f) distance = 1.0f; // Prevent camera from going too close
        }
        if (IsKeyPressed(KEY_LEFT_SHIFT)) {
            distance -= 0.5f;
            if (distance < 1.0f) distance = 1.0f; // Prevent camera from going too close
        }

        // Calculate new camera position using spherical coordinates
        camera.position.x = camera.target.x + distance * cosf(angleY) * sinf(angleX);
        camera.position.y = camera.target.y + distance * sinf(angleY);
        camera.position.z = camera.target.z + distance * cosf(angleY) * cosf(angleX);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                // for demonstration purposes to draw vectors that represent the path of the robotic arm
                DrawCylinderEx((Vector3){ -2.0f, 0.0f, 0.0f }, (Vector3){ 2.0f, 0.0f, 0.0f }, .1f,.1f,16, RED);
                DrawCylinderEx((Vector3){ 2.0f, 0.0f, 0.0f }, (Vector3){ 4.0f, 2.0f, 3.0f }, .1f,.1f,16, RED);
                
                //DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
                //DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
                

                DrawGrid(25, 1.0f);

            EndMode3D();

            DrawText("Welcome to the third dimension!", 10, 40, 20, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();

    

        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
// cmd + shif + p -> CMake: Run Without Debugging
// cmd + shif + p -> CMake: Debug