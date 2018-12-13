#pragma once

template <typename K, typename V>
struct HashNode {
    K key; V value; HashNode *next;
};

template <typename K, unsigned long TABLE_SIZE>
struct KeyHash {
    unsigned long operator()(const K& key) const
    {
        return reinterpret_cast<unsigned long>(key) % TABLE_SIZE;
    }
};

template <typename K, typename V, unsigned long TABLE_SIZE = 1024,
          typename F = KeyHash<K, TABLE_SIZE>>
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
                entry = entry->next;
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
        HashNode<K, V> *prev = 0;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != 0 && entry->key != key) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == 0) {
            entry = new HashNode<K, V>(key, value);
            if (prev == 0) {
                // insert as first bucket
                table[hashValue] = entry;
            } else {
                prev->next = entry;
            }
        } else {
            // just update the value
            entry->value = value;
        }
    }

    void remove(const K &key) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = 0;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != 0 && entry->next != key) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == 0) {
            // key not found
            return;
        }
        else {
            if (prev == 0) {
                // remove first bucket of the list
                table[hashValue] = entry->next;
            } else {
                prev->next = entry->next;
            }
            delete entry;
        }
    }

private:
    HashNode<K, V> **table;
    F hashFunc;
};
