#pragma once

class ProcessOpen {

private:
    unsigned int PID;
    int startPageAddress;

public:
    ProcessOpen(unsigned int PID, int startPageAddress) {
        this->PID = PID;
        this->startPageAddress = startPageAddress;
    }

    ~ProcessOpen() { }

    int getStartPageAddress() {
        return startPageAddress;
    }

    unsigned int getPID() {
        return PID;
    }
};