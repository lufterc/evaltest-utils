#pragma once

typedef unsigned long Hash;

template <typename K, Hash TSIZE>
struct KeyHash {
    Hash operator()(const K& key) {
        return reinterpret_cast<Hash>(key) % TSIZE;
    }
};

template <typename K, typename V, Hash TSIZE = 1024,
          typename F = KeyHash<K, TSIZE>>
class HashMap {
public:
    struct HashNode {
        HashNode(K key, V val) : key(key), val(val), next(0) {}
        K key; V val; HashNode *next;
    };

    HashMap() {
        table = new HashNode *[TSIZE](); // construct zero initialized hash table of size
    }

    ~HashMap() {
        for (Hash i = 0; i < TSIZE; ++i) { // destroy all buckets one by one
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

    HashNode* get(const K &key) {
        HashNode *entry = table[hashFunc(key)];
        while (entry != 0) {
            if (entry->key == key) {
                return entry;
            }
            entry = entry->next;
        }
        return 0;
    }

    void put(const K &key, const V &val) {
        Hash hashValue = hashFunc(key);
        HashNode *prev = 0;
        HashNode *entry = table[hashValue];

        while (entry != 0 && entry->key != key) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == 0) {
            entry = new HashNode(key, val);
            if (prev == 0) {
                table[hashValue] = entry; // insert as first bucket
            }
            else { prev->next = entry; }
        }
        else { entry->val = val; } // just update the value
    }

    void remove(const K &key) {
        Hash hashValue = hashFunc(key);
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
