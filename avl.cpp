#include "avl.h"
#include <algorithm>
#include <iostream>

AVLTree::AVLTree() {
    root = nullptr;
}

void AVLTree::insert(const SensorData& s) {
  root = insert(root, s);


}

void AVLTree::insert(const SensorData& s) {
    root = insert(root, s);
}

No* AVLTree::insert(No* no, const SensorData& s) {
    // 1. Inserção padrão BST
    if (no == nullptr) {
        No* novo = new No;
        novo->data = s;
        novo->left = nullptr;
        novo->right = nullptr;
        novo->height = 1;
        return novo;
    }

    if (s.stator_winding < no->data.stator_winding) {
        no->left = insert(no->left, s);
    } else if (s.stator_winding > no->data.stator_winding) {
        no->right = insert(no->right, s);
    } else {
        return no; 
    }

    no->height = 1 + std::max(height(no->left), height(no->right));

    int balance = getBalance(no);

    if (balance > 1 && s.stator_winding < no->left->data.stator_winding) {
        return rotateRight(no);
    }
    if (balance < -1 && s.stator_winding > no->right->data.stator_winding) {
        return rotateLeft(no);
    }
    if (balance > 1 && s.stator_winding > no->left->data.stator_winding) {
        no->left = rotateLeft(no->left);
        return rotateRight(no);
    }
    if (balance < -1 && s.stator_winding < no->right->data.stator_winding) {
        no->right = rotateRight(no->right);
        return rotateLeft(no);
    }

    return no; 
}


int AVLTree::height(No* no) {
    if (no == nullptr)
        return 0;
    return no->height;
}

int AVLTree::getBalance(No* no) {
    if (no == nullptr)
        return 0;
    return height(no->left) - height(no->right);
}

No* AVLTree::rotateLeft(No* x) {
    No* y = x->right;
    No* T2 = y->left;

    y->left = x;
    x->right = T2;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

No* AVLTree::rotateRight(No* y) {
    No* x = y->left;
    No* T2 = x->right;

    x->right = y;
    y->left = T2;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    return x;
}


void AVLTree::printInOrder(No* no) {
    if (no != nullptr) {
        printInOrder(no->left);
        std::cout << no->data.stator_winding << " ";
        printInOrder(no->right);
    }
}

void AVLTree::printInOrder() {
    printInOrder(root);
}


//Estatística

void AVLTree::imprimirMedia() {
    int count = 0;
    float soma = 0;
    calcularMedia(root, soma, count);
    std::cout << "Média stator_winding: " << (count ? soma / count : 0) << std::endl;
}

void AVLTree::calcularMedia(No* no, float& soma, int& count) {
    if (no == nullptr) return;
    soma += no->data.stator_winding;
    count++;
    calcularMedia(no->left, soma, count);
    calcularMedia(no->right, soma, count);
}

void AVLTree::classificarDados() {
    classificarRec(root);
}

void AVLTree::classificarRec(No* no) {
    if (no == nullptr) return;
    classificarRec(no->left);
    float t = no->data.stator_winding;
    std::string c = (t < 70) ? "Normal" : (t < 90) ? "Alerta" : "Crítico";
    std::cout << t << " → " << c << std::endl;
    classificarRec(no->right);
}

void AVLTree::filtrarCoolantAlta(float limite) {
    filtrarRec(root, limite);
}

void AVLTree::filtrarRec(No* no, float limite) {
    if (no == nullptr) return;
    filtrarRec(no->left, limite);
    if (no->data.coolant > limite)
        std::cout << "Coolant: " << no->data.coolant << " Torque: " << no->data.torque << std::endl;
    filtrarRec(no->right, limite);
}
