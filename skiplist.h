#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>
#include <cstdlib>
#include <ctime>

#define MAX_LEVEL 6

struct SensorData {
    float torque, ambient, coolant, motor_speed, stator_yoke, stator_winding;
};

struct SkipNode {
    SensorData data;
    SkipNode** forward;
    int level;
};

class SkipList {
private:
    SkipNode* head;
    int level;

    int randomLevel();
    SkipNode* createNode(SensorData data, int level);

public:
    SkipList();
    void insert(SensorData data);
    void remove(float stator_winding);
    SensorData* search(float stator_winding);
    void imprimirMedia();
    void classificarDados();
    void filtrarCoolantAlta(float limite);
};

#endif
