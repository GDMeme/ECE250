#include "Trie.h"
#include "Node.h"
#include "illegal_exception.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    Trie* myTrie = new Trie();
    ifstream fin;

    string cmd;
    string addWord;
    while(cin >> cmd) {
        if (cmd == "load") {
            fin.open("corpus.txt");
            while (fin >> addWord) {
                myTrie->insertWord(addWord);
            }
            fin.close();
            cout << "success" << endl;
        } else if (cmd == "i") {
            cin >> addWord;
            try {
                for (int i = 0; i < addWord.size(); i++) {
                    if (!isalpha(addWord[i]) || !isupper(addWord[i])) {
                        throw illegal_exception();
                    }
                }
                // if got here, the word is valid
                // but still have to check if the word is already there
                if (myTrie->insertWord(addWord)) {
                    cout << "success" << endl;
                } else {
                    cout << "failure" << endl;
                }
            }
            catch (illegal_exception e) {
                e.print();
            }
        } else if (cmd == "c") {
            string prefix;
            cin >> prefix;
            try {
                for (int i = 0; i < prefix.size(); i++) {
                    if (!isalpha(prefix[i]) || !isupper(prefix[i])) {
                        throw illegal_exception();
                    }
                }
                // if got here, the word is valid
                myTrie->count(prefix);
            }
            catch (illegal_exception e) {
                e.print();
            }
        } else if (cmd == "e") {
            string removeWord;
            cin >> removeWord;
            try {
                for (int i = 0; i < removeWord.size(); i++) {
                    if (!isalpha(removeWord[i]) || !isupper(removeWord[i])) {
                        throw illegal_exception();
                    }
                }
                // if got here, the word is valid
                myTrie->erase(removeWord);
            }
            catch (illegal_exception e) {
                e.print();
            }
        } else if (cmd == "p") {
            myTrie->print(myTrie->getRoot(), "");
            cout << endl;
        } else if (cmd == "spellcheck") {
            string word;
            cin >> word;
            myTrie->spellCheck(word);
            cout << endl;
        } else if (cmd == "empty") {
            string output = myTrie->getSize() == 0 ? "empty 1" : "empty 0";
            cout << output << endl;
        } else if (cmd == "clear") {
            myTrie->clear(myTrie->getRoot());
            myTrie->setSize(0);
            cout << "success" << endl;
        } else if (cmd == "size") {
            cout << "number of words is " << myTrie->getSize() << endl;
        } else if (cmd == "exit") {
            break;
        }
    }
    delete myTrie;
}