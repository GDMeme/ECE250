#include <iostream>
#include <fstream>
#include <string>
#include <climits>

#include "illegal_exception.h"
#include "Graph.h"
#include "MinHeap.h"
#include "MinHeapNode.h"

using namespace std;

bool checkInvalid(int a, int b, int w) {
    if (a <= 0 || a > 50000 || b <= 0 || b > 50000 || w <= 0) {
        return true;
    }
    return false;
}

void primMST(Graph* graph, bool flag) {
    int V = graph->getV(); // Get the number of vertices in graph
    if (V == 0) {
        if (flag) {
            std::cout << "failure" << std::endl;
        } else {
            std::cout << "cost is 0" << std::endl;
        }
        return;
    }
    MinHeap *minHeap = new MinHeap(V);

    int parent[V]; // Array to store constructed MST
    int key[V]; // Key values used to pick minimum weight
                // edge in cut

    int arrayToLink [50001];
    int arrayToLinkBack [V];

    // Initialize min heap with all vertices. Key value of
    // all vertices (except 0th vertex) is initially
    // infinite
    for (int i = 1; i < V; i++) {
        parent[i] = -1;
        key[i] = INT_MAX;
        MinHeapNode* newNode = new MinHeapNode(i, key[i], graph->getExistingVertices(i));
        minHeap->setArray(i, newNode);
        minHeap->setArrayToDelete(i, newNode);
        arrayToLink[graph->getExistingVertices(i)] = i;
        arrayToLinkBack[i] = graph->getExistingVertices(i);
        minHeap->setPos(i, i); // corresponds to V
    }

    // Make key value of 0th vertex as 0 so that it
    // is extracted first
    key[0] = 0;
    MinHeapNode* newNode = new MinHeapNode(0, key[0], graph->getExistingVertices(0));
    arrayToLink[graph->getExistingVertices(0)] = 0;
    arrayToLinkBack[0] = graph->getExistingVertices(0);
    // std::cout << "0: " << arrayToLinkBack[0] << std::endl;
    // std::cout << "1: " << arrayToLinkBack[1] << std::endl;
    minHeap->setArray(0, newNode);
    minHeap->setArrayToDelete(0, newNode);
    minHeap->setPos(0, 0);

    for (int i = V/2; i > 0; i--) {
        minHeap->minHeapify(minHeap, i);
    }

    // In the following loop, min heap contains all nodes
    // not yet added to MST.
    while (minHeap->getSize() != 0) {
        // Extract the vertex with minimum key value
        MinHeapNode* minHeapNode = minHeap->extractMin(minHeap); // this calls heapify
        // std::cout << "min is: " << minHeapNode->getVertexNumber() << std::endl;
        int currentVertexNumber = minHeapNode->getVertexNumber();
        // Traverse through all adjacent vertices of u (the
        // extracted vertex) and update their key values
        for (int i = 0; i < graph->getAdjacencyListSize(currentVertexNumber); i++) {
            int currentDest = arrayToLink[graph->getAdjacencyListDest(currentVertexNumber, i)]; // 0 to # of vertexes
            // currentDest is only used for the index value for key, parent

            // If v is not yet included in MST and weight of
            // u-v is less than key value of v, then update
            // key value and parent of v
            if (minHeap->getPos(currentDest) < minHeap->getSize() // currentDest is not yet in MST
                    && graph->getAdjacencyListWeight(minHeapNode->getVertexNumber(), i) <= key[currentDest]) { 
                        // weight of edge is less than key value of currentDest
                key[currentDest] = graph->getAdjacencyListWeight(minHeapNode->getVertexNumber(), i); 
                // set equal to the edge weight value
                parent[currentDest] = minHeapNode->getV(); // V is how the parents are linked to child
                minHeap->decreaseKey(minHeap, currentDest, key[currentDest]);
            }
        }
    }

    // print edges of MST
    if (flag) {
        // std::cout << std::endl;
        for (int i = 1; i < V; i++) {
            // std::cout << "parent[i] is: " << parent[i] << std::endl;
            std::cout << arrayToLinkBack[parent[i]] << " " << arrayToLinkBack[i] << " " << key[i] << " ";
        }
        std::cout << std::endl;
    } else {
        int sum = 0;
        for (int i = 1; i < V; i++) {
            sum += key[i];
        }
        std::cout << "cost is " << sum << std::endl;
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
            // cout << "number of vertices is " << myGraph->getV() << std::endl;
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
                if (checkInvalid(a, 1, 1)) { // 1, 1 are arbitrary valid placeholders
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
        // std::cout << "number of vertices is " << myGraph->getV() << std::endl;
    }
    delete myGraph;
}