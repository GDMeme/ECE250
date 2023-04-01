#pragma once

#include <iostream>
#include <vector>
#include <tuple>

#include "MinHeapNode.h"

class MinHeap {

    private:
        int size; // current number of heap nodes in the heap
        int capacity; // max size of heap
        int *stationToIndex; // maps station number to unknownVertices index
        MinHeapNode** unknownVertices; // contains all vertices not yet added to MST
        MinHeapNode** verticesToDelete; // to delete all MinHeapNodes

    public:
        MinHeap(int capacity) {
            this->size = capacity;
            this->capacity = capacity; // for the destructor
            this->stationToIndex = new int [capacity];
            this->unknownVertices = new MinHeapNode* [capacity];
            this->verticesToDelete = new MinHeapNode* [capacity];
        }

        ~MinHeap() {
            for (int i = 0; i < capacity; i++) {
                delete verticesToDelete[i];
            }
            delete[] verticesToDelete;
            delete[] unknownVertices;
            delete[] stationToIndex;
        }

        void setVerticesToDelete(int index, MinHeapNode* value) {
            verticesToDelete[index] = value;
            return;
        }

        void setUnknownVertices(int index, MinHeapNode* value) {
            unknownVertices[index] = value;
            return;
        }

        int getStationToIndex(int index) {
            return stationToIndex[index];
        }

        void setStationToIndex(int index, int value) {
            stationToIndex[index] = value;
            return;
        }

        int getSize() {
            return size;
        }

        void minHeapify(int index) { // start at index node and go down the tree, swapping if needed
            int currentSmallest, leftChild, rightChild;
            currentSmallest = index;
            leftChild = 2 * index + 1;
            rightChild = 2 * index + 2;
        
            if (leftChild < size && // left child exists in the heap so no index out of bound
                    unknownVertices[leftChild]->getKey() < unknownVertices[currentSmallest]->getKey()) { // new smallest found
                currentSmallest = leftChild;
            }
        
            if (rightChild < size && // right child exists in the heap so no index out of bound
                    unknownVertices[rightChild]->getKey() < unknownVertices[currentSmallest]->getKey()) { // new smallest found
                currentSmallest = rightChild;
            }
        
            if (currentSmallest != index) { // new smallest found, need to swap
                MinHeapNode* smallestNode = unknownVertices[currentSmallest];
                MinHeapNode* indexNode = unknownVertices[index];
        
                // swap positions in stationToIndex
                stationToIndex[smallestNode->getVertexNumber()] = index;
                stationToIndex[indexNode->getVertexNumber()] = currentSmallest;
        
                // swap nodes in unknownVertices
                MinHeapNode* temp = smallestNode;
                unknownVertices[currentSmallest] = indexNode;
                unknownVertices[index] = temp;

                minHeapify(currentSmallest);
            }
        }

        MinHeapNode* extractMin() {
            MinHeapNode* minNode = unknownVertices[0]; // root is the min node
        
            // put last node as root node in unknownVertices
            MinHeapNode* lastNode = unknownVertices[size - 1];
            unknownVertices[0] = lastNode;
        
            // update position of root and last node in stationToIndex
            stationToIndex[minNode->getVertexNumber()] = size - 1;
            stationToIndex[lastNode->getVertexNumber()] = 0;
        
            // reduce heap size (gets rid of extracted minimum node)
            size--;

            // heapify root (make in a min heap again)
            minHeapify(0);
        
            return minNode;
        }

        void modifyKey(int currentDest, int key) { 
            // update key of index of current destination
            int i = stationToIndex[currentDest];
            unknownVertices[i]->setKey(key);
        
            int parent = (i - 1) / 2;

            // make it a min heap again
            // different than minHeapify so can't call that
            // starting from currentDest and going up the tree, swapping if needed
            while (i > 0 && unknownVertices[i]->getKey() < unknownVertices[parent]->getKey()) { // need to swap
                // swap positions in stationToIndex
                stationToIndex[unknownVertices[i]->getVertexNumber()] = (i - 1) / 2;
                stationToIndex[unknownVertices[parent]->getVertexNumber()] = i;

                // swap nodes in unknownVertices
                MinHeapNode *temp = unknownVertices[i];
                unknownVertices[i] = unknownVertices[parent];
                unknownVertices[parent] = temp;
        
                // update i and parent value
                i = (i - 1) / 2;
                parent = (i - 1) / 2;
            }
        }
};