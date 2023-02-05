#include "ProcessOpen.h"
#include "Memory.h"
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

    int getHashSize() { // NEED THIS?
        return hashSize;
    }

    void insert(int PID, Memory *Memory) {
        // check if the PID exists in the hash table
        int h1 = PID % hashSize;
        int h2 = (PID / 10) % hashSize;
        int currentIndex;
        for (int i = 0; i < hashSize; i++) { // 0 to m-1
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

        for (int i = 0; i < hashSize; i++) {
            if (Memory->getMemoryFree()[i] == false) { // found allocated memory
                std::cout << "success" << std::endl;
                Memory->setMemoryFree(i, true);
                ProcessOpen *newProcess = new ProcessOpen(PID, i);
                table[currentIndex] = newProcess;
                return;
            }
        }
        std::cout << "failure" << std::endl; // pages are all allocated
        return;
    }

    int search(int PID) {
        int h1 = PID % hashSize;
        int h2 = (PID / 10) % hashSize;
        int currentIndex;
        for (int i = 0; i < hashSize; i++) { // 0 to m-1
            currentIndex = (h1 + (i * h2)) % hashSize;
            if (currentIndex % 2 == 0) {
                currentIndex++;
            }
            if (table[currentIndex]->getPID() == PID) { // found duplicate
                return i;
            }
        }
        return -1;
    }

    void write(int PID, int ADDR, int x, Memory *Memory) {
        if (ADDR > pageSize - 1) { // address is outside of virtual address space
            std::cout << "failure" << std::endl;
            return;
        }
        int index = search(PID);
        if (index == -1) { // PID was not found
            std::cout << "failure" << std::endl;
            return;
        }
        Memory
    }
};