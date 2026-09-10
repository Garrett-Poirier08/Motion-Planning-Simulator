#include <iostream>
#include <string>
#include <vector>

class ConvertCoordinates {
    public:
        /**
         * ConvertCoordinates class method used to convert a vector of Points objects from one coordinate system to another. The method takes in a vector of Points objects, and converts the coordinates of each point from the original coordinate system to the new coordinate system. The method uses a simple linear transformation to convert the coordinates, and returns a new vector of Points objects with the converted coordinates.
         * @param points The vector of Points objects to be converted
         * @return A new vector of Points objects with the converted coordinates
         */
        std::vector<float> convertCoordinates(float x, float y, float z) {
            // Convert from original coordinate system to new coordinate system
            float newX = y;
            float newY = z;
            float newZ = x;
            std::vector<float> convertedPoints;
            convertedPoints.push_back(newX);
            convertedPoints.push_back(newY);
            convertedPoints.push_back(newZ);
            return convertedPoints;
        }
};