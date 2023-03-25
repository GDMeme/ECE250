#pragma once

#include <iostream>

class illegal_exception {
    public:
        void print() {
            std::cout << "illegal argument" << std::endl;
            return;
        }
};