#include "hash.h"
#include "qsort.h"
#include "bsearch.h"
#include <iostream>
#include <cassert>

int main() {
    using namespace std;

    HashMap<long unsigned int, int> hmap;
    hmap.put(24, 100);
    hmap.put(32, 200);

    cout << hmap.get(24)->val << endl;
    cout << hmap.get(32)->val << endl;

    double arr[] = { 0.5, 1.2, 0.3 };
    quickSort(arr, 0, 2);
    cout << arr[0] << endl;

    int sr = binarySearch(arr, 3, 1.2);
    cout << sr << endl;

    return 0;
}
