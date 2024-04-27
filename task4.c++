#include <iostream>
#include <algorithm>

using namespace std;

void printingarray(const int array[], int size) {
    cout << "[ ";
    for (int i = 0; i < size; i++) {
        cout << array[i] << ", ";
    }
    cout << "]" << endl;
}

void partition(int array[], int low, int high, int k, int& i, int& j) {
    i = low - 1, j = high;
    int p = low - 1, q = high;
    int v = array[high];

    while (true) {
        while (array[++i] < v);
        while (v < array[--j])
            if (j == low)
                break;

        if (i >= j) break;
        swap(array[i], array[j]);

        if (array[i] == v) {
            p++;
            swap(array[p], array[i]);
        }
        if (array[j] == v) {
            q--;
            swap(array[j], array[q]);
        }
    }
    swap(array[i], array[high]);
    j = i - 1;
    for (int k = low; k < p; k++, j--)
        swap(array[k], array[j]);
    i = i + 1;
    for (int k = high - 1; k > q; k--, i++)
        swap(array[i], array[k]);
}

void recursiveSort(int array[], int low, int high, int k) {
    if (high <= low) return;

    int i, j;
    partition(array, low, high, k, i, j);
    recursiveSort(array, low, j, k);
    recursiveSort(array, i, high, k);
}

int main() {
    int array[] = { 3, 1, 12, 9, 4, 10, 54, 34, 12, 89 };
    int N = sizeof(array) / sizeof(array[0]);

    cout << "Unsorted arrayay: ";
    printingarray(array, N);

    cout << "Key = ";
    int k;
    cin >> k;

    recursiveSort(array, 0, N - 1, k);

    cout << "Output: ";
    printingarray(array, N);

    return 0;
}