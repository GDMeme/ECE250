#include <vector>

class Memory {

private:
    bool *memoryFree;
    int *memoryValues;

public:
    Memory(int memorySize, int pageSize) {
        this->memoryFree = new bool [memorySize / pageSize]{true}; // true means memory is free
        this->memoryValues = new int [memorySize];
    }

    bool getMemoryFree(int index) { // to not expose the entire memoryFree array
        return memoryFree[index];
    }

    int getMemoryValues(int startPageAddress, int index) { // to not expose the entire memoryValues array
        return memoryValues[startPageAddress + index];
    }

    void setMemoryFree(int index, bool value) {
        memoryFree[index] = value;
        return;
    }

    void setMemoryValues(int startPageAddress, int index, int value) {
        memoryValues[startPageAddress + index] = value;
        return;
    }

};