#include <vector>

class HashTable {

private:
    int N;
    int P;
    int m;
    Process* table;
    std::vector<int> currentSize;

public:
    HashTable(int N, int P) {
        this->N = N;
        this->P = P;
        this->m = N / P; 
        this->table = new Process [m];
        currentSize = std::vector<int> (m, 0);
    }

    int getM() {
        return m;
    }

    int calculateStartPageAddress(int PID) {
        return PID % m;
    }

    void insert(int PID, bool doubleHashing) {
        // Process* newProcess = new Process(PID, m);

        // idea: calculate first hash function separately
        // so I don't need to allocate memory and delete it if it fails
        int startPageAddress = calculateStartPageAddress(PID);
        if (table[startPageAddress]->getPID() == PID) {
            std::cout << "failure" << std::endl; // DUPLICATE NAME FOUND
            return;
        }
        if (table[startPageAddress] == 0) { // EMPTY SPOT FOUND
            Process* newProcess = new Process(PID, m);
            currentSize[startPageAddress]++;
            std::cout << "success" << std::endl;
            table[startPageAddress] = newProcess;
            return;
        } else { // COLLISION
            if (doubleHashing) {
                int indexVariable = 0;
                int newPageAddress = startPageAddress;
                while (indexVariable < m) {
                    newPageAddress += ((PID / 10) % m);
                    newPageAddress %= m;
                    if (newPageAddress % 2 == 0) {
                        newPageAddress += 1;
                    }
                    if (table[newPageAddress]->getPID() == PID) {
                        std::cout << "failure" << std::endl; // DUPLICATE NAME FOUND
                        return;
                    }
                    if (table[newPageAddress] == 0) { // EMPTY SPOT FOUND
                        Process* newProcess = new Process(PID, m);
                        std::cout << "success" << std::endl;
                        table[newPageAddress] = newProcess;
                        currentSize[startPageAddress]++;
                        return;
                    }
                    indexVariable++;
                }
                std::cout << "failure" << std::endl; // HASH TABLE FULL
                return;
            } else { // separate chaining
                int pageSizeCounter = 1;
                Process *temp = table[startPageAddress];
                while (PID < temp->getPID()) {
                    temp = temp->getNext();
                    pageSizeCounter++;
                    if (temp == nullptr) { // reached end of the list
                        if (pageSizeCounter > P) {
                            std::cout << "failure" << std::endl;
                            return;
                        } else {
                            std::cout << "success" << std::endl;
                            Process* newProcess = new Process(PID, m);
                            temp = newProcess;
                            currentSize[startPageAddress]++;
                            return;
                        }
                    }
                }
                // found a number smaller than PID

                return;
            }
        }
    }
};