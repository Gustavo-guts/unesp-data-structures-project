#include "heap.h"
#include <iostream>
#include <cmath>

Heap::Heap() {
    tamanho = 0;
}

void Heap::troca(int a, int b) {
    SensorData temp = dados[a];
    dados[a] = dados[b];
    dados[b] = temp;
}

void Heap::heapifyUp(int idx) {
    while (idx > 0 && dados[idx].stator_winding < dados[(idx - 1) / 2].stator_winding) {
        troca(idx, (idx - 1) / 2);
        idx = (idx - 1) / 2;
    }
}

void Heap::heapifyDown(int idx) {
    int menor = idx;
    int esq = 2 * idx + 1;
    int dir = 2 * idx + 2;

    if (esq < tamanho && dados[esq].stator_winding < dados[menor].stator_winding)
        menor = esq;
    if (dir < tamanho && dados[dir].stator_winding < dados[menor].stator_winding)
        menor = dir;
    if (menor != idx) {
        troca(idx, menor);
        heapifyDown(menor);
    }
}

void Heap::insert(SensorData s) {
    dados[tamanho] = s;
    heapifyUp(tamanho);
    tamanho++;
}

void Heap::removeRaiz() {
    if (tamanho == 0) return;
    dados[0] = dados[tamanho - 1];
    tamanho--;
    heapifyDown(0);
}

SensorData* Heap::search(float sw) {
    for (int i = 0; i < tamanho; i++) {
        if (dados[i].stator_winding == sw)
            return &dados[i];
    }
    return nullptr;
}






//Estatísticas 
void Heap::imprimirMedia() {
    float soma = 0;
    for (int i = 0; i < tamanho; i++) soma += dados[i].stator_winding;
    std::cout << "Média stator_winding: " << (tamanho ? soma / tamanho : 0) << std::endl;
}

void Heap::classificarDados() {
    for (int i = 0; i < tamanho; i++) {
        float t = dados[i].stator_winding;
        std::string c = (t < 70) ? "Normal" : (t < 90) ? "Alerta" : "Crítico";
        std::cout << t << " → " << c << std::endl;
    }
}

void Heap::filtrarCoolantAlta(float limite) {
    for (int i = 0; i < tamanho; i++) {
        if (dados[i].coolant > limite)
            std::cout << "Coolant: " << dados[i].coolant << ", Torque: " << dados[i].torque << std::endl;
    }
}
