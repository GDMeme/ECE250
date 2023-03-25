#include <iostream>
#include <fstream>
#include <string>

#include "illegal_exception.h"
#include "VertexSet.h"

using namespace std;

bool checkInvalid(int a, int b, int w) {
    if (a <= 0 || a > 50000 || b <= 0 || b > 50000 || w <= 0) {
        return true;
    }
    return false;
}

int main() {
    string cmd;
    VertexSet* allVertex;
    while (cin >> cmd) {
        if (cmd == "LOAD") {
            string fName;
            cin >> fName;
            ifstream fin(fName.c_str()); //Note that we are using the variable as the filename
            //Now do your parsing here. Remember to #include <fstream> at the top!
        } else if (cmd == "INSERT") {
            int a; 
            int b;
            int w;
            cin >> a;
            cin >> b;
            cin >> w; 
            try {
                if (checkInvalid(a, b, w)) {
                    throw illegal_exception();
                }
                // if got here, everything is valid
                std::vector<Vertex*> allVertexSet = allVertex->getVertexSet();
                int indexA{-1};
                int indexB{-1};
                for (int i = 0; i < allVertexSet.size(); i++) {
                    if (allVertexSet[i]->getNumber() == a) {
                        indexA = i;
                        continue;
                    }
                    if (allVertexSet[i]->getNumber() == b) {
                        indexB = i;
                        continue;
                    }
                }
                if (indexA == -1) {
                    Vertex *newVertex = new Vertex(a);
                }
                if (indexB == -1) {
                    Vertex *newVertex = new Vertex(b);
                }
            }
            catch (illegal_exception e) {
                e.print();
            }
        } else if (cmd == "PRINT") {
            int a;
            cin >> a;
            try {
                if (checkInvalid(a, 1, 1)) {
                    throw illegal_exception();
                }
                // if got here, everything is valid
                // do something
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
                // do something
            }
            catch (illegal_exception e) {
                e.print();
            }
        } else if (cmd == "MST") {
            // do something
        } else if (cmd == "COST") {
            // do something
        } else if (cmd == "END") {
            break;
        }
    }
}