#include "ProcessOpen.h"
#include "Memory.h"
#include <iostream>

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
        this->table = new ProcessOpen* [hashSize]{nullptr};
    }

    ~HashTableOpen() {
        for (int i = 0; i < hashSize; i++) {
            if (table[i] != nullptr) {
                delete table[i];
            }
        }
        delete[] table;
    }

    void insert(unsigned int PID, Memory *Memory) {
        // check if the PID exists in the hash table
        int h1 = PID % hashSize;
        int h2 = (PID / hashSize) % hashSize;
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
            if (Memory->getMemoryNotFree(i) == false) { // found unallocated memory
                std::cout << "success" << std::endl;
                Memory->setMemoryNotFree(i, true); // no longer free
                ProcessOpen *newProcess = new ProcessOpen(PID, i * pageSize);
                table[currentIndex] = newProcess;
                return;
            }
        }
        std::cout << "failure" << std::endl; // pages are all allocated
        return;
    }

    int search(unsigned int PID) {
        int h1 = PID % hashSize;
        int h2 = (PID / hashSize) % hashSize;
        if (h2 % 2 == 0) {
            h2++;
        }
        int currentIndex;
        for (int i = 0; i < hashSize; i++) { // 0 to m-1
            currentIndex = (h1 + (i * h2)) % hashSize;
            if (table[currentIndex] && table[currentIndex]->getPID() == PID) { // found the PID
                return currentIndex;
            }
        }
        return -1; // reached loop limit, PID was not found
    }

    void write(unsigned int PID, int ADDR, int x, Memory *Memory) {
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

    void read(unsigned int PID, int ADDR, Memory *Memory) {
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

    void deletePID(unsigned int PID, Memory *Memory) {
        int index = search(PID);
        if (index == -1) {
            std::cout << "failure" << std::endl;
            return;
        }
        // PID was found
        std::cout << "success" << std::endl;
        Memory->setMemoryNotFree(table[index]->getStartPageAddress() / pageSize, false); // memory is free now
        ProcessOpen *toDelete = table[index];
        table[index] = nullptr;
        delete toDelete;
        return;
    }
};