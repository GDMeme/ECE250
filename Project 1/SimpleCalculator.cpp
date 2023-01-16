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

    int maxLength;
    int currentLength;
 
public:
    Node* head;
    Linkedlist(int maxLength) { 
        this->head = NULL; 
        this->maxLength = maxLength;
        this->currentLength = 0;
    }

    ~Linkedlist() {
        Node* current = head;
        Node* next;

        while (current != NULL) {
            next = current->next;
            delete current;
            current = next;
        }
    }
 
    void insertNode(string, int);
 
    void deleteNode(string);

    void addValues(string, string, string);

    void subtractValues(string, string, string);

    void printValue(string);
};

void Linkedlist::addValues(string x, string y, string z) {
    Node *temp = head;
    Node *copy = head;
    Node *previousNode = NULL;
    Node *nodeToDelete;
    Node *nextNode = NULL;
    int first = 0;
    int second = 0;
    int third = 0;
    bool foundNext = false;
    bool firstFound = false;
    bool secondFound = false;
    bool thirdFound = false;

    if (temp->name == z) { // first name in list matches z
        previousNode = NULL;
        nextNode = temp->next;
        thirdFound = true;
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
            previousNode = copy; // temp keeps getting updated so this doesn't work
            nodeToDelete = previousNode->next;
            if (nodeToDelete != NULL) {
                nextNode = previousNode->next->next;
            }
            thirdFound = true;
        }
        if (!thirdFound) {
            previousNode = temp; // temp keeps getting updated so this doesn't work
            nodeToDelete = previousNode->next;
            if (nodeToDelete != NULL) {
                nextNode = previousNode->next->next;
            }
        }
        temp = temp->next;
        if (!thirdFound) {
            copy = copy->next;
        }
    }

    if (temp->name == x) {
        first = temp->value;
        firstFound = true;
    }
    if (temp->name == y) {
        second = temp->value;
        secondFound = true;
    }
    if (temp->name == z) {
        thirdFound = true;
    }


    if (firstFound && secondFound && thirdFound) {
        cout << "success" << endl;
        Node *newNode = new Node(z, first + second);
        delete nodeToDelete;
        if (previousNode) {
            previousNode->next = newNode;
        }
        if (nextNode != NULL) { // in case newNode is the last element of list
            newNode->next = nextNode;
        }
        return;
    }
    
    cout << "failure" << endl;
    return;
}

void Linkedlist::subtractValues(string x, string y, string z) {
    Node *temp = head;
    Node *first;
    Node *second;
    Node *third;
    bool firstFound = false;
    bool secondFound = false;
    bool thirdFound = false;
    while (temp != NULL) {
        if (firstFound && secondFound && thirdFound) {
            cout << "success" << endl;
            third->value = first->value - second->value;
            return;
        }
        if (temp->name == x) {
            Node *first = temp;
            firstFound = true;
        } else if (temp->name == y) {
            Node *second = temp;
            secondFound = true;
        } else if (temp->name == z) {
            Node *third = temp;
            thirdFound = true;
        }
        temp = temp->next;
    }

    cout << "failure" << endl;
    return;
} 

void Linkedlist::printValue(string name) {
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
 
void Linkedlist::deleteNode(string name)
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
 
void Linkedlist::insertNode(string name, int val)
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
    Linkedlist* list;

    string cmd;
    while (cin >> cmd) {
        if (cmd == "CRT") {
            int val;
            cin >> val;
            list = new Linkedlist(val);
            cout << "success" << endl;
        } else if (cmd == "DEF") {
            int val;
            string name;
            cin >> name;
            cin >> val;
            list->insertNode(name, val);
        } else if (cmd == "ADD") {
            string name;
            string name2;
            string name3;
            cin >> name;
            cin >> name2;
            cin >> name3;
            list->addValues(name, name2, name3); // TEST: duplicate names are allowed in this command
        } else if (cmd == "SUB") {
            string name;
            string name2;
            string name3;
            cin >> name;
            cin >> name2;
            cin >> name3;
            list->subtractValues(name, name2, name3); // TEST: duplicate names are allowed in this command
        } else if (cmd == "REM") {
            string name;
            cin >> name;
            list->deleteNode(name);
        } else if (cmd == "PRT") {
            string name;
            cin >> name;
            list->printValue(name);
        } else if (cmd == "END") {
            break;
        }
    }

    // Node *temp = list->head;
    // while (temp != NULL) {
    //     cout << temp->name << endl;
    //     temp = temp->next;
    // }

    delete list;
    return 0;
}