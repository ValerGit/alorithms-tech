/*
 * На числовой прямой окрасили ​N​ отрезков. Известны координаты левого и
 * правого концов каждого отрезка (L​i​ и R​i)​.
 * Найти длину окрашенной части числовой прямой.
*/

#include <iostream>

using namespace std;

struct Part {
    bool isEnd;
    int val;

    Part() : isEnd(false), val(0) {}
    Part(const Part& o) : isEnd(o.isEnd), val(o.val) {}
};

bool isBigger(Part& one, Part& two) {
    return one.val > two.val;
}

template <typename T>
void siftDown(T* arr, int index, int size, bool (*isBigger)(T&, T&)) {
    for(int i = index; 2*i+2 <= size; ) {

        int left = 2*i + 1;
        int right = 2*i + 2;
        int largest = i;

        if( left < size  && isBigger(arr[left], arr[largest]) ) largest = left;
        if( right < size  && isBigger(arr[right], arr[largest]) ) largest = right;

        if(largest != i) {
            swap( arr[i], arr[largest] );
            i = largest;
        } else break;
    }
}


template <typename T>
void heapSort(T* arr, size_t size,  bool (*isBigger)(T&, T&) ) {
    for(int i = size/2 - 1; i >= 0; --i ) {
        siftDown( arr, i, size, isBigger );
    }
    for(int i = 0 ;i < size; ++i) {
        swap(arr[0], arr[size-i-1]);
        siftDown(arr, 0, size-i-1, isBigger);
    }
}


int isColored(Part* heap, int size) {
    int res = 0;
    int count = 0;
    int start = 0;
    heapSort(heap, size, isBigger);
    for(int i = 0; i < size; ++i) {
        Part temp = heap[i];
        if(count == 0) {
            ++count;
            start = temp.val;
        } else {
            if(temp.isEnd) --count;
            else ++count;
        }
        if(count == 0) res += (temp.val - start);
    }
    return res;
}


int main()
{
    int num = 0;
    cin >> num;
    num *= 2;
    Part* arr = new Part[num];

    //считывание данных
    int cntr = 0;
    while(cntr < num) {
        cin >> arr[cntr++].val;
        cin >> arr[cntr].val;
        arr[cntr++].isEnd = true;
    }

    cout << isColored(arr, num);
    delete[] arr;

    return 0;
}
