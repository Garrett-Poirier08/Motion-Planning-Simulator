#include "PointStore.h"

std::vector<Vector3> g_points;
bool g_pointsConnected = false;

void AddPoint(Vector3 point) {
    g_points.push_back(point);
}

void RemovePoint(int index) {
    if (index >= 0 && index < (int)g_points.size()) {
        g_points.erase(g_points.begin() + index);
    }
}

void ClearPoints() {
    g_points.clear();
    g_pointsConnected = false;
}

void SetPointsConnected(bool connected) {
    g_pointsConnected = connected;
}
