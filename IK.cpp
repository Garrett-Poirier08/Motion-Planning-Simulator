#include "Position.cpp"
#include <vector>

class IK{
    public:
        float targetX;
        float targetY;
        float targetZ;
        float targetPitch;
        float targetYaw;
        float targetRoll;
        std::vector<Position> jointPositions; // Vector to store the positions of the joints


        IK(float x, float y, float z, float pitch, float yaw, float roll) {
            this->targetX = x;
            this->targetY = y;
            this->targetZ = z;
            this->targetPitch = pitch;
            this->targetYaw = yaw;
            this->targetRoll = roll;
        }
        //defualt constructor assumes end efffector aproches target from above, so pitch is -90 degrees in radians, yaw and roll are 0 degrees in radians
        IK(float x, float y, float z){
            this->targetX = x;
            this->targetY = y;
            this->targetZ = z;
            this->targetPitch = -1.5708f; // -90 degrees in radians
            this->targetYaw = 0.0f;
            this->targetRoll = 0.0f;
        }
        IK() {
            this->targetX = 0.0f;
            this->targetY = 0.0f;
            this->targetZ = 0.0f;
            this->targetPitch = 0.0f;
            this->targetYaw = 0.0f;
            this->targetRoll = 0.0f;
        }
        void Solve(Position joint1, Position joint2, Position joint3, Position joint4, Position joint5, Position joint6){

        }

    
};