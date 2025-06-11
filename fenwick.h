#ifndef FENWICK_H
#define FENWICK_H

#include <iostream>

struct SensorData {
    float torque, ambient, coolant, motor_speed, stator_yoke, stator_winding;
};

class FenwickTree {
private:
    static const int MAX = 2000;
    float tree[MAX];
    SensorData dados[MAX];
    int n;

    int lsb(int i); // least significant bit

public:
    FenwickTree();
    void insert(SensorData s);
    float prefixSum(int i);
    void removeLast();
    SensorData* search(float sw);
    void imprimirMedia();
    void classificarDados();
    void filtrarCoolantAlta(float limite);
};

#endif
