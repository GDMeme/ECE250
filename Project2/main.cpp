#include "HashTableOpen.h"
#include "HashTableOrdered.h"
#include "Process.h"
#include "Memory.h"
#include <iostream>
using namespace std;

int main() {

    string cmd;
    int N;
    int P;
    cin >> cmd;
    Memory* memory;
    if (cmd == "OPEN") {
        HashTableOpen *table;
        while (cin >> cmd) {
            if (cmd == "M") {
                cin >> N;
                cin >> P;
                table = new HashTableOpen(N, P);
                memory = new Memory(N, P);
                cout << "success" << endl;
            } else if (cmd == "INSERT") {
                unsigned int PID;
                cin >> PID;
                table->insert(PID, memory);
            } else if (cmd == "SEARCH") {
                unsigned int PID;
                cin >> PID;
                int index = table->search(PID);
                if (index != -1) {
                    cout << "found " << PID << " in " << index << endl;
                } else {
                    cout << "not found" << endl;
                }
            } else if (cmd == "WRITE") {
                unsigned int PID;
                cin >> PID;
                int ADDR;
                cin >> ADDR;
                int x;
                cin >> x;
                table->write(PID, ADDR, x, memory);
            } else if (cmd == "READ") {
                unsigned int PID; 
                cin >> PID;
                int ADDR;
                cin >> ADDR;
                table->read(PID, ADDR, memory);
            } else if (cmd == "DELETE") {
                unsigned int PID;
                cin >> PID;
                table->deletePID(PID, memory);
            } else if (cmd == "END") {
                break;
            }
        }
        delete table;
    } else { // ORDERED
        HashTableOrdered *table;
        while (cin >> cmd) {
            if (cmd == "M") {
                cin >> N;
                cin >> P;
                table = new HashTableOrdered(N, P);
                memory = new Memory(N, P);
                cout << "success" << endl;
            } else if (cmd == "INSERT") {
                unsigned int PID;
                cin >> PID;
                table->insert(PID, memory);
            } else if (cmd == "SEARCH") {
                unsigned int PID;
                cin >> PID;
                int index = table->search(PID);
                if (index != -1) {
                    cout << "found " << PID << " in " << PID % (N / P) << endl;
                } else {
                    cout << "not found" << endl;
                }
            } else if (cmd == "WRITE") {
                unsigned int PID;
                cin >> PID;
                int ADDR;
                cin >> ADDR;
                int x;
                cin >> x;
                table->write(PID, ADDR, x, memory);
            } else if (cmd == "READ") {
                unsigned int PID; 
                cin >> PID;
                int ADDR;
                cin >> ADDR;
                table->read(PID, ADDR, memory);
            } else if (cmd == "DELETE") {
                unsigned int PID;
                cin >> PID;
                table->deletePID(PID, memory);
            } else if (cmd == "PRINT") {
                unsigned int m;
                cin >> m;
                table->print(m);
            } else if (cmd == "END") {
                break;
            }
        }
        delete table;
    }
    delete memory;
    return 0;
}