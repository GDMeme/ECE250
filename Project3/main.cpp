#include "Trie.h"
#include "illegal_exception.h"

#include <iostream>
#include <fstream>

using namespace std;

int main() {
    Trie* myTrie = new Trie();
    ifstream fin("corpus.txt");

    string cmd;
    string addWord;
    while(cin >> cmd) {
        if (cmd == "load") {
            while (fin >> addWord) {
                myTrie->insertWord(addWord);
            }
            cout << "success" << endl;
        } else if (cmd == "i") {
            cin >> addWord;
            bool illegal{false};
            Node *currentNode = myTrie->getRoot();
            try {
                for (int i = 0; i < addWord.size(); i++) {
                    if (!isalpha(addWord[i]) || !isupper(addWord[i])) {
                        throw illegal_exception();
                    }
                    if (currentNode->getLetterArray(addWord[i] - 'a') == nullptr) { // new node
                        Node *newNode = new Node();
                        currentNode->setLetterArray(addWord[i] - 'a', newNode);
                        currentNode = newNode;
                        if (i == addWord.size() - 1) {
                            currentNode->setTerminal(true);
                        }
                    } else {
                        currentNode = currentNode->getLetterArray(addWord[i] - 'a');
                        if (i == addWord.size() - 1) {
                            currentNode->setTerminal(true);
                        }
                    }
                }
            }
            catch (illegal_exception e) {
                e.print();
                illegal = true;
            }
            if (!illegal) {
                myTrie->insertWord(addWord);
            }
        } else if (cmd == "c") {
            string prefix;
            cin >> prefix;
            bool illegal{false};
            try {
                for (int i = 0; i < prefix.size(); i++) {
                    if (!isalpha(prefix[i]) || !isupper(prefix[i])) {
                        throw illegal_exception();
                    }
                }
            }
            catch (illegal_exception e) {
                e.print();
                illegal = true;
            }
            if (!illegal) {
                cout << myTrie->count(prefix) << endl;
            }
        } else if (cmd == "e") {
            string removeWord;
            bool illegal{false};
            try {
                for (int i = 0; i < removeWord.size(); i++) {
                    if (!isalpha(removeWord[i]) || !isupper(removeWord[i])) {
                        throw illegal_exception();
                    }
                }
            }
            catch (illegal_exception e) {
                e.print();
                illegal = true;
            }
            if (!illegal) {
                myTrie->erase(removeWord);
            }
        } else if (cmd == "p") {
            myTrie->print();
        } else if (cmd == "spellcheck") {
            string word;
            cin >> word;
            myTrie->spellCheck(word);
        } else if (cmd == "empty") {
            myTrie->checkEmpty();
        } else if (cmd == "clear") {
            myTrie->clear();
        } else if (cmd == "size") {
            cout << myTrie->getSize() << endl;
        } else if (cmd == "exit") {
            break;
        }
    }
    delete myTrie;
}