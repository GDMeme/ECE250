#include <iostream>
#include <fstream>
#include <string>
#include <climits>

#include "illegal_exception.h"
#include "Graph.h"

using namespace std;

bool checkInvalid(int a, int b, int w) {
    if (a <= 0 || a > 50000 || b <= 0 || b > 50000 || w <= 0) {
        return true;
    }
    return false;
}

int main() {
    string cmd;
    Graph* myGraph = new Graph();
    while (cin >> cmd) {
        if (cmd == "LOAD") {
            string fName;
            cin >> fName;
            ifstream fin(fName.c_str()); // variable as filename
            int a, b, w;
            fin >> a; // don't need number of vertices
            while (fin >> a) {
                fin >> b;
                fin >> w;
                myGraph->addEdge(a, b, w, false);
            }
            cout << "success" << endl;
        } else if (cmd == "INSERT") {
            int a, b, w;
            cin >> a;
            cin >> b;
            cin >> w;
            try {
                if (checkInvalid(a, b, w)) {
                    throw illegal_exception();
                }
                // if got here, everything is valid
                myGraph->addEdge(a, b, w, true);
            }
            catch (illegal_exception e) {
                e.print();
            }
        } else if (cmd == "PRINT") {
            int a;
            cin >> a;
            try {
                if (checkInvalid(a, 1, 1)) { // 1, 1 are arbitrary valid placeholders to check a
                    throw illegal_exception();
                }
                // if got here, everything is valid
                myGraph->printVertices(a);
            }
            catch (illegal_exception e) {
                e.print();
            }
        } else if (cmd == "DELETE") {
            int a;
            cin >> a;
            try {
                if (checkInvalid(a, 1, 1)) {
                    throw illegal_exception();
                }
                // if got here, everything is valid
                myGraph->deleteVertex(a);
            }
            catch (illegal_exception e) {
                e.print();
            }
        } else if (cmd == "MST") {
            myGraph->primMST(true);
        } else if (cmd == "COST") {
            myGraph->primMST(false);
        } else if (cmd == "END") {
            break;
        }
    }
    delete myGraph;
}