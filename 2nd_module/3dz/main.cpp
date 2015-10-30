/*
На числовой прямой окрасили ​N​ отрезков. Известны координаты левого и
правого концов каждого отрезка (L​i​ и R​i)​ . Найти длину окрашенной части числовой прямой.
*/
#include <iostream>

using namespace std;

struct Part {
    bool isEnd;
    int val;

    Part() : isEnd(false), val(0) {}
    Part(const Part& o) : isEnd(o.isEnd), val(o.val) {}
};

bool isBigger(const Part& one, const Part& two) {
    return one.val > two.val;
}

template <typename T>
class Heap {
public:
    Heap() {}
    Heap(T*,int);
    ~Heap();
    T getElem(int i);

private:
    T* arr;
    int size;
    void buildHeap();
    void sort();
    void siftDown(int index);
};

template <typename T>
Heap<T>::Heap(T* _arr, int n) {
    size = n;
    arr = new T[n];
    for(int i = 0; i < n; ++i) {
        arr[i] = _arr[i];
    }
    buildHeap();
    sort();
}

template <typename T>
Heap<T>::~Heap() {
    delete[] arr;
}

template <typename T>
void Heap<T>::buildHeap() {
    for(int i = size/2-1; i >= 0; --i) {
        siftDown(i);
    }
}

template <typename T>
void Heap<T>::sort() {
    int temp = size--;
    for(int i = 0; i < temp; ++i) {
        swap(arr[0], arr[size]);
        siftDown(0);
        --size;
    }
    size = temp;
}

template <typename T>
T Heap<T>::getElem(int i) {
    return arr[i];
}

template <typename T>
void Heap<T>::siftDown(int index) {
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


template <class T>
int isColored(Heap<T>* heap, int size) {
    int res = 0;
    int count = 0;
    int start = 0;

    for(int i = 0; i < size; ++i) {
        Part temp = heap->getElem(i);
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

    Heap<Part>* heap  = new Heap<Part>( arr, num );
    cout << isColored(heap, num);
    delete[] arr;
    delete heap;
    return 0;
}

