/**
 * @file PointStore.h
 * @brief Shared storage for the points entered through the GUI, where each
 *        point carries its own (x, y, z) position AND a pitch/roll
 *        orientation saved alongside it.
 *
 * WHY THIS EXISTS AS ITS OWN FILE
 * ---------------------------------
 * This data needs to be usable from MULTIPLE .cpp files in this project
 * (main.cpp for rendering/GUI, but also things like RoboticArm.cpp or
 * Path.c++ for whatever motion-planning logic consumes it). Putting it in
 * its own header/source pair, rather than as local variables inside
 * main(), means every file can share the exact same data just by including
 * this header.
 *
 * DATA MODEL
 * -----------
 * Each entry in g_points is a StoredPoint: a position PLUS the pitch/roll
 * that were typed into the GUI at the moment "Add Point" was clicked. This
 * is a change from an earlier version where pitch/roll were a single
 * separate "last simulated" value shared across all points — now every
 * point remembers its own orientation.
 *
 * HOW TO USE THIS FROM ANOTHER FILE
 * ------------------------------------
 *     #include "PointStore.h"
 *
 *     for (const StoredPoint& p : g_points) {
 *         // p.position.x / p.position.y / p.position.z
 *         // p.pitch, p.roll
 *     }
 *
 *     if (g_pointsConnected) {
 *         // g_points now represents an ordered chain
 *         // P0.position -> P1.position -> P2.position -> ...
 *     }
 *
 * HOW THE "extern" DECLARATIONS WORK
 * -------------------------------------
 * `extern` here only DECLARES that a global variable exists somewhere and
 * gives its type — it does NOT create storage for it. The actual variable
 * is defined exactly once, in PointStore.cpp. If PointStore.cpp isn't
 * listed in CMakeLists.txt's add_executable(), you'll get
 * "undefined symbol" linker errors, since the declaration exists but
 * nothing defines it.
 */

#pragma once
#include "raylib.h"
#include <vector>

/**
 * @brief One point as entered through the GUI: a 3D position plus the
 *        pitch/roll (in degrees) that were saved alongside it.
 */
struct StoredPoint {
    Vector3 position;
    float pitch; ///< degrees
    float roll;  ///< degrees
};

/**
 * @brief All points currently entered through the GUI, in the order they
 *        were added.
 *
 * When g_pointsConnected is true, adjacent entries' `.position` fields
 * (g_points[i].position and g_points[i+1].position) represent the
 * endpoints of one vector in the connected chain — i.e. this list doubles
 * as both "the set of points" and "the path through them".
 *
 * Defined in PointStore.cpp.
 */
extern std::vector<StoredPoint> g_points;

/**
 * @brief Whether the points in g_points should currently be rendered as a
 *        connected chain of vectors (true) or as loose, unconnected dots
 *        (false).
 *
 * Becomes true when the user clicks "Connect Points", and is reset back to
 * false automatically whenever the point list changes (a point is added or
 * removed) via AddPoint()/RemovePoint()/ClearPoints(), so a stale chain is
 * never shown after the underlying points have changed.
 *
 * Defined in PointStore.cpp.
 */
extern bool g_pointsConnected;

/**
 * @brief Appends a new point (with its own pitch/roll) to the end of g_points.
 *
 * Does NOT automatically reset g_pointsConnected — callers that want the
 * "adding a point invalidates the current chain" behavior (as the GUI does)
 * should call SetPointsConnected(false) themselves afterward.
 *
 * @param point World-space (x, y, z) position to add.
 * @param pitch Pitch angle in degrees to save alongside this point.
 * @param roll  Roll angle in degrees to save alongside this point.
 */
void AddPoint(Vector3 point, float pitch, float roll);

/**
 * @brief Removes the point at the given position in g_points, if valid.
 *
 * Silently does nothing if `index` is out of range, rather than crashing.
 *
 * NOTE: if points are also saved/mirrored somewhere else (a file, another
 * list, etc.), that cleanup does NOT happen automatically here — see the
 * "TODO: hook up removal from other saved-point storage here" comment at
 * the call site in main.cpp's GUI panel code.
 *
 * @param index Zero-based position of the point to remove (as shown in the
 *              GUI list, e.g. "P0", "P1", ...).
 */
void RemovePoint(int index);

/**
 * @brief Removes all points and resets the connected state.
 */
void ClearPoints();

/**
 * @brief Sets whether g_points should be rendered as a connected vector chain.
 *
 * @param connected True to draw the points as a connected chain, false to
 *                  draw them as individual, unconnected points.
 */
void SetPointsConnected(bool connected);