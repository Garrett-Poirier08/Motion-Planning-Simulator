#include <iostream>
#include <string>
/**
 * Position class used to represent the position of a joint in 3D space, or to determine the orientation of a joint in 3D space. 
 * The class contains six member variables: x, y, z, pitch, yaw, and roll. The x, y, and z variables represent the position of the joint in 3D space, 
 * while the pitch, yaw, and roll variables represent the orientation of the joint in 3D space.
 */
class Position {
    public:
        std::double_t x;//the x position of the joint
        std::double_t y;//the y position of the joint
        std::double_t z;//the z position of the joint
        std::double_t pitch;//the pitch of the joint
        std::double_t yaw;//the yaw of the joint
        std::double_t roll;//the roll of the joint
        /**
         * Position class constructor used to initialize the position of a joint in 3D space, or to determine the orientation of a joint in 3D space. The constructor takes in six parameters: x, y, z, pitch, yaw, and roll. The x, y, and z parameters represent the position of the joint in 3D space, while the pitch, yaw, and roll parameters represent the orientation of the joint in 3D space.
         * @param x The x position of the joint
         * @param y The y position of the joint
         * @param z The z position of the joint
         * @param pitch The pitch of the joint
         * @param yaw The yaw of the joint
         * @param roll The roll of the joint
         */

        Position(std::double_t x, std::double_t y, std::double_t z, std::double_t pitch, std::double_t yaw, std::double_t roll) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->pitch = pitch;
            this->yaw = yaw;
            this->roll = roll;
        }
        /**
         * Position class constructor used to initialize the position of a joint in 3D space.
         * @param x The x position of the joint
         * @param y The y position of the joint
         * @param z The z position of the joint
         */
        Position(std::double_t x, std::double_t y, std::double_t z) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->pitch = 0;
            this->yaw = 0;
            this->roll = 0;
        }
        /**
         * Position class constructor used to initialize the position of a joint in 3D space.
         */
        Position() {
            this->x = 0;
            this->y = 0;
            this->z = 0;
            this->pitch = 0;
            this->yaw = 0;
            this->roll = 0;
        }
        /**
         * Position class getter methods.
         */
        std::double_t getX() {
            return this->x;
        }
        std::double_t getY() {
            return this->y;
        }
        std::double_t getZ() {
            return this->z;
        }
        std::double_t getPitch() {
            return this->pitch;
        }
        std::double_t getYaw() {
            return this->yaw;
        }
        std::double_t getRoll() {
            return this->roll;
        }
        /**
         * Position class setter methods.
         */
        void setX(std::double_t x) {
            this->x = x;
        }
        void setY(std::double_t y) {
            this->y = y;
        }
        void setZ(std::double_t z) {
            this->z = z;
        }
        void setPitch(std::double_t pitch) {
            this->pitch = pitch;
        }
        void setYaw(std::double_t yaw) {
            this->yaw = yaw;
        }
        void setRoll(std::double_t roll) {
            this->roll = roll;
        }
    
};
