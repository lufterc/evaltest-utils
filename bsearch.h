#pragma once

template <class T>
int binarySearch (const T A[], int length, T val) {
    /* initialize variables:
          low : index of smallest value in current subarray of A
          high: index of largest value in current subarray of A
          mid : average of low and high in current subarray of A */
    int low, mid, high;

    low = 0;                                      // set initial value for low
    high = length - 1;                            // set initial value for high

    while (low <= high) {
        mid = low + (high - low) / 2;             // update mid

        if (A [mid] > val) {                      // search left subarray for val
            high = mid - 1;                       // update high
        }
        else if (A [mid] < val) {                 // search right subarray for val
            low = mid + 1;                        // update low
        }
        else {                                    // val = A[mid]
            return mid;                           // return index of val in A
        }
    }

    return (-1);                                  // val not found in A
}
