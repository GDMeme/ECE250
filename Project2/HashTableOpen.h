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

    void insert(int PID, Memory *Memory) {
        // check if the PID exists in the hash table
        int h1 = PID % hashSize;
        int h2 = (PID / 10) % hashSize;
        if (h2 % 2 == 0) {
            h2++;
        }
        int currentIndex;
        for (int i = 0; i < hashSize; i++) { // 0 to m-1
            currentIndex = (h1 + (i * h2)) % hashSize;
            if (table[currentIndex] == nullptr) { // end of double hash found, no duplicate
                break;
            }
            if (table[currentIndex]->getPID() == PID) { // found duplicate
                std::cout << "failure" << std::endl;
                return;
            }
        }
        // check if memory has room
        for (int i = 0; i < hashSize; i++) {
            if (Memory->getMemoryFree(i) == true) { // found unallocated memory
                std::cout << "success" << std::endl;
                Memory->setMemoryFree(i, false); // no longer free
                ProcessOpen *newProcess = new ProcessOpen(PID, i * pageSize);
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
        if (h2 % 2 == 0) {
            h2++;
        }
        int currentIndex;
        for (int i = 0; i < hashSize; i++) { // 0 to m-1
            currentIndex = (h1 + (i * h2)) % hashSize;
            if (table[currentIndex] == nullptr) { // end of double hash, PID was not found
                return -1; // output is in main
            }
            if (table[currentIndex]->getPID() == PID) { // found the PID
                return currentIndex;
            }
        }
        return -1; // reached loop limit, PID was not found
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
        // PID was found
        std::cout << "success" << std::endl;
        Memory->setMemoryValues(table[index]->getStartPageAddress(), ADDR, x);
        return;
    }

    void read(int PID, int ADDR, Memory *Memory) {
        if (ADDR > pageSize - 1) { // address is outside of virtual address space
            std::cout << "failure" << std::endl;
            return;
        }
        int index = search(PID);
        if (index == -1) { // PID was not found
            std::cout << "failure" << std::endl;
            return;
        }
        // PID was found
        std::cout << ADDR << " " << Memory->getMemoryValues(table[index]->getStartPageAddress(), ADDR) << std::endl;
        return;
    }

    void deletePID(int PID, Memory *Memory) {
        int index = search(PID);
        if (index == -1) {
            std::cout << "failure" << std::endl;
            return;
        }
        // PID was found
        Memory->setMemoryFree(table[index]->getStartPageAddress(), true);
        ProcessOpen *toDelete = table[index];
        table[index] = nullptr;
        delete toDelete; // I think this works?
    }
};