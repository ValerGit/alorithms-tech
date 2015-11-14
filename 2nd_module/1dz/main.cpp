/*
 * 1_1. Ящики.
 * На склад привезли много пустых ящиков.
 * Все ящики пронумерованы по порядку поступления от 0.
 * Известно, что их все можно сложить один в один
 * (то есть так, что каждый следующий помещается в предыдущий).
 * Один ящик можно вложить в другой, если его можно перевернуть так,
 * что размеры одного ящика по всем осям станут строго меньше размеров
 * другого ящика по соответствующим осям. Требуется определить,
 * в какой последовательности они будут вложены друг в друга. Вывести номера ящиков.
*/

#include <iostream>
#include <string.h>

using namespace std;

struct Box {
    int index;
    int x;
    int y;
    int z;

    Box() : index(), x(0), y(0), z(0) { }
};

bool isBigger(int &left, int &right) {
    return left > right;
}

bool isBigger(Box &left, Box &right) {
    return left.z > right.z;
}

template<class T>
int binSearch (T* arr, int end, T value, bool ((*isBigger)(T &, T &)) ) {
    int l = 0, r = end;
    while(l < r) {
        int m = ( l + r ) / 2;
        if( isBigger (value, arr[m]) ) l = m + 1;
        else r = m;
    }
    return r;
}

template<class T>
void Sort(T *arr, int left, int right, bool ((*isBigger)(T &, T &))) {


    for (int i = left + 1; i < right; ++i) {

        int newPosit = binSearch(arr, i, arr[i], isBigger);
        if( newPosit < i ) {
            T temp = arr[i];
            memmove( &arr[newPosit+1], &arr[newPosit], (i - newPosit)* sizeof(T));
            arr[newPosit] = temp;
        }
    }
}

int main() {
    const int threeD = 3;
    int* dimensions = new int[threeD];
    int counter = 0, num = 0;
    cin >> num;
    Box* boxes = new Box[num];

    while(counter < num) {
        for(int i = 0; i < threeD; ++i) {
            cin >> dimensions[i];
        }
        Sort(dimensions, 0, threeD, isBigger);
        boxes[counter].x = dimensions[0];
        boxes[counter].y = dimensions[1];
        boxes[counter].z = dimensions[2];
        boxes[counter].index = counter;
        ++counter;
    }
    Sort(boxes, 0, num, isBigger);

    for(int i = 0; i < num ; ++i) {
        cout << boxes[i].index << " ";
    }

    delete[] dimensions;
    delete[] boxes;
    return 0;
}
