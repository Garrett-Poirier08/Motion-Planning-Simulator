#pragma once
#include "raylib.h"
#include <vector>

// Global list of points added through the GUI. Any other .cpp file that
// needs the points just does:
//     #include "PointStore.h"
//     ... use g_points, or the helper functions below ...
extern std::vector<Vector3> g_points;

// Becomes true once "Connect Points" is clicked. While true, the renderer
// draws a connected chain of vectors (P0->P1->P2->...) instead of loose dots.
extern bool g_pointsConnected;

// --- Helpers other files can call instead of touching g_points directly ---
void AddPoint(Vector3 point);
void RemovePoint(int index);
void ClearPoints();          // also resets g_pointsConnected to false
void SetPointsConnected(bool connected);
