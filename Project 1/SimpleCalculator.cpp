#include <iostream>
using namespace std;
 
class Node {
public:
    int value; // Linkedlist needs access to these variables
    string name;
    Node* next;
 
    Node(string name, int value)
    {
        this->value = value;
        this->name = name;
        this->next = NULL;
    }
};

class Linkedlist {

private:
    Node* head;
    int maxLength;
    int currentLength;
 
public:
    Linkedlist(int maxLength) { 
        this->head = NULL; 
        this->maxLength = maxLength;
        this->currentLength = 0;
    }
 
    void insertNode(string, int);
 
    void deleteNode(string);
};
 
void Linkedlist::deleteNode(string name)
{
    Node *temp1 = head;
    bool found = false;
 
    if (head == NULL) { // list is empty
        cout << "failure" << endl;
        return;
    }

    if (temp1->name == name) { // delete the first node
        head = temp1->next;
        delete temp1;
        return;
    }

    Node *temp2 = NULL;

    temp2 = temp1; // temp2 keeps track of the previous node
    temp1 = temp1->next;
    while (temp1 != NULL) {
        if (temp1->name == name) {
            cout << "success" << endl;
            currentLength--;
            found = true;
            temp2->next = temp1->next;
            delete temp1;
            break;
        }
    }

    if (!found) {
        cout << "failure" << endl;
    }
    return;
}
 
void Linkedlist::insertNode(string name, int val)
{
    if (currentLength == maxLength) {
        cout << "failure" << endl;
        return;
    }

    Node* newNode = new Node(name, val);
    bool duplicate = false;
 
    if (head == NULL) { // list is empty
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
    Linkedlist* list;

    string cmd;
    string name;
    string name2;
    string name3;
    int val;
    while (cin >> cmd) {
        if (cmd == "CRT") {
            cin >> val;
            list = new Linkedlist(val);
        } else if (cmd == "DEF") {
            cin >> name;
            cin >> val; // could check if name already exists in the linked list here (call some other function)
            list->insertNode(name, val);
        } else if (cmd == "ADD") {
            cin >> name;
            cin >> name2;
            cin >> name3;
            list->addValues(name, name2, name3); // TEST: duplicate names are allowed in this command
        } else if (cmd == "SUB") {
            cin >> name;
            cin >> name2;
            cin >> name3;
            list->subtractValues(name, name2, name3); // TEST: duplicate names are allowed in this command
        } else if (cmd == "REM") {
            // CHECK IF THE VARIABLE EXISTS (probably do it inside the function call)
            cin >> name;
            list->deleteNode(name);
        } else if (cmd == "PRT") {
            cin >> name;
            list->printValue(name);
        } else if (cmd == "END") {
            break;
        }
    }
}