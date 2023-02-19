#pragma once

#include "Node.h"
#include <iostream>

class Trie {
    private:
        Node* root;
        int size;
    public:
        Trie() {
            this->root = new Node;
            this->size = 0;
        }

        ~Trie(){ }

        int getSize() {
            return size;
        }

        void changeSize(int value) { // 1 to increment, 0 to clear, -1 to decrement
            if (value != 0) {
                size += value;
            } else {
                size = 0;
            }
            return;
        }

        Node *getRoot() {
            return root;
        }

        void insertWord(string word) {

            return;
        }

        int count(string prefix) {

            return 0;
        }

        void erase(string word) {

            return;
        }

        void print() {

            return;
        }

        void spellCheck(string word)  {

            return;
        }

        void checkEmpty() {

            return;
        }

        void clear() {

            return;
        }
};