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
        table = new HashNode *[TSIZE]();                    // construct zero initialized hash table of size
    }

    ~HashMap() {
        for (Hash i = 0; i < TSIZE; ++i) {                  // destroy all buckets one by one
            HashNode *n = table[i];
            while (n != 0) {
                HashNode *prev = n;
                n = n->next;
                delete prev;
            }
            table[i] = 0;
        }
        delete [] table;                                    // destroy the hash table
    }

    HashNode* get(const K &key) {
        HashNode *n = table[hashFunc(key)];
        while (n != 0) {
            if (n->key == key) { return n; }
            n = n->next;
        }
        return 0;
    }

    void put(const K &key, const V &val) {
        Hash hashValue = hashFunc(key);
        HashNode *prev = 0;
        HashNode *n = table[hashValue];

        while (n != 0 && n->key != key) {
            prev = n;
            n = n->next;
        }

        if (n == 0) {
            n = new HashNode(key, val);
            if (prev == 0) { table[hashValue] = n; }        // insert as first bucket
            else { prev->next = n; }
        }
        else { n->val = val; }                              // just update the value
    }

    void remove(const K &key) {
        Hash hashValue = hashFunc(key);
        HashNode *prev = 0;
        HashNode *n = table[hashValue];

        while (n != 0 && n->next != key) { prev = n; n = n->next; }

        if (n == 0) { return; }                             // key not found
        else {
            if (prev == 0) { table[hashValue] = n->next; }  // remove first bucket of the list
            else { prev->next = n->next; }
            delete n;
        }
    }

private:
    HashNode **table; F hashFunc;
};
