#include <iostream>
#include <fstream>
#include <sstream>
#include "avl.h"
using namespace std;

int main() {
    AVLTree arvore;
    ifstream file("data/motor_dados_tratado.csv");
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    string linha;
    getline(file, linha); // pular cabeçalho
    int count = 0;

    // Inserir 10 registros na AVL
    while (getline(file, linha) && count < 10) {
        stringstream ss(linha);
        SensorData s;
        string valor;

        getline(ss, valor, ','); s.torque = stof(valor);
        getline(ss, valor, ','); s.ambient = stof(valor);
        getline(ss, valor, ','); s.coolant = stof(valor);
        getline(ss, valor, ','); s.motor_speed = stof(valor);
        getline(ss, valor, ','); s.stator_yoke = stof(valor);
        getline(ss, valor, ','); s.stator_winding = stof(valor);

        arvore.insert(s);
        count++;
    }

    cout << "\n--- In-Order ---\n";
    arvore.printInOrder();

    cout << "\n\n--- Busca ---\n";
    cout << "Buscando stator_winding = 1003: ";
    SensorData* encontrado = arvore.search(1003);
    if (encontrado)
        cout << "Encontrado: coolant = " << encontrado->coolant << endl;
    else
        cout << "Nao encontrado." << endl;

    cout << "\n--- Remoção ---\n";
    arvore.remove(1003);
    cout << "Removido stator_winding = 1003.\n";
    encontrado = arvore.search(1003);
    cout << (encontrado ? "Ainda existe." : "Remoção confirmada.") << endl;

    cout << "\n--- Média ---\n";
    arvore.imprimirMedia();

    cout << "\n--- Classificação ---\n";
    arvore.classificarDados();

    cout << "\n--- Filtrar Coolant > 65 ---\n";
    arvore.filtrarCoolantAlta(65.0);

    return 0;
}
