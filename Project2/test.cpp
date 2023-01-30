#include <iostream>
#include <algorithm>

int main() {

    bool *myArray = new bool [3]{false};

    myArray[0] = true;
    std::cout << myArray[0] << std::endl;
    std::cout << myArray + 3 << std::endl;
    std::cout << (std::find(myArray, myArray + 3, false)) - myArray << std::endl;
}