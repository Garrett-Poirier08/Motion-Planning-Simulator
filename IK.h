#pragma once

#include <vector>

class IK{
    public:
        float targetX;
        float targetY;
        float targetZ;
        float targetPitch;
        float targetYaw;
        float baseX;
        float baseY;
        float baseZ;
        std::vector<float> jointLengths; // Vector to store the lengths of the joints
        std::vector<float> x; // Vector to store x positions of the joints after transformation
        std::vector<float> y;// Vector to store y positions of the joints after transformation
        std::vector<float> z;// Vector to store z positions of the joints after transformation

        IK(float x, float y, float z, float pitch, float yaw);

        //defualt constructor assumes end efffector aproches target from above, so pitch is -90 degrees in radians, yaw and roll are 0 degrees in radians
        IK(float x, float y, float z);

        IK();

        void SetPos(float x, float y, float z);

        //in terms of the law of cosines formula a is lenght2 and b is length1
        void SetLengths(float length1, float length2, float endEffectorLength);

        /**
         * Solves the inverse kinematics for the robotic arm
         * can only be done on an IK Object
         * @return A vector containing the joint angles
         * @throws std::runtime_error if jointLengths hasn't been set, or if the
         *         target is unreachable given the current link lengths
         */
        std::vector<float> SolveIK();

        void transformToVector();

        float GetTargetX() const;
        float GetTargetY() const;
        float GetTargetZ() const;
        float GetTargetPitch() const;
        float GetTargetYaw() const;
        float GetBaseX() const;
        float GetBaseY() const;
        float GetBaseZ() const;
        std::vector<float> GetJointLengths() const;
        std::vector<float> GetX() const;
        std::vector<float> GetY() const;
        std::vector<float> GetZ() const;
};