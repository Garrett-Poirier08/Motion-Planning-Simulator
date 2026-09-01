#include <iostream>
#include <string>
#include "Position.cpp"

class Points {
    public:
        std::int32_t PointID;//the ID of the point
        Position pos;//the position of the point in 3D space
        std::string name;//the name of the point

        /**
         * Points class constructor used to initialize the position of a point in 3D space, and as a point used for generating a path or target for joint or end effector to reach.
         * @param PointID The ID of the point
         * @param pos The position of the point in 3D space
         * @param name The name of the point may remove latter becuase is kind of redundant with the ID, but for now it is useful for debugging and testing
         */
        Points(std::int32_t PointID, Position pos, std::string name) {
            this->PointID = PointID;
            this->pos = pos;
            this->name = name;
        }
        /**
         * Points no argument constructor used to initialize the position of a point in 3D space.
         */
        Points() {
            this->PointID = 0;
            this->pos = Position();
            this->name = "";
        }
        public:
        std::int32_t getPointID() {
            return this->PointID;
        }
        Position getPos() {
            return this->pos;
        }
        std::string getName() {
            return this->name;
        }
};