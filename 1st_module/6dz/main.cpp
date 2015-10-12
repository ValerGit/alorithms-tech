#include <iostream>
#include <inttypes.h>

using namespace std;

void placing_X_into_Y_row(uint64_t **&arr, uint64_t x, int y, int start, int end) {
    for (int i = start; i < end; ++i) {
        arr[y][i] = x;
    }
}

uint64_t findCombinations(uint64_t**& arr, int size) {
    //один способ положить на верх ноль
    placing_X_into_Y_row(arr, 1, 0, 0, size);
    for (int i = 1; i < size; ++i) {
        for (int j = 1; j < size; ++j) {
            if (i >= j) {
                uint64_t temp = arr[i - j][j-1] + arr[i][j-1];
                placing_X_into_Y_row(arr, temp, i, j, size);
            }
        }
    }
    return arr[size-1][size-1];
}

int main() {
    int n = 0;
    cin >> n;
    if (n <= 0 || n > 300) {
        cout << 0;
        return 0;
    }
    ++n;
    //массив с возможными вариантами построения пирамидок из i-го количества кубиков
    uint64_t **arr = new uint64_t *[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = new uint64_t[n];
        //заполняем всю матрицу нулями
        for (int j = 0; j < n; ++j) {
            arr[i][j] = 0;
        }
    }

    cout << findCombinations(arr, n);

    for (int i = 0; i < n; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
    return 0;
}

