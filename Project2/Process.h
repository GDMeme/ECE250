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

    ~Process() { }

    int getStartPageAddress() {
        return startPageAddress;
    }

    unsigned int getPID() {
        return PID;
    }
};