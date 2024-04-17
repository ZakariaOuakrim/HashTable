#include <iostream>

using namespace std;

class HashEntry {
private:
    int key;
    int value;

public:
    HashEntry(int key, int value) : key(key), value(value) {}

    int getKey() const {
        return key;
    }

    int getValue() const {
        return value;
    }
};

class HashTable {
private:
    HashEntry **t;
    int T_S;
    int count;

public:
    HashTable(int ts) {
        T_S = ts;
        count = 0;
        t = new HashEntry*[T_S];
        for (int i = 0; i < T_S; i++)
            t[i] = NULL;
    }

    ~HashTable() {
        clear();
        delete[] t;
    }

    void insert(int key, int value) {
        int index = hashFunction(key);

        if (t[index] == nullptr) {//empty zone
            t[index] = new HashEntry(key, value);
            count++;
        } else {
            cout << "Collision! index " << index << " already exists." << endl;
        }
    }

    int get(int key) {
        int index = hashFunction(key);

        if (t[index] != nullptr && t[index]->getKey() == key) {
            return t[index]->getValue();
        } else {
            cout << "Key " << key << " not found." << endl;
            return -1; 
        }
    }

    void remove(int key) {
        int index = hashFunction(key);

        if (t[index] != nullptr && t[index]->getKey() == key) {
            delete t[index];
            t[index] = nullptr;
            count--;
        } else {
            cerr << "Key " << key << " not found." << endl;
        }
    }

    void list() {
        cout << "Current Contents of HashTable:" << endl;
        for (int i = 0; i < T_S; ++i) {
            if (t[i] != nullptr) {
                cout << "Key: " << t[i]->getKey() << ", Value: " << t[i]->getValue() << endl;
            }
        }
    }

    void clear() {
        for (int i = 0; i < T_S; ++i) {
            if (t[i] != nullptr) {
                delete t[i];
                t[i] = nullptr;
            }
        }
        count = 0;
    }

private:
    int hashFunction(int key) {
        return key % T_S; 
    }
};

int main() {
    HashTable hashTable(10); 

    // Insertions
    hashTable.insert(1, 10);
    hashTable.insert(2, 20);
    hashTable.insert(11, 30); // Collision, devrait être rejetée
    hashTable.insert(12, 70); // Collision, devrait être rejetée
    hashTable.insert(3, 40);
    hashTable.insert(5, 40);
    

    // Afficher la table de hachage
    hashTable.list();

    // Obtenir une valeur
    cout << "Value for key 2: " << hashTable.get(2) << endl;
    cout << "Value for key 5: " << hashTable.get(5) << endl;
    cout << "Value for key 7: " << hashTable.get(7) << endl;

    // Supprimer une entrée
    hashTable.remove(2);

    // Afficher la table de hachage après suppression
    hashTable.list();

    // Nettoyer la table de hachage
    hashTable.clear();

    return 0;
}

