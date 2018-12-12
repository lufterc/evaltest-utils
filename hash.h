#pragma once

// Hash node class template
template <typename K, typename V>
class HashNode {
public:
    HashNode(const K &key, const V &value) :
    key(key), value(value), next(0) {
    }

    K getKey() const {
        return key;
    }

    V getValue() const {
        return value;
    }

    void setValue(V value) {
        HashNode::value = value;
    }

    HashNode *getNext() const {
        return next;
    }

    void setNext(HashNode *next) {
        HashNode::next = next;
    }

private:
    // key-value pair
    K key;
    V value;
    // next bucket with the same key
    HashNode *next;
};

template <typename K, unsigned long TABLE_SIZE>
struct KeyHash {
    unsigned long operator()(const K& key) const
    {
        return reinterpret_cast<unsigned long>(key) % TABLE_SIZE;
    }
};

template <typename K, typename V, unsigned long TABLE_SIZE = 1024, typename F = KeyHash<K, TABLE_SIZE>>
class HashMap {
public:
    HashMap() {
        // construct zero initialized hash table of size
        table = new HashNode<K, V> *[TABLE_SIZE]();
    }

    ~HashMap() {
        // destroy all buckets one by one
        for (int i = 0; i < TABLE_SIZE; ++i) {
            HashNode<K, V> *entry = table[i];
            while (entry != 0) {
                HashNode<K, V> *prev = entry;
                entry = entry->getNext();
                delete prev;
            }
            table[i] = 0;
        }
        // destroy the hash table
        delete [] table;
    }

    bool get(const K &key, V &value) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *entry = table[hashValue];

        while (entry != 0) {
            if (entry->getKey() == key) {
                value = entry->getValue();
                return true;
            }
            entry = entry->getNext();
        }
        return false;
    }

    void put(const K &key, const V &value) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = 0;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != 0 && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == 0) {
            entry = new HashNode<K, V>(key, value);
            if (prev == 0) {
                // insert as first bucket
                table[hashValue] = entry;
            } else {
                prev->setNext(entry);
            }
        } else {
            // just update the value
            entry->setValue(value);
        }
    }

    void remove(const K &key) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = 0;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != 0 && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == 0) {
            // key not found
            return;
        }
        else {
            if (prev == 0) {
                // remove first bucket of the list
                table[hashValue] = entry->getNext();
            } else {
                prev->setNext(entry->getNext());
            }
            delete entry;
        }
    }

private:
    // hash table
    HashNode<K, V> **table;
    F hashFunc;
};
