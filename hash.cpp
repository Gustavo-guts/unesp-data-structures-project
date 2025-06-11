#include "hash.h"
#include <iostream>
#include <cmath>

HashTable::HashTable() {
    for (int i = 0; i < TAM; i++) table[i] = nullptr;
}

int HashTable::hash(float chave) {
    return static_cast<int>(chave) % TAM;
}

void HashTable::insert(SensorData s) {
    int idx = hash(s.stator_winding);
    SensorData* novo = new SensorData(s);
    novo->next = table[idx];
    table[idx] = novo;
}

void HashTable::remove(float stator_winding) {
    int idx = hash(stator_winding);
    SensorData* atual = table[idx];
    SensorData* anterior = nullptr;
    while (atual != nullptr && atual->stator_winding != stator_winding) {
        anterior = atual;
        atual = atual->next;
    }
    if (atual != nullptr) {
        if (anterior == nullptr) table[idx] = atual->next;
        else anterior->next = atual->next;
        delete atual;
    }
}

SensorData* HashTable::search(float sw) {
    int idx = hash(sw);
    SensorData* atual = table[idx];
    while (atual != nullptr) {
        if (atual->stator_winding == sw) return atual;
        atual = atual->next;
    }
    return nullptr;
}


//Estatísticas
void HashTable::imprimirMedia() {
    int count = 0;
    float soma = 0;
    for (int i = 0; i < TAM; i++) {
        SensorData* atual = table[i];
        while (atual != nullptr) {
            soma += atual->stator_winding;
            count++;
            atual = atual->next;
        }
    }
    std::cout << "Média stator_winding: " << (count ? soma / count : 0) << std::endl;
}

void HashTable::classificarDados() {
    for (int i = 0; i < TAM; i++) {
        SensorData* atual = table[i];
        while (atual != nullptr) {
            float t = atual->stator_winding;
            std::string c = (t < 70) ? "Normal" : (t < 90) ? "Alerta" : "Crítico";
            std::cout << t << " → " << c << std::endl;
            atual = atual->next;
        }
    }
}

void HashTable::filtrarCoolantAlta(float limite) {
    for (int i = 0; i < TAM; i++) {
        SensorData* atual = table[i];
        while (atual != nullptr) {
            if (atual->coolant > limite)
                std::cout << "Coolant: " << atual->coolant << " Torque: " << atual->torque << std::endl;
            atual = atual->next;
        }
    }
}




