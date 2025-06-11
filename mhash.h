#ifndef MHASH_H
#define MHASH_H

#include "sensor_data.h" // Certifique-se de que SensorData está declarado aqui

class MelhorHashTable {
private:
    SensorData** table;
    int capacidade;
    int tamanho;

    int hash(float key);
    float loadFactor();
    void resizeTable();

public:
    MelhorHashTable();
    ~MelhorHashTable();

    void insert(SensorData s);
    void remove(float sw);
    SensorData* search(float sw);
};
#endif 