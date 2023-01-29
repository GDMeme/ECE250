#pragma once

class Process {

private:
    unsigned int PID;
    int startPageAddress;
    Process *next;

public:
    Process(unsigned int PID, int m) { // m is the size of the hash table REMEMBER TO PASS THIS IN
        this->PID = PID;
        this->startPageAddress = PID % m;
        this->next = nullptr;
    }

    Process() {
        this->PID = 0;
        this->startPageAddress = 0;
        this->next = nullptr;
    }

    ~Process() { }

    int getStartPageAddress() {
        return startPageAddress;
    }

    unsigned int getPID() {
        return PID;
    }

    Process * getNext() {
        return next;
    }

    void * setNext(Process *nextPID) {
        next = nextPID;
    }

};