#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

struct SensorData {
    float torque;
    float ambient;
    float coolant;
    float motor_speed;
    float stator_yoke;
    float stator_winding;
};

#endif
