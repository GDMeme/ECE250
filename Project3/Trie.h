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
            if (currentNode->getTerminal()) {
                counter++;
            }
            for (int i = 0; i < 26; i++) {
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

        ~Trie(){
            clear(root);
            delete root;
        }

        Node *getRoot() {
            return root;
        }

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
                        if (currentNode->getTerminal()) { // duplicate found
                            return false; 
                        } else {
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
                    cout << "not found" << endl;
                    return;
                }
                currentNode = nextNode;
            }
            cout << "count is " << findCombinations(currentNode) << endl;
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
            if (currentNode->getTerminal()) {
                std::cout << "success" << std::endl;
                currentNode->setTerminal(false);
                size--;
            } else { // word was not actually found
                std::cout << "failure" << std::endl; // it was just part of a longer word
                return;
            }
            // check if I can delete nodes
            bool deleteNode;
            for (int i = path.size() - 1; i > 0; i--) { // DON'T DELETE THE ROOT
                deleteNode = true;
                for (int j = 0; j < 26; j++) {
                    if (path[i]->getLetterArray(j) != nullptr) {
                        deleteNode = false;
                        break;
                    }
                }
                if (deleteNode && !path[i]->getTerminal()) {
                    delete path[i];
                    path[i - 1]->setLetterArray(word[i - 1] - 'A', nullptr);
                } else {
                    break;
                }
            }
            return;
        }

        void print(Node *currentNode, string currentString) {
            Node *nextNode;
            for (int i = 0; i < 26; i++) {
                if (currentNode->getTerminal()) {
                    std::cout << currentString << " " << std::endl;
                }
                nextNode = currentNode->getLetterArray(i);
                if (nextNode != nullptr) {
                    print(nextNode, currentString + char(i + 'A'));
                }
            }
            return;
        }

        void spellCheck(string word) {
            Node *currentNode = root;
            Node *nextNode;
            for (int i = 0; i < word.size(); i++) {
                nextNode = currentNode->getLetterArray(word[i] - 'A');
                if (nextNode == nullptr) {
                    print(currentNode, "");
                    return;
                }
                currentNode = nextNode;
            }
            return;
        }

        void clear(Node *currentNode) {
            Node *nextNode;
            for (int i = 0; i < 26; i++) {
                nextNode = currentNode->getLetterArray(i);
                if (nextNode != nullptr) {
                    clear(nextNode);
                    delete nextNode;
                }
            }
            // DON'T DELETE THE ROOT
            return;
        }
};