#include "ProcessOpen.h"
#include <vector>
#include <iostream>
#include <algorithm>

class HashTableOpen {

private:
    int memorySize; // N
    int pageSize; // P
    int hashSize; // m
    ProcessOpen** table;

public:
    HashTableOpen(int memorySize, int pageSize) {
        this->memorySize = memorySize;
        this->pageSize = pageSize;
        this->hashSize = memorySize / pageSize; 
        this->table = new ProcessOpen* [hashSize]{nullptr}; // default constructor
    }

    ~HashTableOpen() {
        for (int i = 0; i < hashSize; i++) {
            if (table[i] != nullptr) {
                delete table[i];
            }
        }
        delete[] table;
    }

    int getHashSize() {
        return hashSize;
    }

    int calculateStartPageAddress(int PID) {
        return PID % hashSize;
    }

    void insert(int PID, Memory *Memory) {
        // check if the PID exists in the hash table
        int h1 = PID % hashSize;
        int h2 = (PID / 10) % hashSize;
        int currentIndex;
        for (int i = 0; i < hashSize - 1; i++) {
            currentIndex = (h1 + (i * h2)) % hashSize;
            if (currentIndex % 2 == 0) {
                currentIndex++;
            }
            if (table[currentIndex]->getPID() == 0) { // end of double hash found, no duplicate
                break;
            }
            if (table[currentIndex]->getPID() == PID) { // found duplicate
                std::cout << "failure" << std::endl;
                return;
            }
        }
        // check if memory has room

        for (int i = 0; i < sizeof(Memory->getMemoryFree())/sizeof(int); i++) {
            if (Memory->getMemoryFree()[i] == 0) { // found allocated memory
                Memory->getMemoryFree()[i] = PID;
                ProcessOpen *newProcess = new ProcessOpen(PID, i);
                table[currentIndex] = newProcess;
                return;
            }
        }
        std::cout << "failure" << std::endl; // pages are all allocated
        return;
    }
};