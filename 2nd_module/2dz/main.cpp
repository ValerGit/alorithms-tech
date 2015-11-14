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

    Time() : isLeaving(false), time(0) { }
    Time(int n) : isLeaving(false), time(n) { }
    Time(const Time& obj) : isLeaving(obj.isLeaving), time(obj.time) {}
};

ostream &operator<<(ostream &os, const Time &n) {
    cout << n.time << " ";
    return os;
}

bool isLess(const Time &one, const Time &two) {
    if (one.time == two.time) {
        if (one.isLeaving) return false;
        else return true;
    }
    return one.time < two.time;
}

template<typename T>
class Heap {
public:
    Heap() { }
    Heap(int);
    ~Heap();

    void addElement(T);
    T extractMin();
    int size;

private:
    void siftDown(int index);
    void siftUp(int index);

    T *arr;
    int buff_size;
};

template<typename T>
Heap<T>::Heap(int n) {
    size = 0;
    buff_size = n;
    arr = new T[n];
}

template<typename T>
Heap<T>::~Heap() {
    delete[] arr;
}


template<typename T>
void Heap<T>::addElement(T obj) {
    if(size > buff_size) return;
    arr[size++] = obj;
    siftUp(size - 1);
}

template<typename T>
T Heap<T>::extractMin() {
    T temp = arr[0];
    swap(arr[0], arr[--size]);
    siftDown(0);
    return temp;
}

template<typename T>
void Heap<T>::siftUp(int index) {
    int i = index;
    while (i > 0) {
        int upper = (i - 1) / 2;
        if (isLess(arr[i], arr[upper])) {
            swap(arr[i], arr[upper]);
            i = upper;
        } else break;
    }
}

template<typename T>
void Heap<T>::siftDown(int index) {
    for (int i = index; 2 * i + 2 <= size;) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < size && isLess(arr[left], arr[smallest])) smallest = left;
        if (right < size && isLess(arr[right], arr[smallest])) smallest = right;

        if (smallest != i) {
            swap(arr[i], arr[smallest]);
            i = smallest;
        } else break;
    }
}

//алгоритм извлекает корень кучи и проверяет
//приезжает или уезжает поезд
template<class T>
int findNumber(Heap<T> *mine) {
    int res = 0, count = 0, size = mine->size;
    for (int i = 0; i < size; ++i) {

        if (mine->extractMin().isLeaving) --count;
        else ++count;

        if (count > res) res = count;

    }
    return res;
}


int main() {
    int num = 0;
    cin >> num;
    num *= 2;

    Heap<Time> *mine = new Heap<Time>(num);
    int cntr = 0;
    Time temp;
    while (cntr < num) {

        cin >> temp.time;
        temp.isLeaving = false;
        mine->addElement(temp);
        ++cntr;

        cin >> temp.time;
        temp.isLeaving = true;
        mine->addElement(temp);

        ++cntr;
    }

    cout << findNumber(mine);
    delete mine;
    return 0;
}

