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

        void minHeapify(MinHeap* minHeap, int idx) {
            int smallest, left, right;
            smallest = idx;
            left = 2 * idx + 1;
            right = 2 * idx + 2;
        
            if (left < minHeap->size && minHeap->array[left]->getKey() < minHeap->array[smallest]->getKey()) {
                // std::cout << "i got here" << std::endl;
                // std::cout << "left is " << left << std::endl;
                // std::cout << minHeap->size << std::endl << minHeap->array[left]->getKey() << std::endl << minHeap->array[smallest]->getKey() << std::endl;
                smallest = left;
            }
        
            if (right < minHeap->size && minHeap->array[right]->getKey() < minHeap->array[smallest]->getKey()) {
                // std::cout << "smallest=right" << std::endl;
                smallest = right;
            }
        
            if (smallest != idx) { // need to swap
                // std::cout << "nee dto swap" << std::endl;
                // The nodes to be swapped in min heap
                MinHeapNode* smallestNode = minHeap->array[smallest];
                MinHeapNode* idxNode = minHeap->array[idx];
        
                // Swap positions
                minHeap->pos[smallestNode->getV()] = idx;
                minHeap->pos[idxNode->getV()] = smallest;
        
                // Swap nodes
                MinHeapNode* temp = smallestNode;
                minHeap->array[smallest] = idxNode;
                minHeap->array[idx] = temp;
                // std::cout << "array start" << std::endl;
                // for (int i = 0; i < 4; i++) {
                //     std::cout << minHeap->array[i]->getKey() << " ";
                // }
                // std::cout << std::endl;
                minHeapify(minHeap, smallest);
            }
        }

        MinHeapNode* extractMin(MinHeap* minHeap) {
            if (size == 0)
                return NULL;
        
            // Store the root node
            MinHeapNode* root = minHeap->array[0];
        
            // Replace root node with last node
            MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
            minHeap->array[0] = lastNode;
        
            // Update position of last node
            minHeap->pos[root->getV()] = minHeap->size - 1;
            minHeap->pos[lastNode->getV()] = 0;
        
            // Reduce heap size and heapify root
            minHeap->size--;
            minHeapify(minHeap, 0);
        
            return root;
        }

        void decreaseKey(MinHeap* minHeap, int currentDest, int key) {
            // Get the index of v in heap array
            int i = minHeap->pos[currentDest];
        
            // Get the node and update its key value
            minHeap->array[i]->setKey(key);
        
            // Travel up while the complete tree is not heapified.
            // This is a O(Logn) loop
            while (i && minHeap->array[i]->getKey() < minHeap->array[(i - 1) / 2]->getKey()) {
                // Swap this node with its parent
                minHeap->pos[minHeap->array[i]->getV()] = (i - 1) / 2;
                minHeap->pos[minHeap->array[(i - 1) / 2]->getV()] = i;

                MinHeapNode *temp = minHeap->array[i];
                minHeap->array[i] = minHeap->array[(i - 1) / 2];
                minHeap->array[(i - 1) / 2] = temp;
                // swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        
                // move to parent index
                i = (i - 1) / 2;
            }
        }
};