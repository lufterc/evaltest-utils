#include "hash.h"
#include <iostream>
#include <cassert>

int main() {
    using namespace std;

    HashMap<long unsigned int, int> hmap;
    hmap.put(24, 100);
    hmap.put(32, 200);

    int out;
    hmap.get(24, out);
    cout << out << endl;

    hmap.get(32, out);
    cout << out << endl;

    return 0;
}
