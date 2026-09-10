
/**
 * Position class used to represent the position of a joint in 3D space, or to determine the orientation of a joint in 3D space. 
 * The class contains six member variables: x, y, z, pitch, yaw, and roll. The x, y, and z variables represent the position of the joint in 3D space, 
 * while the pitch, yaw, and roll variables represent the orientation of the joint in 3D space.
 */
class Position {
    public:
        float x=0.0f;//the x position of the joint
        float y=0.0f;//the y position of the joint
        float z=0.0f;//the z position of the joint
        float pitch=0.0f;//the pitch of the joint
        float yaw=0.0f;//the yaw of the joint
        float roll=0.0f;//the roll of the joint
        /**
         * Position class constructor used to initialize the position of a joint in 3D space, or to determine the orientation of a joint in 3D space. The constructor takes in six parameters: x, y, z, pitch, yaw, and roll. The x, y, and z parameters represent the position of the joint in 3D space, while the pitch, yaw, and roll parameters represent the orientation of the joint in 3D space.
         * @param x The x position of the joint
         * @param y The y position of the joint
         * @param z The z position of the joint
         * @param pitch The pitch of the joint
         * @param yaw The yaw of the joint
         * @param roll The roll of the joint
         */

        Position(float x, float y, float z, float pitch, float yaw, float roll) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->pitch = pitch;
            this->yaw = yaw;
            this->roll = roll;
        }
        Position() {
            this->x = 0.0f;
            this->y = 0.0f;
            this->z = 0.0f;
            this->pitch = 0.0f;
            this->yaw = 0.0f;
            this->roll = 0.0f;
        }
    
        
        /**
         * Position class getter methods.
         */
        float getX() {
            return this->x;
        }
        float getY() {
            return this->y;
        }
        float getZ() {
            return this->z;
        }
        float getPitch() {
            return this->pitch;
        }
        float getYaw() {
            return this->yaw;
        }
        float getRoll() {
            return this->roll;
        }
        /**
         * Position class setter methods.
         */
        void setX(float x) {
            this->x = x;
        }
        void setY(float y) {
            this->y = y;
        }
        void setZ(float z) {
            this->z = z;
        }
        void setPitch(float pitch) {
            this->pitch = pitch;
        }
        void setYaw(float yaw) {
            this->yaw = yaw;
        }
        void setRoll(float roll) {
            this->roll = roll;
        }
    
};
