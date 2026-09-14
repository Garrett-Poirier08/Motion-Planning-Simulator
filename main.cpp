// Vector3D GUI - accept (x,y,z) points plus a pitch/roll orientation, then
// connect them into a chain of vectors in 3D space on demand.
//
// Points live in PointStore.h/.cpp (g_points), so other files in this
// project (RoboticArm.cpp, Path.c++, etc.) can read/modify them too:
//     #include "PointStore.h"
//     for (const StoredPoint& p : g_points) { ... }

#include "raylib.h"
#include "raymath.h"
#include "rcamera.h" // CameraYaw / CameraPitch / CameraMoveToTarget live here, not in raylib.h

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "PointStore.h"
//#include "Position.cpp"
#include "ConvertCordnates.cpp"
#include "IK.cpp"
#include "Path.cpp"
#include <string>
#include <cstdio>
#include <cstring>

// A small fixed palette so each connected segment gets a distinct, readable color.
static Color NextColor(int index) {
    static const Color palette[] = {
        RED, GREEN, BLUE, ORANGE, PURPLE, GOLD,
        LIME, SKYBLUE, MAGENTA, MAROON, DARKGREEN, VIOLET
    };
    return palette[index % (int)(sizeof(palette) / sizeof(palette[0]))];
}

// Draws a vector as a cylindrical shaft + a cone arrowhead at the tip.
static void DrawArrow3D(Vector3 from, Vector3 to, Color color) {
    Vector3 dir = Vector3Subtract(to, from);
    float len = Vector3Length(dir);
    if (len < 0.0001f) {
        DrawSphere(to, 0.05f, color);
        return;
    }
    Vector3 dirNorm = Vector3Scale(dir, 1.0f / len);

    float headLen = fminf(0.35f, len * 0.25f); // arrowhead length scales with vector, capped
    float shaftLen = len - headLen;
    Vector3 headStart = Vector3Add(from, Vector3Scale(dirNorm, shaftLen));

    float shaftRadius = 0.025f;
    float headRadius = 0.09f;

    if (shaftLen > 0.001f) {
        DrawCylinderEx(from, headStart, shaftRadius, shaftRadius, 8, color);
    }
    DrawCylinderEx(headStart, to, headRadius, 0.0f, 12, color);
}

static void DrawAxes(float length) {
    // X - red, Y - green, Z - blue
    DrawArrow3D({0,0,0}, {length,0,0}, (Color){230,60,60,255});
    DrawArrow3D({0,0,0}, {0,length,0}, (Color){60,200,80,255});
    DrawArrow3D({0,0,0}, {0,0,length}, (Color){60,120,230,255});

}
/**takes target position and orientation of the end effector, base position, and lengths of the joints, then draws the arm in 3D space
 * @param x The x position of the target
 * @param y The y position of the target
 * @param z The z position of the target
 * @param pitch The pitch of the target
 * @param yaw The yaw of the target
 * @param Base The position of the base
 * @param Length1 The length of the first joint
 * @param Length2 The length of the second joint
 * @param Length3 The length of the third joint
 */
static void DrawArm(float x, float y, float z, float pitch,float yaw, float BaseX, float BaseY, float BaseZ, float Length1, float Length2, float Length3){
    IK arm(x,y,z,pitch,yaw);
    arm.SetPos(BaseX, BaseY, BaseZ);
    arm.SetLengths(Length1,Length2,Length3);
    arm.transformToVector();
    DrawCylinderEx({BaseX,BaseY,BaseZ},{arm.GetX()[1],arm.GetY()[1],arm.GetZ()[1]},0.05f,0.05f,8,(Color){150, 150, 150, 255});
    DrawCylinderEx({arm.GetX()[1],arm.GetY()[1],arm.GetZ()[1]},{arm.GetX()[2],arm.GetY()[2],arm.GetZ()[2]},0.05f,0.05f,8,(Color){150, 150, 150, 255});
}


