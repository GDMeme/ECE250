#include <vector>
#include <iostream>

int main() {
    std::vector<int> myVector(5, 0);
    myVector.insert(myVector.begin() + 1, 5);
    std::cout << myVector[1] << std::endl;
}