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
    struct Node {
        Node(K key, V val) : key(key), val(val), next(0) {}
        K key; V val; Node *next;
    };

    HashMap() {
        table = new Node *[TSIZE]();                        // construct zero initialized hash table of size
    }

    ~HashMap() {
        for (Hash i = 0; i < TSIZE; ++i) {                  // destroy all buckets one by one
            Node *n = table[i];
            while (n != 0) {
                Node *p = n;
                n = n->next;
                delete p;
            }
            table[i] = 0;
        }
        delete [] table;                                    // destroy the hash table
    }

    Node* get(const K &key) {
        Node *n = table[hashFunc(key)];
        while (n != 0) {
            if (n->key == key) { return n; }
            n = n->next;
        }
        return 0;
    }

    void put(const K &key, const V &val) {
        Hash hashValue = hashFunc(key);
        Node *p = 0;
        Node *n = table[hashValue];

        while (n != 0 && n->key != key) {
            p = n;
            n = n->next;
        }

        if (n == 0) {
            n = new Node(key, val);
            if (p == 0) { table[hashValue] = n; }           // insert as first bucket
            else { p->next = n; }
        }
        else { n->val = val; }                              // just update the value
    }

    void remove(const K &key) {
        Hash hashValue = hashFunc(key);
        Node *p = 0;
        Node *n = table[hashValue];

        while (n != 0 && n->next != key) { p = n; n = n->next; }

        if (n == 0) { return; }                             // key not found
        else {
            if (p == 0) { table[hashValue] = n->next; }     // remove first bucket of the list
            else { p->next = n->next; }
            delete n;
        }
    }

private:
    Node **table; F hashFunc;
};
