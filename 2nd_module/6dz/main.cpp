/*
 * Binary MSD для long long.
 * Дан массив неотрицательных целых 64­разрядных чисел.
 * Количество чисел не больше 106​ ​. Отсортировать массив
 * методом MSD по битам (бинарный QuickSort).
*/

#include <iostream>
#include <stdio.h>
#include <stdint.h>

bool digit(unsigned long long val, int division) {
    return val & ((unsigned long long)1 << division);
}

void quickSort(unsigned long long* arr, int left, int right, int division ) {
    if( right <= left || division < 0) return;
    int i = left, j = right;
    while( i != j) {
        while( !digit(arr[i], division) && i < j) ++i;
        while( digit(arr[j], division) && i < j) --j;
        std::swap( arr[i], arr[j]);
    }
    if( digit( arr[right], division) == 0) ++j;
    quickSort( arr, left, j-1, division-1);
    quickSort( arr, j, right, division-1);
}

int main()
{
    int n = 0;
    std::cin >> n;
    unsigned long long* arr =  new unsigned long long[n];

    for(int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    const int maxDivision = 63;
    quickSort( arr, 0, n-1, maxDivision);
    for(int i = 0; i < n; ++i) {
        std::cout << arr[i] << std::endl;
    }
    delete[] arr;
    return 0;
}
