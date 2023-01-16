#include <iostream>
using namespace std;
 
class Node {

public:
    int value; // LinkedList needs access to these variables
    string name;
    Node* next;
 
    Node(string name, int value)
    {
        this->value = value;
        this->name = name;
        this->next = NULL;
    }

};

class LinkedList {

private:
    int maxLength;
    int currentLength;
 
public:
    Node* head;
    LinkedList(int maxLength) { 
        this->head = NULL; 
        this->maxLength = maxLength;
        this->currentLength = 0;
    }

    ~LinkedList() {
        Node* current = head;
        Node* next;

        while (current != NULL) {
            next = current->next;
            delete current;
            current = next;
        }
    }
 
    void addNode(string, int);
 
    void removeName(string);

    void addValues(string, string, string);

    void subtractValues(string, string, string);

    void printValue(string);
};

void LinkedList::addValues(string x, string y, string z) {
    Node *temp = head;
    Node *copy = head;
    Node *foundNode = NULL;
    int first = 0;
    int second = 0;
    bool firstFound = false;
    bool secondFound = false;
    if (temp->name == x) {
        first = temp->value;
        firstFound = true;
    }
    if (temp->name == y) {
        second = temp->value;
        secondFound = true;
    }
    if (temp->name == z) { // first name in list matches z
        foundNode = copy;
    }
    while (temp->next != NULL) {
        if (temp->next->name == x) {
            first = temp->next->value;
            firstFound = true;
        }
        if (temp->next->name == y) {
            second = temp->next->value;
            secondFound = true;
        }
        if (temp->next->name == z) {
            foundNode = copy->next;
        }
        temp = temp->next;
        if (!foundNode) {
            copy = copy->next;
        }
    }
    if (firstFound && secondFound && foundNode) {
        cout << "success" << endl;
        foundNode->value = first + second;
        return;
    }
    cout << "failure" << endl;
    return;
}

void LinkedList::subtractValues(string x, string y, string z) {
    Node *temp = head;
    Node *copy = head;
    Node *foundNode = NULL;
    int first = 0;
    int second = 0;
    bool firstFound = false;
    bool secondFound = false;
    if (temp->name == x) {
        first = temp->value;
        firstFound = true;
    }
    if (temp->name == y) {
        second = temp->value;
        secondFound = true;
    }
    if (temp->name == z) { // first name in list matches z
        foundNode = copy;
    }
    while (temp->next != NULL) {
        if (temp->next->name == x) {
            first = temp->next->value;
            firstFound = true;
        }
        if (temp->next->name == y) {
            second = temp->next->value;
            secondFound = true;
        }
        if (temp->next->name == z) {
            foundNode = copy->next;
        }
        temp = temp->next;
        if (!foundNode) {
            copy = copy->next;
        }
    }
    if (firstFound && secondFound && foundNode) {
        cout << "success" << endl;
        foundNode->value = first - second;
        return;
    }
    cout << "failure" << endl;
    return;
} 

void LinkedList::printValue(string name) {
    Node *temp = head;
    while (temp != NULL) {
        if (temp->name == name) {
            cout << temp->value << endl;
            return;
        }
        temp = temp->next;
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
    if (temp1->name == name) { // delete the first node (because I have to change head)
        cout << "success" << endl;
        currentLength--;
        head = temp1->next;
        delete temp1;
        return;
    }
    while (temp1->next != NULL) {
        if (temp1->next->name == name) {
            cout << "success" << endl;
            currentLength--;
            temp1->next = temp1->next->next;
            delete temp1->next;
            return;
        }
        temp1 = temp1->next;
    }
    cout << "failure" << endl;
    return;
}
 
void LinkedList::addNode(string name, int val)
{
    if (currentLength == maxLength) {
        cout << "failure" << endl;
        return;
    }
    Node* newNode = new Node(name, val);
    bool duplicate = false;
    if (head == NULL) { // list is empty
        cout << "success" << endl;
        currentLength++;
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != NULL) {
        if (temp->name == name) {
            duplicate = true;
            break;
        }
        temp = temp->next;
    }
    if (temp->name == name) {
        duplicate = true;
    }
    if (duplicate) {
        cout << "failure" << endl;
        return;
    }
    cout << "success" << endl;
    currentLength++;
    temp->next = newNode;
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