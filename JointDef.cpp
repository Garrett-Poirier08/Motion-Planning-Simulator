#include <iostream>
#include <string>
#include "Position.cpp"
class jointDef {
    public:
        std::int32_t JointID;//the ID of the joint
        double lenght;//the lenght of the joint connected after the joint
        double angle;//the angle of the joint is set too
        Position pos;//the position of the joint in 3D space
        
    jointDef(std::int32_t JointID, double lenght, double angle, Position pos) {
        this->JointID = JointID;
        this->lenght = lenght;
        this->angle = angle;
        this->pos = pos;
    }
    jointDef() {
        this->JointID = 0;
        this->lenght = 0;
        this->angle = 0;
        this->pos = Position();
    }
    public:
    std::int32_t getJointID() {
        return this->JointID;
    }
    double getLenght() {
        return this->lenght;
    }
    double getAngle() {
        return this->angle;
    }
    Position getPos() {
        return this->pos;
    }


};
