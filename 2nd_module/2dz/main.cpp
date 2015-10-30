/*
 * На вокзале есть некоторое количество тупиков, куда прибывают электрички.
 * Этот вокзал является их конечной станцией. Дано расписание движения электричек,
 * в котором для каждой электрички указано время ее прибытия, а также время отправления
 * в следующий рейс. Электрички в расписании упорядочены по времени прибытия.
 * Когда электричка прибывает, ее ставят в свободный тупик с минимальным номером.
 * При этом если электричка из какого­то тупика отправилась в момент времени X,
 * то электричку, которая прибывает в момент времени X, в этот тупик ставить нельзя,
 * а электричку, прибывающую в момент X+1 — можно.
 * В данный момент на вокзале достаточное количество тупиков для работы по расписанию.
 * Напишите программу, которая по данному расписанию определяет, какое минимальное
 * количество тупиков требуется для работы вокзала.
*/
#include <iostream>

using namespace std;

struct Time {
    bool isLeaving;
    int time;

    Time() : isLeaving(false), time(0) {}
    Time(int n) : isLeaving(false), time(n) {}
};

ostream& operator<<(ostream &os, const Time& n) {
    cout << n.time << " ";
    return os;
}

bool isLess(const Time& one, const Time& two) {
    if(one.time == two.time) {
        if(one.isLeaving) return false;
        else return true;
    }
    return one.time < two.time;
}

template <typename T>
class Heap {
public:
    Heap() {}
    Heap(T*,int);
    ~Heap();
    void buildHeap();
    T extractMax();

private:
    void siftDown(int index);
    T* arr;
    int size;
};

template <typename T>
Heap<T>::Heap(T* _arr, int n) {
    size = n;
    arr = new T[n];
    for(int i = 0; i < n; ++i) {
        arr[i] = _arr[i];
    }
    buildHeap();
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
T Heap<T>::extractMax() {
    T temp = arr[0];
    swap(arr[0], arr[--size]);
    siftDown(0);
    return temp;
}

template <typename T>
void Heap<T>::siftDown(int index)
{
    for(int i = index; 2*i+2 <= size; ) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int largest = i;
        if( left < size  && isLess(arr[left], arr[largest]) ) largest = left;
        if( right < size  && isLess(arr[right], arr[largest]) ) largest = right;

        if(largest != i) {
            swap( arr[i], arr[largest] );
            i = largest;
        } else break;
    }
}


template <class T>
int findNumber(Heap<T>* mine, int size)
{
    //алгоритм извлекает верх кучи и проверяет
    //приезжает или уезжает поезд
    int res = 0;
    int count = 0;
    for(int i = 0; i < size; ++i) {

        if(mine->extractMax().isLeaving) --count;
        else ++count;

        if(count > res) res = count;

    }
    return res;
}


int main()
{
    int num = 0;
    cin >> num;
    num *= 2;
    Time* arr = new Time[num];

    //считывание данных
    int cntr = 0;
    while(cntr < num) {
        cin >> arr[cntr++].time;
        cin >> arr[cntr].time;
        arr[cntr++].isLeaving = true;
    }

    Heap<Time>* mine = new Heap<Time>( arr, num );
    cout << findNumber(mine, num);
    delete[] arr;
    delete mine;
    return 0;
}

