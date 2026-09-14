#include "IK.h"
#include <cmath>
#include <stdexcept>
#include <algorithm>

IK::IK(float x, float y, float z, float pitch, float yaw)
    : targetX(x), targetY(y), targetZ(z),
      targetPitch(pitch), targetYaw(yaw),
      baseX(0.0f), baseY(0.0f), baseZ(0.0f) {
}

//defualt constructor assumes end efffector aproches target from above, so pitch is -90 degrees in radians, yaw and roll are 0 degrees in radians
IK::IK(float x, float y, float z)
    : targetX(x), targetY(y), targetZ(z),
      targetPitch(-1.5708f), // -90 degrees in radians
      targetYaw(0.0f),
      baseX(0.0f), baseY(0.0f), baseZ(0.0f) {
}

IK::IK()
    : targetX(0.0f), targetY(0.0f), targetZ(0.0f),
      targetPitch(0.0f), targetYaw(0.0f),
      baseX(0.0f), baseY(0.0f), baseZ(0.0f) {
}

void IK::SetPos(float x, float y, float z){
    this->baseX = x;
    this->baseY = y;
    this->baseZ = z;
}

//in terms of the law of cosines formula a is lenght2 and b is length1
void IK::SetLengths(float length1, float length2, float endEffectorLength){
    this->jointLengths.clear();
    this->jointLengths.push_back(length1);
    this->jointLengths.push_back(length2);
    this->jointLengths.push_back(endEffectorLength);
}

std::vector<float> IK::SolveIK(){
    if(this->jointLengths.size() < 3){
        throw std::runtime_error("SolveIK: jointLengths not set, call SetLengths() first");
    }

    //need to find offset from target for end effector so I dont need to use matrix :)
    float offsetTargetX = this->targetX - (this->jointLengths[2] * cos(this->targetPitch) * cos(this->targetYaw));
    float offsetTargetY = this->targetY - (this->jointLengths[2] * cos(this->targetPitch) * sin(this->targetYaw));
    float offsetTargetZ = this->targetZ - (this->jointLengths[2] * sin(this->targetPitch));
    //now the rest of the ARM Calculations
    float dx = offsetTargetX - this->baseX;
    float dy = offsetTargetY - this->baseY;
    float dz = offsetTargetZ - this->baseZ;
    //distance across the ground plane from the base to the target
    float distance = sqrt(dx * dx + dy * dy);

    float baseAngle = atan2(dy, dx);
    float a = this->jointLengths[0];
    float b = this->jointLengths[1];
    float c  = sqrt(dx * dx + dy * dy + dz * dz);

    // Reachability check: with side lengths a, b, c a triangle can only
    // be formed if c <= a + b (and c >= |a - b|). Outside that range the
    // law-of-cosines argument falls outside [-1, 1] and acos() would
    // silently return NaN.
    if(c > a + b || c < std::fabs(a - b) || c == 0.0f){
        throw std::runtime_error("SolveIK: target is unreachable with the given joint lengths");
    }

    auto safeAcos = [](float value) -> float {
        // Clamp for safety against floating point drift even when the
        // reachability check above passes.
        value = std::clamp(value, -1.0f, 1.0f);
        return acos(value);
    };

    float angleA = safeAcos((b * b + c * c - a * a) / (2 * b * c));
    float angleB = safeAcos((a * a + c * c - b * b) / (2 * a * c));
    float angleC = safeAcos((a * a + b * b - c * c) / (2 * a * b)); //not really needed but have it just in case
    float joint1Angle = atan2(dz, distance) + angleA;
    float joint2Angle = angleB;
    float joint3Angle = this->targetPitch - joint1Angle - joint2Angle;
    std::vector<float> jointAngles;
    jointAngles.push_back(baseAngle);
    jointAngles.push_back(joint1Angle);
    jointAngles.push_back(joint2Angle);
    jointAngles.push_back(joint3Angle);
    return jointAngles;
}

void IK::transformToVector(){
    std::vector<float> jointAngles = SolveIK();
    this->x.clear();
    this->y.clear();
    this->z.clear();

    this->x.push_back(this->baseX);
    this->y.push_back(this->baseY);
    this->z.push_back(this->baseZ);

    float baseAngle = jointAngles[0];

    // jointAngles[1] (joint1Angle) is already an absolute angle measured
    // from horizontal, so link 1's orientation is exactly that.
    float link1Angle = jointAngles[1];

    // jointAngles[2] (joint2Angle) is the INTERIOR angle of the
    // triangle at joint 2, not an absolute orientation. To draw link 2
    // in space we need to accumulate it onto link 1's absolute angle.
    // Convention: a straight arm (angleB == pi) keeps the same
    // direction as link 1, so we subtract the deviation from straight.
    float link2Angle = link1Angle - (static_cast<float>(M_PI) - jointAngles[2]);

    // Link 3 (the end effector) is defined to finish at the target's
    // approach pitch by construction (see joint3Angle in SolveIK),
    // so its absolute orientation is simply the target pitch.
    float link3Angle = this->targetPitch;

    std::vector<float> absoluteAngles = { link1Angle, link2Angle, link3Angle };

    for(size_t i = 0; i < absoluteAngles.size(); i++){
        float length = this->jointLengths[i];
        float angle = absoluteAngles[i];
        float newX = this->x[i] + length * cos(angle) * cos(baseAngle);
        float newY = this->y[i] + length * cos(angle) * sin(baseAngle);
        float newZ = this->z[i] + length * sin(angle);
        this->x.push_back(newX);
        this->y.push_back(newY);
        this->z.push_back(newZ);
    }
}

float IK::GetTargetX() const { return this->targetX; }
float IK::GetTargetY() const { return this->targetY; }
float IK::GetTargetZ() const { return this->targetZ; }
float IK::GetTargetPitch() const { return this->targetPitch; }
float IK::GetTargetYaw() const { return this->targetYaw; }
float IK::GetBaseX() const { return this->baseX; }
float IK::GetBaseY() const { return this->baseY; }
float IK::GetBaseZ() const { return this->baseZ; }
std::vector<float> IK::GetJointLengths() const { return this->jointLengths; }
std::vector<float> IK::GetX() const { return this->x; }
std::vector<float> IK::GetY() const { return this->y; }
std::vector<float> IK::GetZ() const { return this->z; }