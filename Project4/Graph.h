#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

#include "MinHeap.h"

class Graph {
    private:
        std::vector<std::tuple<int, int>>* adjacencyList;
        int numberOfVertices;
        std::vector<int> existingVertices;

    public:
        Graph() {
            this->adjacencyList = new std::vector<std::tuple<int, int>> [50001];
            this->numberOfVertices = 0;
        }

        ~Graph() {
            delete[] adjacencyList;
        }

        int getNumberOfVertices() {
            return numberOfVertices;
        }

        int getAdjacencyListDest(int firstIndex, int secondIndex) {
            return std::get<1>(adjacencyList[firstIndex][secondIndex]);
        }

        int getAdjacencyListWeight(int firstIndex, int secondIndex) {
            return std::get<0>(adjacencyList[firstIndex][secondIndex]);
        }

        int getAdjacencyListSize(int index) {
            return adjacencyList[index].size();
        }

        int getExistingVertices(int index) {
            return existingVertices[index];
        }

        void addEdge(int a, int b, int w, bool flag) { // flag determines whether to output anything
            for (int i = 0; i < adjacencyList[a].size(); i++) {
                if (std::get<1>(adjacencyList[a][i]) == b) { // edge was found already in the graph
                    if (flag) {
                        std::cout << "failure" << std::endl;
                    }
                    return;
                }
            }
            // if got here, need to add the edge
            if (flag) {
                std::cout << "success" << std::endl;
            }
            if (adjacencyList[a].size() == 0) { // adding a new vertice
                numberOfVertices++;
                existingVertices.push_back(a);
            }
            if (adjacencyList[b].size() == 0) { // adding a new vertice
                numberOfVertices++;
                existingVertices.push_back(b);
            }
            adjacencyList[a].push_back(std::make_tuple(w, b));
            adjacencyList[b].push_back(std::make_tuple(w, a));
            return;
        }

        void printVertices(int a) {
            if (adjacencyList[a].size() == 0) {
                std::cout << "failure" << std::endl;
                return;
            }
            for (int i = 0; i < adjacencyList[a].size(); i++) {
                std::cout << std::get<1>(adjacencyList[a][i]) << " ";
            }
            std::cout << std::endl;
            return;
        }

        void deleteVertex(int a) {
            if (adjacencyList[a].size() == 0) { // the vertex only exists if there is an edge
                std::cout << "failure" << std::endl;
                return;
            }
            for (int i = 0; i < adjacencyList[a].size(); i++) { // O(E)
                int vertexNumber = std::get<1>(adjacencyList[a][i]);
                std::vector<std::tuple<int, int>> vertexVector = adjacencyList[vertexNumber];
                for (int j = 0; j < vertexVector.size(); j++) { // O(E) remove connected edges from other vertices
                    if (std::get<1>(vertexVector[j]) == a) {
                        adjacencyList[vertexNumber].erase(adjacencyList[vertexNumber].begin() + j); // O(E)
                        break;
                    }
                }
                if (adjacencyList[vertexNumber].size() == 0) {
                    numberOfVertices--;
                    for (int k = 0; k < existingVertices.size(); k++) { // O(V) remove vertex from existing vertices
                        if (existingVertices[k] == vertexNumber) {
                            existingVertices.erase(existingVertices.begin() + k); // O(V)
                            break;
                        }
                    }
                }
            }
            adjacencyList[a].clear(); // remove all edges from vertex a
            numberOfVertices--;
            for (int i = 0; i < existingVertices.size(); i++) { // O(V) remove vertex from existing vertices
                if (existingVertices[i] == a) {
                    existingVertices.erase(existingVertices.begin() + i); // O(V)
                    break;
                }
            }
            std::cout << "success" << std::endl;
            return;
        }

        void primMST(bool flag) { // flag determines whether to output MST or cost
            int numberOfVertices = getNumberOfVertices();
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

            int arrayToLink [50001]; // links from station number to vertex number
            int arrayToLinkBack [numberOfVertices]; // links from vertex number to station number

            // initialize all vertices (except 0th index) 
            for (int i = 1; i < numberOfVertices; i++) {
                parent[i] = -1; // no parent yet
                key[i] = INT_MAX; // so that any edge is better than the default key
                MinHeapNode* newNode = new MinHeapNode(i, key[i], getExistingVertices(i));
                minHeap->setArray(i, newNode);
                minHeap->setArrayToDelete(i, newNode);
                arrayToLink[getExistingVertices(i)] = i;
                arrayToLinkBack[i] = getExistingVertices(i);
                minHeap->setPos(i, i); // maps vertice to position in array
            }

            // setting 0th index
            key[0] = 0;
            MinHeapNode* newNode = new MinHeapNode(0, key[0], getExistingVertices(0));
            arrayToLink[getExistingVertices(0)] = 0;
            arrayToLinkBack[0] = getExistingVertices(0);
            minHeap->setArray(0, newNode);
            minHeap->setArrayToDelete(0, newNode);
            minHeap->setPos(0, 0);

            // building heap
            for (int i = numberOfVertices / 2; i > 0; i--) { // from floor(n/2) to 1
                minHeap->minHeapify(i);
            }

            // minHeap has all nodes not in MST yet
            while (minHeap->getSize() != 0) {
                MinHeapNode* minHeapNode = minHeap->extractMin(); // this calls heapify
                int currentStationNumber = minHeapNode->getStationNumber();
                // check all adjacent destinations to (possibly) update their key values
                for (int i = 0; i < getAdjacencyListSize(currentStationNumber); i++) {
                    int currentDest = arrayToLink[getAdjacencyListDest(currentStationNumber, i)]; // 0 to # of vertexes
                    // currentDest is only used for the index value for key, parent

                    if (minHeap->getPos(currentDest) < minHeap->getSize() // currentDest is not yet in MST
                            && getAdjacencyListWeight(minHeapNode->getStationNumber(), i) <= key[currentDest]) {
                                // weight of edge is less than key value of currentDest
                                // meaning need to update key
                        key[currentDest] = getAdjacencyListWeight(minHeapNode->getStationNumber(), i); 
                        // set equal to the edge weight value
                        parent[currentDest] = minHeapNode->getVertexNumber(); // VertexNumber is how the nodes are linked through parent
                        minHeap->modifyKey(currentDest, key[currentDest]);
                    }
                }
            }
            if (flag) { // print edges of MST
                for (int i = 1; i < numberOfVertices; i++) {
                    std::cout << arrayToLinkBack[parent[i]] << " " << arrayToLinkBack[i] << " " << key[i] << " ";
                }
                std::cout << std::endl;
            } else { // calculate cost
                int sum = 0;
                for (int i = 1; i < numberOfVertices; i++) {
                    sum += key[i];
                }
                std::cout << "cost is " << sum << std::endl;
            }
            delete minHeap;
            return;
        }
};