#include <vector>

class Memory {

private:
    int *memoryFree;
    int *memoryValues;

public:
    Memory(int memorySize, int pageSize) {
        this->memoryFree = new int [memorySize / pageSize]{0};
        this->memoryValues = new int [memorySize];
    }

    int *getMemoryFree() {
        return memoryFree;
    }

    int *getMemoryValues() {
        return memoryValues;
    }

};