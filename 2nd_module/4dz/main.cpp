/*
 * Реализуйте стратегию выбора опорного элемента “медиана трёх”.
 * Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
 */

#include <iostream>

using namespace std;

int findPivot(int *arr, int start, int end) {
    int pivotPl = 0, half = ((end + start) / 2) - 1;
    int a = arr[start],
            b = arr[half],
            c = arr[end - 1];

    if (a < b) {
        if (b < c) pivotPl = half;
        else {
            if (a < c) pivotPl = end - 1;
            else pivotPl = start;
        }
    } else {
        if (c < b) pivotPl = half;
        else {
            if (a < c) pivotPl = start;
            else pivotPl = end - 1;
        }
    }
    return pivotPl;
}

int partition(int *arr, int start, int end) {
    int pivot = findPivot(arr, start, end);

    swap(arr[end - 1], arr[pivot]);

    int i = start, j = start;
    while (j < end - 1) {
        if (arr[j] > arr[end - 1]) ++j;
        else {
            swap(arr[i], arr[j]);
            ++i;
            ++j;
        }
    }
    swap(arr[i], arr[end - 1]);
    return i;
}

int findPlace(int *arr, int start, int size, int num) {
    int toFind = 0;
    while (start < size) {
        toFind = partition(arr, start, size);
        if (num == toFind) break;
        else if (num < toFind) size = toFind;
        else start = toFind + 1;
    }
    return arr[num];
}

int main() {
    int k = 0, n = 0;
    cin >> n >> k;
    int *arr = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    cout << findPlace(arr, 0, n, k);
    delete[] arr;
    return 0;
}
