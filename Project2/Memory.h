#include <vector>

class Memory {

private:
    bool *memoryFree;
    int *memoryValues;

public:
    Memory(int memorySize, int pageSize) {
        this->memoryFree = new bool [memorySize / pageSize]{0};
        this->memoryValues = new int [memorySize];
    }

    bool *getMemoryFree() {
        return memoryFree;
    }

    int *getMemoryValues() {
        return memoryValues;
    }

    void *setMemoryFree(int index, bool value) {
        memoryFree[index] = value;
    }

    void *setMemoryValues() {
        // do something
    }

};