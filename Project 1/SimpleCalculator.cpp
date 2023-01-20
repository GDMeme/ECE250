#include <iostream>
using namespace std;
 
class Node {

private:
    double value;
    string name;
    Node* next;

public:
    Node(string name, double value)
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

    string getName() {
        return name;
    }

    Node* getNext() {
        return next;
    }

    void setNext(Node* nextNode) {
        next = nextNode;
    }
};
class LinkedList {

private:
    unsigned int maxLength;
    unsigned int currentLength;
    Node* head;
 
public:
    LinkedList(unsigned int maxLength) { 
        this->head = NULL; 
        this->maxLength = maxLength;
        this->currentLength = 0;
    }

    ~LinkedList() {
        Node* current = head;
        Node* next;

        while (current != NULL) {
            next = current->getNext();
            delete current;
            current = next;
        }
    }
 
    Node* getHead() {
        return head;
    }

    void setHead(Node* newHead) {
        head = newHead;
    }

    void addNode(string, double);
 
    void removeName(string);

    void addValues(string, string, string);

    void subtractValues(string, string, string);

    void printValue(string);
};


void LinkedList::addValues(string x, string y, string z) {
    Node *temp = head;
    Node *copy = head;
    Node *foundNode = NULL;
    double first = 0;
    double second = 0;
    bool firstFound = false;
    bool secondFound = false;
    if (temp->getName() == x) { // check the head node
        first = temp->getValue();
        firstFound = true;
    }
    if (temp->getName() == y) {
        second = temp->getValue();
        secondFound = true;
    }
    if (temp->getName() == z) { // first name in list matches z
        foundNode = copy;
    }
    while (temp->getNext() != NULL) {
        if (temp->getNext()->getName() == x) {
            first = temp->getNext()->getValue();
            firstFound = true;
        }
        if (temp->getNext()->getName() == y) {
            second = temp->getNext()->getValue();
            secondFound = true;
        }
        if (temp->getNext()->getName() == z) {
            foundNode = copy->getNext();
        }
        temp = temp->getNext();
        if (!foundNode) {
            copy = copy->getNext();
        }
        if (firstFound && secondFound && foundNode) {
            cout << "success" << endl;
            foundNode->setValue(first + second);
            return;
        }
    }
    cout << "failure" << endl;
    return;
}

void LinkedList::subtractValues(string x, string y, string z) {
    Node *temp = head;
    Node *copy = head;
    Node *foundNode = NULL;
    double first = 0;
    double second = 0;
    bool firstFound = false;
    bool secondFound = false;
    if (temp->getName() == x) { // check the head node
        first = temp->getValue();
        firstFound = true;
    }
    if (temp->getName() == y) {
        second = temp->getValue();
        secondFound = true;
    }
    if (temp->getName() == z) { // first name in list matches z
        foundNode = copy;
    }
    while (temp->getNext() != NULL) {
        if (temp->getNext()->getName() == x) {
            first = temp->getNext()->getValue();
            firstFound = true;
        }
        if (temp->getNext()->getName() == y) {
            second = temp->getNext()->getValue();
            secondFound = true;
        }
        if (temp->getNext()->getName() == z) {
            foundNode = copy->getNext();
        }
        temp = temp->getNext();
        if (!foundNode) {
            copy = copy->getNext();
        }
    }
    if (firstFound && secondFound && foundNode) {
        cout << "success" << endl;
        foundNode->setValue(first - second);
        return;
    }
    cout << "failure" << endl;
    return;
} 

void LinkedList::printValue(string name) {
    Node *temp = head;
    while (temp != NULL) {
        if (temp->getName() == name) {
            cout << temp->getValue() << endl;
            return;
        }
        temp = temp->getNext();
    }
    cout << "variable " << name << " not found" << endl;
    return;
}
 
void LinkedList::removeName(string name)
{
    Node *temp1 = head;
    if (head == NULL) { // list is empty
        cout << "failure" << endl;
        return;
    }
    if (temp1->getName() == name) { // delete the first node (because I have to change head)
        cout << "success" << endl;
        currentLength--;
        head = temp1->getNext();
        delete temp1;
        return;
    }
    while (temp1->getNext() != NULL) {
        if (temp1->getNext()->getName() == name) {
            cout << "success" << endl;
            currentLength--;
            temp1->setNext(temp1->getNext()->getNext());
            delete temp1->getNext();
            return;
        }
        temp1 = temp1->getNext();
    }
    cout << "failure" << endl;
    return;
}
 
void LinkedList::addNode(string name, double val)
{
    if (currentLength == maxLength) {
        cout << "failure" << endl;
        return;
    }
    Node* newNode = new Node(name, val);
    if (head == NULL) { // list is empty
        cout << "success" << endl;
        currentLength++;
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->getNext() != NULL) {
        if (temp->getName() == name) {
            cout << "failure" << endl;
            return;
        }
        temp = temp->getNext();
    }
    if (temp->getName() == name) { // check the last element
        cout << "failure" << endl;
        return;
    }
    cout << "success" << endl;
    currentLength++;
    temp->setNext(newNode);
    return;
}

int main()
{
    LinkedList* list;
    string cmd;
    string name;
    string name2;
    string name3;
    while (cin >> cmd) {
        if (cmd == "CRT") {
            unsigned int val;
            cin >> val;
            list = new LinkedList(val);
            cout << "success" << endl;
        } else if (cmd == "DEF") {
            double val;
            string name;
            cin >> name;
            cin >> val;
            list->addNode(name, val);
        } else if (cmd == "ADD") {
            cin >> name;
            cin >> name2;
            cin >> name3;
            list->addValues(name, name2, name3);
        } else if (cmd == "SUB") {
            cin >> name;
            cin >> name2;
            cin >> name3;
            list->subtractValues(name, name2, name3);
        } else if (cmd == "REM") {
            cin >> name;
            list->removeName(name);
        } else if (cmd == "PRT") {
            cin >> name;
            list->printValue(name);
        } else if (cmd == "END") {
            break;
        }
    }
    delete list;
    return 0;
}