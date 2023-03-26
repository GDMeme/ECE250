#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

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

        std::vector<std::tuple<int, int>> getAdjacencyList (int index) {
            return adjacencyList[index];
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

        int getExistingVerticeSize() {
            return existingVertices.size();
        }

        int getExistingVertices(int index) {
            return existingVertices[index];
        }

        void addEdge(int a, int b, int w, bool flag) {
            for (int i = 0; i < adjacencyList[a].size(); i++) {
                if (std::get<1>(adjacencyList[a][i]) == b) { // edge is already in the graph
                    if (flag) {
                        std::cout << "failure" << std::endl;
                    }
                    return;
                }
            }
            if (flag) {
                std::cout << "success" << std::endl;
            }
            if (adjacencyList[a].size() == 0) {
                numberOfVertices++;
                existingVertices.push_back(a);
            }
            if (adjacencyList[b].size() == 0) {
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
            for (int i = 0; i < adjacencyList[a].size(); i++) {
                int vertexNumber = std::get<1>(adjacencyList[a][i]);
                std::vector<std::tuple<int, int>> vertexVector = adjacencyList[vertexNumber];
                for (int j = 0; j < vertexVector.size(); j++) { // remove connected edges from other vertices
                    if (std::get<1>(vertexVector[j]) == a) {
                        adjacencyList[vertexNumber].erase(adjacencyList[vertexNumber].begin() + j);
                        if (adjacencyList[vertexNumber].size() == 0) {
                            numberOfVertices--;
                            for (int k = 0; k < existingVertices.size(); k++) { // remove vertex from existing vertices
                                if (existingVertices[k] == vertexNumber) {
                                    existingVertices.erase(existingVertices.begin() + k);
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
            }
            adjacencyList[a].clear(); // remove all edges from vertex a
            numberOfVertices--;
            for (int i = 0; i < existingVertices.size(); i++) { // remove vertex from existing vertices
                if (existingVertices[i] == a) {
                    existingVertices.erase(existingVertices.begin() + i);
                    break;
                }
            }
            std::cout << "success" << std::endl;
            return;
        }
};