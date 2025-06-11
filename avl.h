struct SensorData {
    float torque, ambient, coolant, motor_speed, stator_yoke, stator_winding;
};

struct No{
    int height;
    SensorData data;
    No* left;
    No* right;
};

class AVLTree {
private:
    No* root;
    No* insert(No* no, const SensorData& s);
    int height(No* no);
    int getBalance(No* no);
    No* rotateLeft(No* x);
    No* rotateRight(No* y);
    void printInOrder(No* no);
    No* minValueNo(No* no);
    No* remove(No* no, float key);

public:
    AVLTree();
    void insert(const SensorData& s);
    void printInOrder();
    void remove(float stator_winding);
    SensorData* search(float stator_winding);

    void imprimirMedia();
    void calcularMedia(No* no, float& soma, int& count);
    void classificarDados();
    void classificarRec(No* no);
    void filtrarCoolantAlta(float limite);
    void filtrarRec(No* no, float limite);

};
