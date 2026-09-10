#include <iostream>
#include <string>
#include "Position.cpp"
#include <list>
class RoboticArm {
    std::vector<Position> jointPositions; // Vector to store the positions of the joints
    public:
        //assums 6 dof arm
        RoboticArm();
};