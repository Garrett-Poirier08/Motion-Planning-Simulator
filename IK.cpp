
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


        IK(float x, float y, float z, float pitch, float yaw) {
            this->targetX = x;
            this->targetY = y;
            this->targetZ = z;
            this->targetPitch = pitch;
            this->targetYaw = yaw;
            
        }
        //defualt constructor assumes end efffector aproches target from above, so pitch is -90 degrees in radians, yaw and roll are 0 degrees in radians
        IK(float x, float y, float z){
            this->targetX = x;
            this->targetY = y;
            this->targetZ = z;
            this->targetPitch = -1.5708f; // -90 degrees in radians
            this->targetYaw = 0.0f;
            
        }
        IK() {
            this->targetX = 0.0f;
            this->targetY = 0.0f;
            this->targetZ = 0.0f;
            this->targetPitch = 0.0f;
            this->targetYaw = 0.0f;
        }
        void SetPos(float x, float y, float z){
            this->baseX = x;
            this->baseY = y;
            this->baseZ = z;
        }
        //in terms of the law of cosines formula a is lenght2 and b is length1
        void SetLengths(float length1, float length2, float endEffectorLength){
            this-> jointLengths.clear();
            this-> jointLengths.push_back(length1);
            this-> jointLengths.push_back(length2);
            this-> jointLengths.push_back(endEffectorLength);
        }
        /**
         * Solves the inverse kinematics for the robotic arm
         * can only be done on an IK Object
         * @return A vector containing the joint angles
         */
        std::vector<float> SolveIK(){
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
        void transformToVector(){
            std::vector<float> jointAngles = SolveIK();
            this->x.clear();
            this->y.clear();
            this->z.clear();
            for(int i = 0; i < jointAngles.size(); i++){
                if(i==0){
                    this->x.push_back(this->baseX);
                    this->y.push_back(this->baseY);
                    this->z.push_back(this->baseZ);
                }
                else{
                    float x = this->x[i-1] + this->jointLengths[i-1] * cos(jointAngles[i]) * cos(jointAngles[0]);
                    float y = this->y[i-1] + this->jointLengths[i-1] * cos(jointAngles[i]) * sin(jointAngles[0]);
                    float z = this->z[i-1] + this->jointLengths[i-1] * sin(jointAngles[i]);
                    this -> x.push_back(x);
                    this -> y.push_back(y);
                    this -> z.push_back(z);
                }
            }
        }
        float GetTargetX(){
            return this->targetX;
        }
        float GetTargetY(){
            return this->targetY;
        }
        float GetTargetZ(){
            return this->targetZ;
        }
        float GetTargetPitch(){
            return this->targetPitch;
        }
        float GetTargetYaw(){
            return this->targetYaw;
        }
        float GetBaseX(){
            return this->baseX;
        }
        float GetBaseY(){
            return this->baseY;
        }
        float GetBaseZ(){
            return this->baseZ;
        }
        std::vector<float> GetJointLengths(){
            return this->jointLengths;
        }
        std::vector<float> GetX(){
            return this->x;
        }
        std::vector<float> GetY(){
            return this->y;
        }
        std::vector<float> GetZ(){
            return this->z;
        }

    
};