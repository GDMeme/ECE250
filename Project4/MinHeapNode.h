#pragma once

class MinHeapNode {
    private:
        int v;
        int key;

    public:
        MinHeapNode(int v, int key) {
            this->v = v;
            this->key = key;
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

};