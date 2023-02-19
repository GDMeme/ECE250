#pragma once

#include "Node.h"
#include <iostream>

class Trie {
    private:
        Node* root;
        int size;

        int findCombinations (Node *currentNode) {
            int counter = 0;
            Node *nextNode;
            if (currentNode->getTerminal() == true) {
                counter++;
            }
            for (int i = 0; i <= 25; i++) {
                nextNode = currentNode->getLetterArray(i);
                if (nextNode != nullptr) {
                    counter += findCombinations(nextNode);
                }
            }
            return counter;
        }

    public:
        Trie() {
            this->root = new Node;
            this->size = 0;
        }

        ~Trie(){ }

        int getSize() {
            return size;
        }

        bool insertWord(string word) {
            Node *currentNode = root;
            Node *nextNode;
            for (int i = 0; i < word.size(); i++) {
                nextNode = currentNode->getLetterArray(word[i] - 'A');
                if (nextNode == nullptr) { // new node
                    Node *newNode = new Node();
                    currentNode->setLetterArray(word[i] - 'A', newNode);
                    currentNode = newNode;
                    if (i == word.size() - 1) {
                        currentNode->setTerminal(true);
                        size++;
                        return true;
                    }
                } else {
                    currentNode = nextNode;
                    if (i == word.size() - 1) { // possible duplicate found
                        if (currentNode->getTerminal() == true) { // duplicate found
                            return false; 
                        } else {
                            std::cout << "success" << endl;
                            currentNode->setTerminal(true);
                            size++;
                            return true;
                        }
                    }
                }
            }
            std::cout << "How did you get here?" << std::endl;
        }

        void count(string prefix) {
            int counter = 0;
            Node *currentNode = root;
            Node *nextNode;
            for (int i = 0; i < prefix.size(); i++) {
                nextNode = currentNode->getLetterArray(prefix[i] - 'A');
                if (nextNode == nullptr) {
                    counter = findCombinations(currentNode);
                    break;
                } else {
                    currentNode = nextNode;
                    if (i == prefix.size() - 1) { // the entire prefix exists in the trie
                        counter = findCombinations(currentNode);
                    }
                }
            }
            if (counter == 0) {
                cout << "not found" << endl;
            } else {
                cout << "count is " << counter << endl;
            }
            return;
        }

        void erase(string word) {
            Node *currentNode = root;
            Node *nextNode;
            std::vector<Node*> path;
            path.push_back(root);
            for (int i = 0; i < word.size(); i++) {
                nextNode = currentNode->getLetterArray(word[i] - 'A');
                if (nextNode == nullptr) { // next letter was not found
                    std::cout << "failure" << std::endl; 
                    return;
                } 
                currentNode = nextNode;
                path.push_back(currentNode);
            }
            // if got here, entire word was found
            if (currentNode->getTerminal() == true) {
                std::cout << "success" << std::endl;
                currentNode->setTerminal(false);
                return;
            } else { // word was not actually found
                std::cout << "failure" << std::endl; // it was just part of a longer word
                return;
            }
            // check if I can delete nodes
            for (int i = path.size() - 1; i > 0; i--) { // DON'T DELETE THE ROOT
                bool deleteNode = true;
                for (int j = 0; j <= 25; j++) {
                    if (path[i]->getLetterArray(j) != nullptr) {
                        deleteNode = false;
                        break;
                    }
                }
                if (deleteNode && path[i]->getTerminal() == false) {
                    delete path[i];
                    path[i - 1]->setLetterArray(word[i - 1] - 'A', nullptr);
                } else {
                    break;
                }
            }
            std::cout << "success" << std::endl;
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