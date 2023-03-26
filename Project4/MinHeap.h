#pragma once

#include <vector>
#include <tuple>

#include "MinHeapNode.h"

class MinHeap {

    private:
        int size;
        int capacity;
        int *pos;
        std::vector<MinHeapNode*> array;

    public:
        MinHeap() {
            this->size = 0;
            this->capacity = 0;
        }

        ~MinHeap() {
            for (int i = 0; i < array.size(); i++) {
                delete array[i];
            }
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

        void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b) {
            MinHeapNode *temp = *a;
            *a = *b;
            *b = temp;
        }

        void minHeapify(MinHeap* minHeap, int idx) {
            int smallest, left, right;
            smallest = idx;
            left = 2 * idx + 1;
            right = 2 * idx + 2;
        
            if (left < minHeap->size && minHeap->array[left]->getKey() < minHeap->array[smallest]->getKey()) {
                smallest = left;
            }
        
            if (right < minHeap->size && minHeap->array[right]->getKey() < minHeap->array[smallest]->getKey()) {
                smallest = right;
            }
        
            if (smallest != idx) { // need to swap
                // The nodes to be swapped in min heap
                MinHeapNode* smallestNode = minHeap->array[smallest];
                MinHeapNode* idxNode = minHeap->array[idx];
        
                // Swap positions
                minHeap->pos[smallestNode->getV()] = idx;
                minHeap->pos[idxNode->getV()] = smallest;
        
                // Swap nodes
                swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        
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
            --minHeap->size;
            minHeapify(minHeap, 0);
        
            return root;
        }

        void decreaseKey(struct MinHeap* minHeap, int v, int key) {
            // Get the index of v in  heap array
            int i = minHeap->pos[v];
        
            // Get the node and update its key value
            minHeap->array[i]->setKey(key);
        
            // Travel up while the complete tree is not heapified.
            // This is a O(Logn) loop
            while (i && minHeap->array[i]->getKey() < minHeap->array[(i - 1) / 2]->getKey()) {
                // Swap this node with its parent
                minHeap->pos[minHeap->array[i]->getV()] = (i - 1) / 2;
                minHeap->pos[minHeap->array[(i - 1) / 2]->getV()] = i;
                swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        
                // move to parent index
                i = (i - 1) / 2;
            }
        }
};