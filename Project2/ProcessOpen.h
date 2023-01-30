#pragma once

class Process {

private:
    unsigned int PID;
    int startPageAddress;

public:
    Process(unsigned int PID, int startPageAddress) {
        this->PID = PID;
        this->startPageAddress = startPageAddress;
    }

    Process() {
        this->PID = 0;
        this->startPageAddress = 0;
    }

    ~Process() { }

    int getStartPageAddress() {
        return startPageAddress;
    }

    unsigned int getPID() {
        return PID;
    }
};