#pragma once

class Node {
    private:
        Node** letterArray;
        bool terminal;
    public:
        Node() {
            this->letterArray = new Node* [26]{nullptr};
            this->terminal = false;
        }

        void setTerminal(bool value) {
            terminal = value;
            return;
        }

        Node *getLetterArray(int index) {
            return letterArray[index];
        }

        void setLetterArray(int index, Node *newNode) {
            letterArray[index] = newNode;
            return;
        }
};