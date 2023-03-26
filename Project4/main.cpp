#include <iostream>
#include <fstream>
#include <string>
#include <climits>

#include "illegal_exception.h"
#include "Graph.h"
#include "MinHeap.h"

using namespace std;

bool checkInvalid(int a, int b, int w) {
    if (a <= 0 || a > 50000 || b <= 0 || b > 50000 || w <= 0) {
        return true;
    }
    return false;
}

void primMST(Graph* graph, bool flag) {
    int numberOfVertices = graph->getNumberOfVertices();
    if (numberOfVertices == 0) { // empty graph
        if (flag) {
            std::cout << "failure" << std::endl;
        } else {
            std::cout << "cost is 0" << std::endl;
        }
        return;
    }
    MinHeap *minHeap = new MinHeap(numberOfVertices);

    int parent[numberOfVertices]; // stores constructed MST
    int key[numberOfVertices]; // stores weight to get to corresponding vertice

    int arrayToLink [50001];
    int arrayToLinkBack [numberOfVertices];

    // initialize all vertices (except 0th index) 
    for (int i = 1; i < numberOfVertices; i++) {
        parent[i] = -1; // no parent yet
        key[i] = INT_MAX; // so that any edge is better than the default key
        MinHeapNode* newNode = new MinHeapNode(i, key[i], graph->getExistingVertices(i));
        minHeap->setArray(i, newNode);
        minHeap->setArrayToDelete(i, newNode);
        arrayToLink[graph->getExistingVertices(i)] = i;
        arrayToLinkBack[i] = graph->getExistingVertices(i);
        minHeap->setPos(i, i); // maps vertice to position in array
    }

    // setting 0th index
    key[0] = 0;
    MinHeapNode* newNode = new MinHeapNode(0, key[0], graph->getExistingVertices(0));
    arrayToLink[graph->getExistingVertices(0)] = 0;
    arrayToLinkBack[0] = graph->getExistingVertices(0);
    minHeap->setArray(0, newNode);
    minHeap->setArrayToDelete(0, newNode);
    minHeap->setPos(0, 0);

    // building heap
    for (int i = numberOfVertices/2; i > 0; i--) {
        minHeap->minHeapify(i);
    }

    // minHeap has all nodes not in MST yet
    while (minHeap->getSize() != 0) {
        MinHeapNode* minHeapNode = minHeap->extractMin(); // this calls heapify
        int currentStationNumber = minHeapNode->getStationNumber();
        // check all adjacent destinations to (possibly) update their key values
        for (int i = 0; i < graph->getAdjacencyListSize(currentStationNumber); i++) {
            int currentDest = arrayToLink[graph->getAdjacencyListDest(currentStationNumber, i)]; // 0 to # of vertexes
            // currentDest is only used for the index value for key, parent

            if (minHeap->getPos(currentDest) < minHeap->getSize() // currentDest is not yet in MST
                    && graph->getAdjacencyListWeight(minHeapNode->getStationNumber(), i) <= key[currentDest]) {
                        // weight of edge is less than key value of currentDest
                        // meaning need to update key
                key[currentDest] = graph->getAdjacencyListWeight(minHeapNode->getStationNumber(), i); 
                // set equal to the edge weight value
                parent[currentDest] = minHeapNode->getVertexNumber(); // VertexNumber is how the nodes are linked through parent
                minHeap->modifyKey(currentDest, key[currentDest]);
            }
        }
    }
    if (flag) { // print edges of MST
        for (int i = 1; i < numberOfVertices; i++) {
            cout << arrayToLinkBack[parent[i]] << " " << arrayToLinkBack[i] << " " << key[i] << " ";
        }
        cout << endl;
    } else { // calculate cost
        int sum = 0;
        for (int i = 1; i < numberOfVertices; i++) {
            sum += key[i];
        }
        cout << "cost is " << sum << endl;
    }
    delete minHeap;
    return;
}

int main() {
    string cmd;
    Graph* myGraph = new Graph();
    while (cin >> cmd) {
        if (cmd == "LOAD") {
            string fName;
            cin >> fName;
            ifstream fin(fName.c_str()); // Note we are using the variable as the filename
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
                if (checkInvalid(a, 1, 1)) { // 1, 1 are arbitrary valid placeholders, only need to check a
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
            primMST(myGraph, true);
        } else if (cmd == "COST") {
            primMST(myGraph, false);
        } else if (cmd == "END") {
            break;
        }
    }
    delete myGraph;
}