#include <iostream>

int main() {
    int a{0};
    std::string s = "A";
    s += char(a + 'A');
    std::cout << s << std::endl;
}