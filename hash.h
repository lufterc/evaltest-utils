#pragma once

template <typename K, unsigned long TABLE_SIZE>
struct KeyHash {
    unsigned long operator()(const K& key) {
        return reinterpret_cast<unsigned long>(key) % TABLE_SIZE;
    }
};

template <typename K, typename V, unsigned long TABLE_SIZE = 1024,
          typename F = KeyHash<K, TABLE_SIZE>>
class HashMap {
public:
    struct HashNode {
        HashNode(K key, V value) : key(key), value(value), next(next) {}
        K key; V value; HashNode *next;
    };

    HashMap() {
        table = new HashNode *[TABLE_SIZE](); // construct zero initialized hash table of size
    }

    ~HashMap() {
        for (int i = 0; i < TABLE_SIZE; ++i) { // destroy all buckets one by one
            HashNode *entry = table[i];
            while (entry != 0) {
                HashNode *prev = entry;
                entry = entry->next;
                delete prev;
            }
            table[i] = 0;
        }
        delete [] table; // destroy the hash table
    }

    bool get(const K &key, V &value) {
        unsigned long hashValue = hashFunc(key);
        HashNode *entry = table[hashValue];

        while (entry != 0) {
            if (entry->key == key) {
                value = entry->value;
                return true;
            }
            entry = entry->next;
        }
        return false;
    }

    void put(const K &key, const V &value) {
        unsigned long hashValue = hashFunc(key);
        HashNode *prev = 0;
        HashNode *entry = table[hashValue];

        while (entry != 0 && entry->key != key) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == 0) {
            entry = new HashNode(key, value);
            if (prev == 0) {
                table[hashValue] = entry; // insert as first bucket
            }
            else { prev->next = entry; }
        }
        else { entry->value = value; } // just update the value
    }

    void remove(const K &key) {
        unsigned long hashValue = hashFunc(key);
        HashNode *prev = 0;
        HashNode *entry = table[hashValue];

        while (entry != 0 && entry->next != key) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == 0) { return; } // key not found

        else {
            if (prev == 0) { table[hashValue] = entry->next; } // remove first bucket of the list
            else { prev->next = entry->next; }
            delete entry;
        }
    }

private:
    HashNode **table;
    F hashFunc;
};
