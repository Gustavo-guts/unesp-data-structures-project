#include "skiplist.h"

SkipList::SkipList() {
    level = 0;
    head = createNode(SensorData(), MAX_LEVEL);
    srand(time(nullptr));
}

int SkipList::randomLevel() {
    int lvl = 1;
    while ((rand() % 2) && lvl < MAX_LEVEL)
        lvl++;
    return lvl;
}

SkipNode* SkipList::createNode(SensorData data, int lvl) {
    SkipNode* node = new SkipNode;
    node->data = data;
    node->level = lvl;
    node->forward = new SkipNode*[lvl];
    for (int i = 0; i < lvl; i++) node->forward[i] = nullptr;
    return node;
}

void SkipList::insert(SensorData data) {
    SkipNode* update[MAX_LEVEL];
    SkipNode* x = head;
    for (int i = level - 1; i >= 0; i--) {
        while (x->forward[i] && x->forward[i]->data.stator_winding < data.stator_winding)
            x = x->forward[i];
        update[i] = x;
    }

    int lvl = randomLevel();
    if (lvl > level) {
        for (int i = level; i < lvl; i++)
            update[i] = head;
        level = lvl;
    }

    SkipNode* novo = createNode(data, lvl);
    for (int i = 0; i < lvl; i++) {
        novo->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = novo;
    }
}






//Estatística
SensorData* SkipList::search(float sw) {
    SkipNode* x = head;
    for (int i = level - 1; i >= 0; i--) {
        while (x->forward[i] && x->forward[i]->data.stator_winding < sw)
            x = x->forward[i];
    }
    x = x->forward[0];
    if (x && x->data.stator_winding == sw)
        return &x->data;
    return nullptr;
}

void SkipList::remove(float sw) {
    SkipNode* update[MAX_LEVEL];
    SkipNode* x = head;
    for (int i = level - 1; i >= 0; i--) {
        while (x->forward[i] && x->forward[i]->data.stator_winding < sw)
            x = x->forward[i];
        update[i] = x;
    }

    x = x->forward[0];
    if (x && x->data.stator_winding == sw) {
        for (int i = 0; i < level; i++) {
            if (update[i]->forward[i] != x) break;
            update[i]->forward[i] = x->forward[i];
        }
        delete[] x->forward;
        delete x;
    }
}
