/*
 * Дан массив целых чисел в диапазоне [0..10^9]. Размер массива ограничен
 * сверху значением 2.5 * 10^7 элементов. Все значения массива являются
 * элементами псевдо­рандомной последовательности.
 * В контест необходимо отправить реализацию функции
 * void FastSort( int* vector, int n );
 * За основу должна быть взят алгоритм быстрой сортировки. Набор оптимизаций,
 * который необходимо реализовать:
 * 1. Оптимизация выбора опорного элемента.
 * 2. Оптимизация Partition.
 * 3. Оптимизация концевой рекурсии.
 *  4. Написать без рекурсии.
*/

#include <iostream>
#include <stack>
#include <vector>
#include <cstring>
#define CUTOFF 18

using namespace std;

struct Dimension {
    int start;
    int end;
    Dimension(int l, int r) : start(l), end(r) {}
};

struct pivots {
    int left, right;
};


int binSearch (int* arr, int end, int value) {
    int l = 0, r = end;
    while(l < r) {
        int m = ( l + r ) / 2;
        if( value > arr[m] ) l = m + 1;
        else r = m;
    }
    return r;
}

void insertion_sort(int* arr, int left, int right) {

    for (int i = left + 1; i < right; ++i) {

        int newPosit = binSearch(arr, i, arr[i]);
        if( newPosit < i ) {
            int temp = arr[i];
            memmove( &arr[newPosit+1], &arr[newPosit], (i - newPosit)* sizeof(int));
            arr[newPosit] = temp;
        }
    }
}

int findPivot(int *arr, int start, int end) {
    int pivotPl = 0, half = ((end + start) / 2) - 1;
    int a = arr[start],
            b = arr[half],
            c = arr[end];

    if (a < b) {
        if (b < c) pivotPl = half;
        else {
            if (a < c) pivotPl = end;
            else pivotPl = start;
        }
    } else {
        if (c < b) pivotPl = half;
        else {
            if (a < c) pivotPl = start;
            else pivotPl = end ;
        }
    }
    return pivotPl;
}

int partition(int *arr, int start, int end) {
    int pivot = findPivot(arr, start, end);

    swap(arr[end], arr[pivot]);

    int i = start, j = start;
    while (j < end) {
        if (arr[j] > arr[end]) ++j;
        else {
            swap(arr[i], arr[j]);
            ++i;
            ++j;
        }
    }
    swap(arr[i], arr[end]);
    return i;
}

void quicksort_r (int* list, int left, int right )
{
    std::vector<Dimension>* stack = new std::vector<Dimension>;
    stack->push_back(Dimension(left,right));

    while(!stack->empty()) {
        Dimension temp = stack->back();
        stack->pop_back();

        if( temp.start < temp.end) {

            if(temp.end - temp.start <= CUTOFF) {
                insertion_sort(list,temp.start, temp.end + 1);

            } else {
                int pivot = partition (list, temp.start, temp.end);
                stack->push_back(Dimension( temp.start, pivot - 1) );
                stack->push_back( Dimension( pivot + 1, temp.end) );
            }

        }
    }
    delete stack;
}


void FastSort(int* vector, int n)
{
    quicksort_r ( vector, 0, n-1);
}
