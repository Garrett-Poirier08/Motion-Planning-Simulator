/**
 * @file PointStore.cpp
 * @brief Definitions for the globals and helper functions declared in
 *        PointStore.h. See that header for the full usage explanation.
 *
 * Keep the logic in here intentionally tiny and boring — this is meant to
 * be a thin, predictable shared data layer, not a place for point/IK
 * processing logic. Anything more complex belongs in its own file that
 * #includes "PointStore.h" and reads/writes these globals.
 */

#include "PointStore.h"

std::vector<StoredPoint> g_points;
bool g_pointsConnected = false;

void AddPoint(Vector3 point, float pitch, float roll) {
    g_points.push_back(StoredPoint{ point, pitch, roll });
}

void RemovePoint(int index) {
    // Bounds-checked on purpose: silently ignoring an invalid index is
    // safer for a shared global than letting an out-of-range erase() call
    // invoke undefined behavior.
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