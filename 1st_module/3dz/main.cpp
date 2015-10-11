#include <iostream>

using namespace std;

int binarySearch(int* arr, int size, int left, int val)
{
    int l = left, r = size;
    for(int i = l; i*i < size; ++i) {
        if(arr[i*i] < val) {
            l = i*i + 1;
        }
        else break;
    }
    if(l*l < size) r = l*l;

    while(l < r) {
        int m = ( l + r ) / 2;

        if(val > arr[m]) l = m + 1;
        else r = m;
    }
    return l;
}

int main()
{
    //считывание данных
    int n = 0, m = 0;
    cin >> n;
    cin >> m;
    int* A = new int[n];
    for(int i = 0; i < n; ++i) {
        cin >> A[i];
    }
    int* B = new int[m];
    for(int i = 0; i < m; ++i) {
        cin >> B[i];
    }

    //переменная для левой границы бинарного поиска
    int prevPlace = 0;

    for(int i = 0; i < m; ++i) {
        //поиск места в массиве arr для элемента из массива barr
        int foundPlace = binarySearch(A, n, prevPlace, B[i]);
        if(B[i] == A[foundPlace]) {
            cout << B[i];
            if(i != m-1) cout << " ";
            prevPlace = foundPlace;
        }
    }

    delete[] A;
    delete[] B;
    return 0;
}

