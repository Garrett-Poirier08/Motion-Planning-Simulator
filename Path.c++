#include <iostream>
#include <string>
#include "Position.cpp"
#include "Points.cpp"
#include "Lines.cpp"
#include <list>
#include <vector>
#include <cmath>
class Path {
    public:
        std::int32_t PathID;//the ID of the path
        std::string name;//the name of the path
        std::double_t maxSpeed;//the max speed of the path
        std::double_t maxAccel;//the max acceleration of the path
        std::list<Lines> lines;//the points of the path
        /**
         * Path class constructor used to initialize the path with its ID, name, and points. 
         * The constructor takes in three parameters: PathID, name, and points. 
         * The PathID parameter represents the ID of the path, the name parameter represents the name of the path, 
         * and the points parameter represents the points of the path.
         * @param PathID The ID of the path
         * @param name The name of the path
         * @param maxSpeed The max speed of the path
         * @param maxAccel The max acceleration of the path
         * @param points The points of the path
         */
        Path(std::int32_t PathID, std::string name, std::double_t maxSpeed, std::double_t maxAccel, std::list<Lines> lines) {
            this->PathID = PathID;
            this->name = name;
            this->maxSpeed = maxSpeed;
            this->maxAccel = maxAccel;
            this->lines = lines;
        }
        /**
         * Path no argument constructor used to initialize the path with its ID, name, and points. 
         */
        Path() {
            this->PathID = 0;
            this->name = "";
            this->maxSpeed = 0.0;
            this->maxAccel = 0.0;
            this->lines = {};

        }
        public:
        std::int32_t getPathID() {
            return this->PathID;
        }
        std::string getName() {
            return this->name;
        }
        std::list<Lines> getLines() {
            return this->lines  ;
        }
        std::double_t getMaxSpeed() {
            return this->maxSpeed;
        }
        std::double_t getMaxAccel() {
            return this->maxAccel;
        }
        std::vector<Position> getPositions() {
            std::vector<Position> positions;
            for (auto line : this->lines) {
                auto linePositions = line.getPositions();
                positions.insert(positions.end(), linePositions.begin(), linePositions.end());
            }
            return positions;
        }
        std::vector<Lines> DrawPath(std::vector<Position> positions) {
            std::vector<Lines> lines;
            for (size_t i = 0; i < positions.size() - 1; i++) {
                Points startPoint(0, positions[i], "");
                Points endPoint(0, positions[i + 1], "");
                Lines line(0, "", startPoint);
                auto linePoints = line.drawLine(startPoint, endPoint);
                lines.push_back(line);
            }
            return lines;
        }
};