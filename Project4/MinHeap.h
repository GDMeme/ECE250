#pragma once

#include <iostream>
#include <vector>
#include <tuple>

#include "MinHeapNode.h"

class MinHeap {

    private:
        int size; // current number of heap nodes in the heap
        int capacity; // max size of heap
        int *pos; // Node position number in the heap (1, 2, 3, ...)
        MinHeapNode** array; // contains all vertices not yet added to MST
        MinHeapNode** arrayToDelete; // to delete all MinHeapNodes

    public:
        MinHeap(int capacity) {
            this->size = capacity; // Initially size of min heap is equal to V
            this->capacity = capacity;
            this->pos = new int [capacity];
            this->array = new MinHeapNode* [capacity];
            this->arrayToDelete = new MinHeapNode* [capacity];
        }

        ~MinHeap() {
            for (int i = 0; i < capacity; i++) {
                delete arrayToDelete[i];
            }
            delete[] arrayToDelete;
            delete[] array;
            delete[] pos;
        }

        void setArrayToDelete(int index, MinHeapNode* newNode) {
            arrayToDelete[index] = newNode;
            return;
        }

        MinHeapNode* getArray(int index) {
            return array[index];
        } 

        void setArray(int index, MinHeapNode* minHeapNode) {
            array[index] = minHeapNode;
            return;
        }

        int getPos(int index) {
            return pos[index];
        }

        void setPos(int index, int value) {
            pos[index] = value;
            return;
        }

        void setSize(int size) {
            this->size = size;
            return; 
        }

        int getSize() {
            return size;
        }

        void minHeapify(int index) {
            int smallest, leftChild, rightChild;
            smallest = index;
            leftChild = 2 * index + 1;
            rightChild = 2 * index + 2;
        
            if (leftChild < size && // left child exists in the heap
                    array[leftChild]->getKey() < array[smallest]->getKey()) { // new smallest found
                smallest = leftChild;
            }
        
            if (rightChild < size && // right child exists in the heap
                    array[rightChild]->getKey() < array[smallest]->getKey()) { // new smallest found
                smallest = rightChild;
            }
        
            if (smallest != index) { // need to swap
                MinHeapNode* smallestNode = array[smallest];
                MinHeapNode* indexNode = array[index];
        
                // swap positions
                pos[smallestNode->getVertexNumber()] = index;
                pos[indexNode->getVertexNumber()] = smallest;
        
                // swap nodes in array
                MinHeapNode* temp = smallestNode;
                array[smallest] = indexNode;
                array[index] = temp;

                minHeapify(smallest);
            }
        }

        MinHeapNode* extractMin() {
            if (size == 0)
                return NULL;
        
            MinHeapNode* minNode = array[0];
        
            // swap root and last node
            MinHeapNode* lastNode = array[size - 1];
            array[0] = lastNode;
        
            // update position of root and last node
            pos[minNode->getVertexNumber()] = size - 1;
            pos[lastNode->getVertexNumber()] = 0;
        
            // reduce heap size (gets rid of extracted minimum node)
            size--;

            // heapify root
            minHeapify(0);
        
            return minNode;
        }

        void modifyKey(int currentDest, int key) {
            // index of current destination
            int i = pos[currentDest];
        
            // update key
            array[i]->setKey(key);
        
            int parent = (i - 1) / 2;

            // heapify
            while (i && 
                    array[i]->getKey() < array[parent]->getKey()) { // need to swap
                // swap positions
                pos[array[i]->getVertexNumber()] = (i - 1) / 2;
                pos[array[parent]->getVertexNumber()] = i;

                // swap nodes in array
                MinHeapNode *temp = array[i];
                array[i] = array[parent];
                array[parent] = temp;
        
                i = (i - 1) / 2;
                parent = (i - 1) / 2;
            }
        }
};