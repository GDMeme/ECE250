#include "ProcessOpen.h"
#include "ProcessOrdered.h"
#include "HashTableOpen.h"
#include "HashTableOrdered.h"
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
        HashTableOpen *table; // everything below this might not be right
        while (cin >> cmd) {
            if (cmd == "M") {
                cin >> N;
                cin >> P;
                table = new HashTableOpen(N, P);
            } else if (cmd == "INSERT") {
                unsigned int PID;
                cin >> PID;
                table->insert(PID, memory);
                // SOMEHOW INSERT IT
            } else if (cmd == "SEARCH") {
                unsigned int PID;
                cin >> PID;

                // SEARCH FOR THE KEY PID IN THE TABLE

            } else if (cmd == "WRITE") {
                unsigned int PID;
                cin >> PID;
                int ADDR;
                cin >> ADDR;
                int x;
                cin >> x;

                // WRITE THE INTEGER (x) TO THE MEMORY ADDRESS
            } else if (cmd == "READ") {
                unsigned int PID; 
                cin >> PID;
                int ADDR;
                cin >> ADDR;

                // READ THE INTEGER STORED IN THE MEMORY ADDRESS
            } else if (cmd == "DELETE") {
                unsigned int PID;
                cin >> PID;

                // DELETE THE KEY PID FROM THE HASH TABLE
            } else if (cmd == "PRINT") {
                unsigned int m;
                cin >> m;

                // PRINT THE CHAIN OF STORED KEYS IN POSITION M OF THE HASH TABLE
                // ONLY FOR SEPARATE CHAINING, NOT DOUBLE HASHING
            } else if (cmd == "END") {
                break;
            }
        }
        delete table;
    }
    delete memory;
    return 0;
}