#include "hash.h"
#include <iostream>
#include <cassert>

int main() {
    using namespace std;

    HashMap<long unsigned int, int> hmap;
    hmap.put(24, 100);
    hmap.put(32, 200);

    cout << hmap.get(24)->value << endl;
    cout << hmap.get(32)->value << endl;

    return 0;
}
