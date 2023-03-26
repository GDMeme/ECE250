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
    MinHeap *minHeap = new MinHeap();
    int V = graph->getV(); // Get the number of vertices in graph
    int parent[V]; // Array to store constructed MST
    int key[V]; // Key values used to pick minimum weight
                // edge in cut

    // Initialize min heap with all vertices. Key value of
    // all vertices (except 0th vertex) is initially
    // infinite
    for (int v = 1; v < V; ++v) {
        parent[v] = -1;
        key[v] = INT_MAX;
        minHeap->setArray(v, new MinHeapNode(v, key[v]));
        minHeap->setPos(v, v);
    }

    // Make key value of 0th vertex as 0 so that it
    // is extracted first
    key[0] = 0;
    minHeap->setArray(0, new MinHeapNode(0, key[0]));
    minHeap->setPos(0, 0);

    // Initially size of min heap is equal to V
    minHeap->setSize(V);

    // In the following loop, min heap contains all nodes
    // not yet added to MST.
    while (minHeap->getSize() != 0) {
        // Extract the vertex with minimum key value
        MinHeapNode* minHeapNode = minHeap->extractMin(minHeap);
        int u = minHeapNode->getV(); // Store the extracted vertex number

        // Traverse through all adjacent vertices of u (the
        // extracted vertex) and update their key values
        for (int i = 0; i < graph->getExistingVerticeSize(); i++) {
            int v = graph->getAdjacencyListDest(graph->getExistingVertices(u), i);

            // If v is not yet included in MST and weight of
            // u-v is less than key value of v, then update
            // key value and parent of v
            if (minHeap->getPos(v) < minHeap->getSize() && graph->getAdjacencyListWeight(graph->getExistingVertices(u), i) < key[v]) {
                key[v] = graph->getAdjacencyListWeight(graph->getExistingVertices(u), i);
                parent[v] = u;
                minHeap->decreaseKey(minHeap, v, key[v]);
            }
        }
    }

    // print edges of MST
    if (flag) {
        for (int i = 1; i < V; i++) {
            std::cout << parent[i] << " " << i << key[i] << " ";
        }
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
    }
    delete myGraph;
}