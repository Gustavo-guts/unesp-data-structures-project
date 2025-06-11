#ifndef HEAP_H
#define HEAP_H

struct SensorData {
    float torque, ambient, coolant, motor_speed, stator_yoke, stator_winding;
};

class Heap {
private:
    static const int MAX = 1000;
    SensorData dados[MAX];
    int tamanho;

    void heapifyUp(int idx);
    void heapifyDown(int idx);
    void troca(int a, int b);

public:
    Heap();
    void insert(SensorData s);
    void removeRaiz();
    SensorData* search(float sw);
    void imprimirMedia();
    void classificarDados();
    void filtrarCoolantAlta(float limite);
};

#endif
