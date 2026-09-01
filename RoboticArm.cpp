#include <iostream>
#include <string>
#include "Position.cpp"
#include "JointDef.cpp"
#include "Points.cpp"
#include <list>
class RoboticArm {
    public:
        std::int32_t ArmID;//the ID of the robotic arm
        std::string name;//the name of the robotic arm
        std::list<jointDef> joints;//the joints of the robotic arm
        std::list<Points> points;//the points of the robotic arm
        /**
         * RoboticArm class constructor used to initialize the robotic arm with its ID, name, joints, and points. 
         * The constructor takes in four parameters: ArmID, name, joints, and points. 
         * The ArmID parameter represents the ID of the robotic arm, the name parameter represents the name of the robotic arm, 
         * the joints parameter represents the joints of the robotic arm, and the points parameter represents the points of the robotic arm.
         * @param ArmID The ID of the robotic arm
         * @param name The name of the robotic arm
         * @param joints The joints of the robotic arm
         * @param points The points of the robotic arm
         */
        RoboticArm(std::int32_t ArmID, std::string name, std::list<jointDef> joints, std::list<Points> points) {
            this->ArmID = ArmID;
            this->name = name;
            this->joints = joints;
            this->points = points;
        }
        /**
         * RoboticArm no argument constructor used to initialize the robotic arm with its ID, name, joints, and points. 
         */
        RoboticArm() {
            this->ArmID = 0;
            this->name = "";
            this->joints = {};
            this->points = {};
        }
        public:
        std::int32_t getArmID() {
            return this->ArmID;
        }
        std::string getName() {
            return this->name;
        }
        std::list<jointDef> getJoints() {
            return this->joints;
        }
        std::list<Points> getPoints() {
            return this->points;
        }
};