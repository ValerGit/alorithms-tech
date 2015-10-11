#include <iostream>
#include <cstdio>
#include <assert.h>

using namespace std;
const int startSize = 1;
const int growFactor = 2;
int cinBuff = 2;

class Stack
{
public:
    Stack();
    Stack(const Stack&);
    ~Stack();

    void push(int);
    char pop();
    void print() const;

private:
    void grow();
    char* arr;
    int size;
    int buffSize;
};

Stack::Stack()
{
    buffSize = startSize;
    arr = new char[buffSize];
    size = 0;
}

Stack::Stack(const Stack &obj)
{
    buffSize = size = obj.size;
    arr = new char[size];
    for(int i = 0; i < size; ++i) {
        arr[i] = obj.arr[i];
    }
}

Stack::~Stack()
{
    delete[] arr;
}

void Stack::grow()
{
    buffSize *= growFactor;
    char* temp = new char[buffSize];
    for(int i = 0; i < size; ++i) {
        temp[i] = arr[i];
    }
    delete[] arr;
    arr = temp;
}

void Stack::push(int n)
{
    if(size == buffSize) grow();
    arr[size++] = n;
}

char Stack::pop()
{
    if(size == 0)
    {
        return -1;
    }
    return arr[--size];
}

void Stack::print() const
{
    cout << endl;
    cout << "-------------------------------------" << endl;
    for(int i = 0; i < size; ++i)
    {
        cout << arr[i] <<" ";
    }
    cout << endl;
    cout << "-------------------------------------" << endl;
}

//функция проверяет равны строки
bool equalWords(char* first, char* second, int n)
{
    assert(n >= 0);
    for(int i = 0; i < n; ++i)
    {
        if(first[i] != second[i])return false;
    }
    return true;
}


bool isAnagramm(char* A, char* B, int size) {
    assert(size >= 0);
    Stack* stack = new Stack;
    char* result = new char[size];

    for(int iterA = 0; iterA < size; ) {
        int iterB = iterA;
        while(iterB < size) {
            stack->push(B[iterB]);
            if(A[iterA] == B[iterB]) {
                ++iterB;
                break;
            }
            ++iterB;
        }
        for(int i = iterA; i < iterB; ++i) {
            result[i] = stack->pop();
        }
        iterA = iterB;
    }
    if(equalWords(A, result, size)) {
        delete[] result;
        return true;
    }
    delete stack;
    delete[] result;
    return false;
}

// функция увеличивающая буффер для считывания stdin в growFactor раз
void cinGrow(char*& array, int size)
{
    cinBuff *= growFactor;
    char* temp = new char[cinBuff];
    for(int i = 0; i < size; ++i) {
        temp[i] = array[i];
    }
    delete[] array;
    array = temp;
}

int main()
{
    //считывание
    char* first = new char[cinBuff];
    int size = 0;
    while(1) {
        if(size == cinBuff) cinGrow(first, size);
        char temp = getchar();
        if(temp < 'A' || temp > 'Z') break;
        else first[size++] = temp;
    }
    //массив для второго слова
    char* second = new char[size];
    int j = 0;
    while(1) {
        char temp = getchar();
        if(temp <'A' || temp > 'Z') break;
        else second[j++] = temp;
    }
    if(j != size) {
        delete[] first;
        delete[] second;
        cout << "NO";
        return 0;
    }
    if(isAnagramm(first,second,size)) cout << "YES";
    else cout << "NO";
    delete[] first;
    delete[] second;
    return 0;
}
