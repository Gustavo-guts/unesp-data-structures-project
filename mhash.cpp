#include "mhash.h"
#include <iostream>

MelhorHashTable::MelhorHashTable() {
    capacidade = 101;
    tamanho = 0;
    table = new SensorData*[capacidade];
    for (int i = 0; i < capacidade; i++) table[i] = nullptr;
}

MelhorHashTable::~MelhorHashTable() {
    for (int i = 0; i < capacidade; i++) {
        if (table[i] != nullptr) delete table[i];
    }
    delete[] table;
}

int MelhorHashTable::hash(float key) {
    return ((int)(key * 1000)) % capacidade;
}

float MelhorHashTable::loadFactor() {
    return (float)tamanho / capacidade;
}

void MelhorHashTable::resizeTable() {
    int novaCapacidade = capacidade * 2;
    SensorData** novaTabela = new SensorData*[novaCapacidade];
    for (int i = 0; i < novaCapacidade; i++) novaTabela[i] = nullptr;

    for (int i = 0; i < capacidade; i++) {
        if (table[i] != nullptr) {
            int idx = ((int)(table[i]->stator_winding * 1000)) % novaCapacidade;
            while (novaTabela[idx] != nullptr)
                idx = (idx + 1) % novaCapacidade;
            novaTabela[idx] = table[i];
        }
    }

    delete[] table;
    table = novaTabela;
    capacidade = novaCapacidade;
}

void MelhorHashTable::insert(SensorData s) {
    if (loadFactor() >= 0.7)
        resizeTable();

    int idx = hash(s.stator_winding);
    while (table[idx] != nullptr)
        idx = (idx + 1) % capacidade;

    table[idx] = new SensorData(s);
    tamanho++;
}

SensorData* MelhorHashTable::search(float sw) {
    int idx = hash(sw);
    int start = idx;
    while (table[idx] != nullptr) {
        if (table[idx]->stator_winding == sw)
            return table[idx];
        idx = (idx + 1) % capacidade;
        if (idx == start) break;
    }
    return nullptr;
}

void MelhorHashTable::remove(float sw) {
    int idx = hash(sw);
    int start = idx;
    while (table[idx] != nullptr) {
        if (table[idx]->stator_winding == sw) {
            delete table[idx];
            table[idx] = nullptr;
            tamanho--;
            return;
        }
        idx = (idx + 1) % capacidade;
        if (idx == start) break;
    }
}
