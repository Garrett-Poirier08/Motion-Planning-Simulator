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
        std::vector<float> jointLengths; // Vector to store the lengths of the joints


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
        void SetPos(Position joint1, Position joint2, Position joint3, Position endEffector){
            this-> jointPositions.clear();
            this-> jointPositions.push_back(joint1);
            this-> jointPositions.push_back(joint2);
            this-> jointPositions.push_back(joint3);
            this-> jointPositions.push_back(endEffector);
        }
        void SetLengths(float length1, float length2, float length3, float length4){
            this-> jointLengths.clear();
            this-> jointLengths.push_back(length1);
            this-> jointLengths.push_back(length2);
            this-> jointLengths.push_back(length3);
            this-> jointLengths.push_back(length4);
        }
        std::vector<float> SolveIK(){
            //need to find offset from target for end effector so I dont need to use matrix
            float offsetTargetX = this->targetX - (this->jointLengths[3] * cos(this->targetPitch) * cos(this->targetYaw));
            float offsetTargetY = this->targetY - (this->jointLengths[3] * cos(this->targetPitch) * sin(this->targetYaw));
            float offsetTargetZ = this->targetZ - (this->jointLengths[3] * sin(this->targetPitch));
            //now the rest of the ARM Calculations
            float dx = offsetTargetX - this->jointPositions[0].getX();
            float dy = offsetTargetY - this->jointPositions[0].getY();
            float dz = offsetTargetZ - this->jointPositions[0].getZ();
            //distance across the ground plane from the base to the target
            float distance = sqrt(dx * dx + dy * dy);

            float baseAngle = atan2(dy, dx);
            float a = this->jointLengths[0];
            float b = this->jointLengths[1];
            float c  = sqrt(dx * dx + dy * dy + dz * dz);
            float angleA = acos((b * b + c * c - a * a) / (2 * b * c));
            float angleB = acos((a * a + c * c - b * b) / (2 * a * c));
            float angleC = acos((a * a + b * b - c * c) / (2 * a * b));//not really needed but have it just i case
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
        std::vector<float> transformToVector(){
            std::vector<float> jointAngles = SolveIK();
            std::vector<float> jointVectorsX;
            std::vector<float> jointVectorsY;
            std::vector<float> jointVectorsZ;
            for(int i = 0; i < jointAngles.size(); i++){
                if(i==0){
                    jointVectorsX.push_back(this->jointPositions[0].getX());
                    jointVectorsY.push_back(this->jointPositions[0].getY());
                    jointVectorsZ.push_back(this->jointPositions[0].getZ());
                }
                else{
                    float x = jointVectorsX[i-1] + this->jointLengths[i-1] * cos(jointAngles[i]) * cos(jointAngles[0]);
                    float y = jointVectorsY[i-1] + this->jointLengths[i-1] * cos(jointAngles[i]) * sin(jointAngles[0]);
                    float z = jointVectorsZ[i-1] + this->jointLengths[i-1] * sin(jointAngles[i]);
                    jointVectorsX.push_back(x);
                    jointVectorsY.push_back(y);
                    jointVectorsZ.push_back(z);
                }
            }
            return jointVectorsX;
        }
        std::vector<Position> GetJointPositions(){
            return this->jointPositions;
        }
        std::vector<float> GetJointLengths(){
            return this->jointLengths;
        }

    
};