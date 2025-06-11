#include "fenwick.h"
#include <cmath>

FenwickTree::FenwickTree() {
    n = 0;
    for (int i = 0; i < MAX; i++) tree[i] = 0;
}

int FenwickTree::lsb(int i) {
    return i & -i;
}

void FenwickTree::insert(SensorData s) {
    dados[n] = s;
    float val = s.stator_winding;
    int i = n + 1;
    while (i < MAX) {
        tree[i] += val;
        i += lsb(i);
    }
    n++;
}

float FenwickTree::prefixSum(int i) {
    float soma = 0;
    i++;
    while (i > 0) {
        soma += tree[i];
        i -= lsb(i);
    }
    return soma;
}

void FenwickTree::removeLast() {
    if (n == 0) return;
    float val = dados[n - 1].stator_winding;
    int i = n;
    while (i < MAX) {
        tree[i] -= val;
        i += lsb(i);
    }
    n--;
}

SensorData* FenwickTree::search(float sw) {
    for (int i = 0; i < n; i++) {
        if (dados[i].stator_winding == sw)
            return &dados[i];
    }
    return nullptr;
}



//Estatística

void FenwickTree::imprimirMedia() {
    float soma = prefixSum(n - 1);
    std::cout << "Média: " << (n ? soma / n : 0) << std::endl;
}

void FenwickTree::classificarDados() {
    for (int i = 0; i < n; i++) {
        float t = dados[i].stator_winding;
        std::string c = (t < 70) ? "Normal" : (t < 90) ? "Alerta" : "Crítico";
        std::cout << t << " → " << c << std::endl;
    }
}

void FenwickTree::filtrarCoolantAlta(float limite) {
    for (int i = 0; i < n; i++) {
        if (dados[i].coolant > limite)
            std::cout << "Coolant: " << dados[i].coolant << ", Torque: " << dados[i].torque << std::endl;
    }
}
