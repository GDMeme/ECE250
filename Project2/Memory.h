#include <vector>

class Memory {

private:
    bool *memoryNotFree;
    int *memoryValues;

public:
    Memory(int memorySize, int pageSize) {
        this->memoryNotFree = new bool [memorySize / pageSize]{}; // true means memory is free
        this->memoryValues = new int [memorySize];
    }

    ~Memory() {
        delete[] memoryNotFree;
        delete[] memoryValues;
    }

    bool getMemoryNotFree(int index) { // to not expose the entire memoryFree array
        return memoryNotFree[index];
    }

    int getMemoryValues(int startPageAddress, int index) { // to not expose the entire memoryValues array
        return memoryValues[startPageAddress + index];
    }

    void setMemoryNotFree(int index, bool value) {
        memoryNotFree[index] = value;
        return;
    }

    void setMemoryValues(int startPageAddress, int index, int value) {
        memoryValues[startPageAddress + index] = value;
        return;
    }

};