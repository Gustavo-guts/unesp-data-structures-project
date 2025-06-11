struct SensorData {
    float torque, ambient, coolant, motor_speed, stator_yoke, stator_winding;
    SensorData* next;
};

class HashTable {
private:
    static const int TAM = 101;
    SensorData* table[TAM];

    int hash(float chave);

public:
    HashTable();
    void insert(SensorData s);
    void remove(float stator_winding);
    SensorData* search(float stator_winding);
    void imprimirMedia();
    void classificarDados();
    void filtrarCoolantAlta(float limite);
};
