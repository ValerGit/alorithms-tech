/*
    1_1. Ящики.
    На склад привезли много пустых ящиков.
    Все ящики пронумерованы по порядку поступления от 0.
    Известно, что их все можно сложить один в один
    (то есть так, что каждый следующий помещается в предыдущий).
    Один ящик можно вложить в другой, если его можно перевернуть так,
    что размеры одного ящика по всем осям станут строго меньше размеров
    другого ящика по соответствующим осям. Требуется определить,
    в какой последовательности они будут вложены друг в друга. Вывести номера ящиков.
*/

#include <iostream>
#include <vector>

using namespace std;

struct Box {
    int index;
    int x;
    int y;
    int z;
    Box() : index(), x(0), y(0), z(0) {}
};

bool isLess(int& left, int& right) {
    return left < right;
}

bool isLess(Box& left, Box& right) {
    return left.x < right.x;
}

template <class T>
void Sort (T* arr, int left, int right, bool ((*isLess)(T&, T&)) ) {
    for( int i = left+1; i < right; ++i) {
        for( int j = i-1; j >= 0; --j) {
            if(isLess(arr[j], arr[i])) {
                T temp= arr[i];
                memcpy( &arr[j], &arr[j+1], i-j);
                arr[j+1] = temp;
            }
        }
    }
}

int main()
{
    const int threeD = 3;
    int* dimensions = new int[threeD];
    int counter = 0, num = 0;
    cin >> num;
    Box* boxes = new Box[num];

    while(counter < num) {
        for(int i = 0; i < threeD; ++i) {
            cin >> dimensions[i];
        }
        Sort(dimensions, 0, threeD, isLess);
        boxes[counter].x = dimensions[0];
        boxes[counter].y = dimensions[1];
        boxes[counter].z = dimensions[2];
        boxes[counter].index = counter;
        ++counter;
    }
    Sort(boxes, 0, num, isLess);

    for(int i = num-1; i >= 0; --i) {
        cout << boxes[i].index << " ";
    }

    delete[] dimensions;
    delete[] boxes;
    return 0;
}

