#pragma once

class MinHeapNode {
    private:
        int v;
        int key;
        int vertexNumber;

    public:
        MinHeapNode(int v, int key, int vertexNumber) {
            this->v = v; // 0, 1, 2, ... # of vertices (arbitrary number to keep track of vertices)
            this->key = key; // weight to get to this
            this->vertexNumber = vertexNumber; // the actual station number
        }

        ~MinHeapNode() {}

        int getKey() {
            return key;
        }

        int getV() {
            return v;
        }

        void setKey(int key) {
            this->key = key;
            return;
        }

        int getVertexNumber() {
            return vertexNumber;
        }
};