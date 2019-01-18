#pragma once

template <class T>
void swap(T* a, T* b) {
    T t = *a; *a = *b; *b = t;
}

template <class T>
int partition(T arr[], int l, int h) {
    int x = arr[h];
    int i = (l - 1);

    for (int j = l; j <= h- 1; j++) {
        if (arr[j] <= x) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[h]);
    return (i + 1);
}

template <class T>
void quickSort(T arr[], int l, int h) {          // arr[] --> Array to be sorted, l  --> starting index, h  --> ending index
    int stack[h - l + 1];                        // create an auxiliary stack
    int top = -1;                                // initialize top of stack

    stack[++top] = l;                            // push initial values of l and h to stack
    stack[++top] = h;

    while (top >= 0) {                           // keep popping from stack while is not empty
        h = stack[top--];                        // pop h and l
        l = stack[top--];

        int p = partition(arr, l, h);            // set pivot element at its correct position in sorted array

        if (p - 1 > l) {                         // if there are elements on left side of pivot, then push left side to stack
            stack[ ++top ] = l;
            stack[ ++top ] = p - 1;
        }

        if (p+1 < h) {                           // if there are elements on right side of pivot, then push right side to stack
            stack[ ++top ] = p + 1;
            stack[ ++top ] = h;
        }
    }
}
