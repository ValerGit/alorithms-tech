#include <iostream>

using namespace std;

const int initSize = 1, growFactor = 2;

class Deque
{
public:
    Deque();
    ~Deque();

    void pushFront(int num);
    void pushBack(int num);
    int popFront();
    int popBack();
    void print() const;

private:
    int* arr;
    int size;
    int buffSize;
    int frontIndex;
    int backIndex;
    void grow();
};

Deque::Deque()
{
    buffSize = initSize;
    arr = new int[buffSize];
    size = frontIndex = backIndex = 0;
}

Deque::~Deque()
{
    delete[] arr;
}

//вычисляет место для следующего элемента в начале дека и записывает его туда
//указатель frontIndex указывает непосредственно на новый элемент
void Deque::pushFront(int num)
{
    if(size == buffSize) grow();
    frontIndex = (frontIndex + buffSize - 1) % buffSize;
    arr[frontIndex] = num;
    ++size;
}

//возвращает первый элемент в начале и сдвигает индекс frontIndex вперед
int Deque::popFront()
{
    if(size == 0) return -1;
    int temp = arr[frontIndex];
    frontIndex = (frontIndex + 1) % buffSize;
    --size;
    return temp;
}

//вычисляет место для следующего элемента в конце дека и записывает его туда
//указатель backIndex указывает на элемент следующий за добавленным
void Deque::pushBack(int num)
{
    if(size == buffSize) grow();
    arr[backIndex] = num;
    backIndex = (backIndex + 1) % buffSize;
    ++size;
}

//возвращает первый элемент в конце и сдвигает индекс backIndex назад
int Deque::popBack()
{
    if(size == 0) return -1;
    backIndex = (backIndex + buffSize - 1) % buffSize;
    --size;
    return arr[backIndex];
}

//динамически увеличивает буфер в growFactor раз
void Deque::grow()
{
    int prevBuff = buffSize;
    buffSize *= growFactor;
    int* temp = new int[buffSize];
    int iter = frontIndex, counter = 0;
    while(counter < size)
    {
        temp[counter++] = arr[iter];
        iter = (iter + 1) % prevBuff;
    }
    delete[] arr;
    arr = temp;
    frontIndex = 0;
    backIndex = size;
}

void Deque::print() const
{
    int iter = frontIndex, counter = 0;
    while(counter < size)
    {
        cout << arr[iter] << " ";
        iter = (iter + 1) % buffSize;
        ++counter;
    }
    cout << endl;
}

//выполняет необходимые действия с деком и возвращает правильность их работы
bool deqWork(Deque* deq, int* operation, int* value, int size)
{
    for(int k = 0; k < size; ++k)
    {
        switch(operation[k])
        {
        case 1:
        {
            deq->pushFront(value[k]);
            break;
        }
        case 2:
        {
            int j = deq->popFront();
            if(j != value[k]) return false;
            break;
        }
        case 3:
        {
            deq->pushBack(value[k]);
            break;
        }
        case 4:
        {
            int j = deq->popBack();
            if(j != value[k]) return false;
            break;
        }
        }
    }
    return true;
}

int main()
{
    Deque* deque = new Deque;
    int n = 0;
    cin >> n;
    int* operation = new int[n];
    int* value = new int [n];
    int i = 0;
    while(i < n)
    {
        cin >> operation[i];
        cin >> value[i];
        ++i;
    }

    if(deqWork(deque, operation, value, n)) cout <<"YES";
    else cout << "NO";

    delete[] operation;
    delete[] value;
    delete deque;
    return 0;
}

