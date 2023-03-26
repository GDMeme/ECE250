#pragma once

class MinHeapNode {
    private:
        int vertexNumber; // 0, 1, 2, ... # of vertices (arbitrary number to keep track of vertices)
        int key; // weight to get to this node
        int stationNumber; // the actual station number

    public:
        MinHeapNode(int vertexNumber, int key, int stationNumber) {
            this->vertexNumber = vertexNumber; 
            this->key = key;
            this->stationNumber = stationNumber;
        }

        ~MinHeapNode() { }

        int getKey() {
            return key;
        }

        int getVertexNumber() {
            return vertexNumber;
        }

        void setKey(int key) {
            this->key = key;
            return;
        }

        int getStationNumber() {
            return stationNumber;
        }
};