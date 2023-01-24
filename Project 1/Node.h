#include <string>

class Node {

private:
    double value;
    std::string name;
    Node* next;

public:
    Node(std::string name, double value)
    {
        this->value = value;
        this->name = name;
        this->next = NULL;
    }

    ~Node() { }

    double getValue() {
        return value;
    }

    void setValue(double val) {
        value = val;
    }

    std::string getName() {
        return name;
    }

    Node* getNext() {
        return next;
    }

    void setNext(Node* nextNode) {
        next = nextNode;
    }
};