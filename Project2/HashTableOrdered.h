#pragma once

#include "Process.h"
#include "Memory.h"
#include <iostream>
#include <vector>

class HashTableOrdered {

private:
    int memorySize; // N
    int pageSize; // P
    int hashSize; // m
    std::vector<Process*>* table;

public:
    HashTableOrdered(int memorySize, int pageSize) {
        this->memorySize = memorySize;
        this->pageSize = pageSize;
        this->hashSize = memorySize / pageSize; 
        this->table = new std::vector<Process*> [hashSize];
    }

    ~HashTableOrdered() {
        for (int i = 0; i < hashSize; i++) {
            for (int j = 0; j < table[i].size(); j++) {
                if (table[i][j] != 0) {
                    delete table[i][j]; // make sure when deleting from hash table, set to 0.
                }
            }
        }
        delete[] table;
    }

    void insert(unsigned int PID, Memory *Memory) {
        // check if memory has room
        int i;
        bool memoryFound{false};
        for (i = 0; i < hashSize; i++) {
            if (Memory->getMemoryNotFree(i) == false) { // found unallocated memory
                memoryFound = true;
                break;
            }
        }
        if (!memoryFound) {
            std::cout << "failure" << std::endl; // pages are all allocated
            return;
        }
        // check if the PID exists in the hash table
        int h1 = PID % hashSize;
        for (int j = 0; j < table[h1].size(); j++) {
            if (table[h1][j]->getPID() < PID) {
                std::cout << "success" << std::endl;
                Memory->setMemoryNotFree(i, true); // no longer free
                Process *newProcess = new Process(PID, i * pageSize);
                table[h1].insert(table[h1].begin() + j, newProcess);
                return;
            }
            if (table[h1][j]->getPID() == PID) { // duplicate found
                std::cout << "failure" << std::endl;
                return;
            }
        }
        std::cout << "success" << std::endl;
        Memory->setMemoryNotFree(i, true); // no longer free
        Process *newProcess = new Process(PID, i * pageSize);
        table[h1].push_back(newProcess);
        return;
    }

    int search(unsigned int PID) {
        int h1 = PID % hashSize;
        for (int j = 0; j < table[h1].size(); j++) {
            if (table[h1][j]->getPID() == PID) { // found the PID
                return j;
            }
        }
        // not found in the chain
        return -1;
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
        Memory->setMemoryValues(table[PID % hashSize][index]->getStartPageAddress(), ADDR, x);
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
        std::cout << ADDR << " " << Memory->getMemoryValues(table[PID % hashSize][index]->getStartPageAddress(), ADDR) << std::endl;
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
        Memory->setMemoryNotFree(table[PID % hashSize][index]->getStartPageAddress() / pageSize, false); // memory is free now
        Process *toDelete = table[PID % hashSize][index];
        table[PID % hashSize].erase(table[PID % hashSize].begin() + index);
        delete toDelete;
        return;
    }

    void print(int m) {
        if (table[m].size() == 0) {
            std::cout << "chain is empty" << std::endl;
            return;
        }
        std::cout << table[m][0]->getPID();
        for (int i = 1; i < table[m].size(); i++) {
            std::cout << " " << table[m][i]->getPID();
        }
        std::cout << std::endl;
        return;
    }
};