#pragma once

class ProcessOrdered {

private:
    unsigned int PID;
    int startPageAddress;

public:
    ProcessOrdered(unsigned int PID, int startPageAddress) {
        this->PID = PID;
        this->startPageAddress = startPageAddress;
    }

    ~ProcessOrdered() { }

    int getStartPageAddress() {
        return startPageAddress;
    }

    unsigned int getPID() {
        return PID;
    }
};