#ifndef PHYSICS_H
#define PHYSICS_H

// check for collisions
// Robot
extern struct
{
    // This variable stores the radius of our wheels in cm
    float WHEEL_RADIUS;
    // This variable stores the distance between the center of the wheels in cm
    float TRACK;
    // This variable stores the distance between the ultrasonic sensor and the center of the robot in cm
    float SENSOR_DISTANCE;
    // This variable stores the speed at which wheels should rotate
    float WHEEL_TURN_SPEED;
    // This variable stores the acceleration at which wheels should rotate
    float WHEEL_ACCELERATION;
    // This variable stores the current orientation of the robot in degrees
    float ORIENTATION_ANGLE;
    // This variable stores the current location of the robot in x plane coordinates in cm
    float LOCATION_X_COORDINATE;
    // This variable stores the current location of the robot in z plane coordinates in cm
    float LOCATION_Z_COORDINATE;
} robot;

// Ball
extern struct
{
    // This variable stores the current location of the ball in x plane coordinates in cm
    float LOCATION_X_COORDINATE;
    // This variable stores the current location of the ball in z plane coordinates in cm
    float LOCATION_Z_COORDINATE;
    // This variable stores the current velocity of the ball in x plane coordinates in m/s
    float X_VELOCITY;
    // This variable stores the current velocity of the ball in x plane coordinates in m/s
    float Z_VELOCITY;
} ball;

#endif