int main() {
    const int screenWidth = 1200;
    const int screenHeight = 750;
    const int panelWidth = 300;

    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "MotionPlanningSimulator - point/vector viewer");
    SetTargetFPS(60);

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 8.0f, 8.0f, 8.0f };
    camera.target   = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up       = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy     = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Text box buffers for X, Y, Z input
    char bufX[32] = "x";
    char bufY[32] = "y";
    char bufZ[32] = "z";
    bool editX = false, editY = false, editZ = false;

    // Text box buffers for Pitch / Roll input - sit right under X/Y/Z and
    // get saved together with the point when "Add Point" is clicked.
    char bufPitch[32] = "0.0";
    char bufRoll[32] = "0.0";
    bool editPitch = false, editRoll = false;

    bool showGrid = true;
    bool showAxes = true;
    bool showLabels = true;
    

    while (!WindowShouldClose()) {
        //reset Camera to default position if R is pressed
        if(IsKeyPressed(KEY_R)) {
            camera.position = (Vector3){ 8.0f, 8.0f, 8.0f };
            camera.target   = (Vector3){ 0.0f, 0.0f, 0.0f };
            camera.up       = (Vector3){ 0.0f, 1.0f, 0.0f };
            camera.fovy     = 45.0f;
            camera.projection = CAMERA_PERSPECTIVE;
        }
        if(IsKeyDown(KEY_A)){
            camera.position.x += 0.5f;
            camera.target.x += 0.5f;
        }
        if(IsKeyDown(KEY_D)){
            camera.position.x -= 0.5f;
            camera.target.x -= 0.5f;
        }
        if(IsKeyDown(KEY_W)){
            camera.position.z += 0.5f;
            camera.target.z += 0.5f;
        }
        if(IsKeyDown(KEY_S)){
            camera.position.z -= 0.5f;
            camera.target.z -= 0.5f;
        }
        if(IsKeyDown(KEY_SPACE)){
            camera.position.y += 0.5f;
            camera.target.y += 0.5f;
        }
        if(IsKeyDown(KEY_LEFT_CONTROL)){
            camera.position.y -= 0.5f;
            camera.target.y -= 0.5f;
        }
        int sw = GetScreenWidth();
        int sh = GetScreenHeight();
        Rectangle panelRect = { (float)(sw - panelWidth), 0, (float)panelWidth, (float)sh };
        bool mouseOverPanel = CheckCollisionPointRec(GetMousePosition(), panelRect);

        // Only orbit/zoom the camera when the mouse isn't busy with the GUI panel
        if (!mouseOverPanel) {
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                Vector2 delta = GetMouseDelta();
                CameraYaw(&camera, -delta.x * 0.005f, true);
                CameraPitch(&camera, -delta.y * 0.005f, true, true, false);
            }
            float wheel = GetMouseWheelMove();
            if (wheel != 0) CameraMoveToTarget(&camera, -wheel * 0.8f);
        }

        BeginDrawing();
        ClearBackground((Color){ 245, 246, 248, 255 });

        BeginMode3D(camera);
            if (showGrid) DrawGrid(20, 1.0f);
            if (showAxes) DrawAxes(3.0f);

            if (g_pointsConnected && g_points.size() >= 2) {
                // Chain: P0 -> P1 -> P2 -> ... each segment its own color
                for (size_t i = 0; i + 1 < g_points.size(); i++) {
                    DrawArrow3D(g_points[i].position, g_points[i + 1].position, NextColor((int)i));
                }
                // Still mark each point so you can see where the chain bends
                for (auto& p : g_points) DrawSphere(p.position, 0.06f, DARKGRAY);
            } else {
                // Not connected yet: just show the raw points as dots
                for (auto& p : g_points) DrawSphere(p.position, 0.08f, GRAY);
            }
            //DrawArm({0,0,0,1.57079f,0,0}, {0,0,0,1.57079f,0,0}, {0,0,0,1.57079f,0,0}, {0,0,0,1.57079f,0,0}, {0,0,0,1.57079f,0,0}, {0,0,0,1.57079f,0,0}, 3.0f, 2.0f, 1.0f, 1.0f, 1.0f);
        EndMode3D();

        // Labels drawn in 2D space projected from 3D tip positions (stay readable, unlike 3D text)
        if (showLabels) {
            for (size_t i = 0; i < g_points.size(); i++) {
                Vector2 screenPos = GetWorldToScreen(g_points[i].position, camera);
                if (screenPos.x < sw - panelWidth) {
                    DrawText(TextFormat("P%d", (int)i), (int)screenPos.x + 6, (int)screenPos.y - 6, 16, DARKGRAY);
                }
            }
        }

        DrawFPS(10, sh - 24);
        DrawText("Right-drag: orbit   |   Wheel: zoom", 10, 10, 18, DARKGRAY);

        // ---------------- GUI PANEL ----------------
        GuiPanel(panelRect, "Point Controls");

        float px = panelRect.x + 15;
        float py = 40;
        float fieldW = panelWidth - 30;

        GuiLabel((Rectangle){ px, py, fieldW, 20 }, "New point (x, y, z):");
        py += 24;

        if (GuiTextBox((Rectangle){ px, py, fieldW, 28 }, bufX, sizeof(bufX), editX))
            editX = !editX;
        py += 34;
        if (GuiTextBox((Rectangle){ px, py, fieldW, 28 }, bufY, sizeof(bufY), editY))
            editY = !editY;
        py += 34;
        if (GuiTextBox((Rectangle){ px, py, fieldW, 28 }, bufZ, sizeof(bufZ), editZ))
            editZ = !editZ;
        py += 40;

        // Pitch / Roll sit right under X/Y/Z and get saved along with the
        // point below when "Add Point" is clicked - not a separate step.
        GuiLabel((Rectangle){ px, py, fieldW, 20 }, "Pitch / Roll (deg):");
        py += 24;

        if (GuiTextBox((Rectangle){ px, py, fieldW, 28 }, bufPitch, sizeof(bufPitch), editPitch))
            editPitch = !editPitch;
        py += 34;
        if (GuiTextBox((Rectangle){ px, py, fieldW, 28 }, bufRoll, sizeof(bufRoll), editRoll))
            editRoll = !editRoll;
        py += 40;

        if (GuiButton((Rectangle){ px, py, fieldW, 32 }, "Add Point")) {
            ///vars dont line up with name becuase textboxes are in wrong order, but the values are correct
            float x = (float)atof(bufY);
            float y = (float)atof(bufZ);
            float z = (float)atof(bufX);
            float pitch = (float)atof(bufPitch);
            float roll = (float)atof(bufRoll);
            AddPoint((Vector3){ x, y, z }, pitch, roll);
            // Adding a new point breaks any previously drawn chain until
            // "Connect Points" is pressed again.
            SetPointsConnected(false);
        }
        py += 40;

        bool connectPressed = GuiButton((Rectangle){ px, py, fieldW, 32 }, "Connect Points");
        if (connectPressed) {
            SetPointsConnected(true);
        }
        py += 38;

        if (GuiButton((Rectangle){ px, py, fieldW, 28 }, "Clear All")) {
            ClearPoints();
        }
        py += 40;

        GuiLine((Rectangle){ px, py, fieldW, 1 }, NULL);
        py += 12;

        GuiCheckBox((Rectangle){ px, py, 20, 20 }, "Show grid", &showGrid);
        py += 26;
        GuiCheckBox((Rectangle){ px, py, 20, 20 }, "Show axes", &showAxes);
        py += 26;
        GuiCheckBox((Rectangle){ px, py, 20, 20 }, "Show labels", &showLabels);
        py += 34;

        GuiLine((Rectangle){ px, py, fieldW, 1 }, NULL);
        py += 12;

        GuiLabel((Rectangle){ px, py, fieldW, 20 },
                 g_pointsConnected ? "Points (connected):" : "Points (not connected):");
        py += 24;

        // Simple list with remove buttons
        int removeIndex = -1;
        int defaultTextColor = GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL);
        for (int i = 0; i < (int)g_points.size(); i++) {
            if (py > sh - 40) break; // stop drawing if we run out of panel space
            Rectangle rowLabelRect = { px, py, fieldW - 34, 22 };
            Rectangle rowBtnRect   = { px + fieldW - 28, py, 28, 22 };

            Color rowColor = g_pointsConnected ? NextColor(i) : GRAY;
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(rowColor));
            GuiLabel(rowLabelRect, TextFormat("P%d: (%.1f,%.1f,%.1f) p%.0f/r%.0f", i,
                     g_points[i].position.x, g_points[i].position.y, g_points[i].position.z,
                     g_points[i].pitch, g_points[i].roll));
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, defaultTextColor);

            if (GuiButton(rowBtnRect, "X")) removeIndex = i;
            py += 26;
        }
        if (removeIndex >= 0) {
            // If points are also tracked/saved somewhere else besides
            // g_points (e.g. written to a file, mirrored into a separate
            // "confirmed path" list, or synced into another data
            // structure used by IK/RoboticArm/Path), remove or update that
            // storage HERE, before RemovePoint() erases it from g_points.
            // `removeIndex` is the position to remove; g_points[removeIndex]
            // still holds the actual point/pitch/roll at this point in code
            // if you need it (e.g. to find a matching entry elsewhere by value).
            //
            // TODO: hook up removal from other saved-point storage here.

            RemovePoint(removeIndex);

            SetPointsConnected(false); // chain changed, needs reconnecting
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}