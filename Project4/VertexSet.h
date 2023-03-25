#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

#include "Vertex.h"

class VertexSet {
    private:
        std::vector<std::tuple<int, int>> adjacencyList [50000]; // 50000 vectors

    public:
        VertexSet() {}

        ~VertexSet() {}

        void addEdge(int a, int b, int w) {
            for (int i = 0; i < adjacencyList[a].size(); i++) {
                if (std::get<1>(adjacencyList[a][i]) == b) { // edge is already in the graph
                    std::cout << "failure" << std::endl;
                    return;
                }
            }
            std::cout << "success" << std::endl;
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
                        vertexVector.erase(vertexVector.begin() + j);
                        break;
                    }
                }
            }
            adjacencyList[a].clear(); // remove all edges from vertex a
            std::cout << "success" << std::endl;
            return;
        }
};