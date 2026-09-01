#include <iostream>
#include <string>
#include "Position.cpp"
#include "Points.cpp"
#include <vector>
class Lines {
    public:
        std::int32_t LineID;//the ID of the line
        std::string name;//the name of the line
        Points points;//the points of the line
        /**
         * Lines class constructor used to initialize the line with its ID, name, and points.
         * The constructor takes in three parameters: LineID, name, and points.
         * The LineID parameter represents the ID of the line, the name parameter represents the name of the line, and the points parameter represents the points of the line.
         * @param LineID The ID of the line
         * @param name The name of the line
         * @param points The points of the line
         */
        Lines(std::int32_t LineID, std::string name, Points points) {
            this->LineID = LineID;
            this->name = name;
            this->points = points;
        }
        /**
         * Lines no argument constructor used to initialize the line with its ID, name, and points.
         */
        Lines() {
            this->LineID = 0;
            this->name = "";
            this->points = {};
        }
        public:
        std::int32_t getLineID() {
            return this->LineID;
        }
        std::string getName() {
            return this->name;
        }
        Points getPoints() {
            return this->points;
        }
        std::vector<Position> getPositions() {
            std::vector<Position> positions;
            positions.push_back(this->points.getPos());
            return positions;
        }
        /**
         * drawLine method used to generate a line between two points in 3D space. The method takes in two Points objects, start and end, 
         * and generates a vector of Points objects that represent the line between the two points. 
         * The method uses linear interpolation to generate the points along the line cause i dont like matrices.
         * @param start The starting point of the line
         * @param end The ending point of the line
         * @return A vector of Points objects that represent the line between the two points
         */
        std::vector<Points> drawLine(Points start, Points end) {
            std::vector<Points> linePoints;
            for(double_t t = 0; t <= 1; t += 0.01) {
                std::double_t x = (1 - t) * start.getPos().getX() + t * end.getPos().getX();
                std::double_t y = (1 - t) * start.getPos().getY() + t * end.getPos().getY();
                std::double_t z = (1 - t) * start.getPos().getZ() + t * end.getPos().getZ();
                std::double_t roll = (1 - t) * start.getPos().getRoll() + t * end.getPos().getRoll();
                std::double_t pitch = (1 - t) * start.getPos().getPitch() + t * end.getPos().getPitch();
                std::double_t yaw = (1 - t) * start.getPos().getYaw() + t * end.getPos().getYaw();
                Position pos(x, y, z, roll, pitch, yaw);
                Points point(0, pos, "");
                linePoints.push_back(point);
            }
            return linePoints;
        }
};