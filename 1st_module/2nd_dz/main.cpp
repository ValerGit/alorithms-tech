#include <iostream>

using namespace std;

struct Result
{
    Result() {}

    Result(int x, int y) : firstArr(x), secArr(y) {}

    int firstArr = 0;
    int secArr = 0;
};


Result findMaxSum(int* first, int* second, int size)
{
    //элементы с макс суммой
    Result best(0, 0);
    //наибольший элемент первого массива
    int biggestFirst = 0;
    //макисмальная сумма
    int sum = first[best.firstArr] + second[best.secArr];
    for(int i = 1; i < size ; ++i)
    {
        //больший элемент второго массива всегда будет предпочтительнее
        if(second[i] > second[best.secArr])
        {
            best.secArr = i;
        }
        //для поиска оптимальной суммы всегда сохраняем
        //наибольший элемент первого массива
        if(first[i] > first[biggestFirst])
        {
            biggestFirst = i;
        }
        //проверка не дают ли текущий элемент второго массива и наибольший первого
        //самую большую сумму
        if((first[biggestFirst] + second[i]) >
                (first[best.firstArr] + second[best.secArr]))
        {
            best.secArr= i;
            best.firstArr = biggestFirst;
            sum = first[best.firstArr] + second[best.secArr];
        }
    }
    return best;
}

int main()
{
    //Входные параметры
    int n = 0;
    cin >> n;
    if(n <= 0) return 0;

    int* first = new int[n];
    int* second = new int[n];
    for(int i = 0 ; i < n; ++i)
    {
        cin >> first[i];
    }
    for(int i = 0 ; i < n; ++i)
    {
        cin >> second[i];
    }

    Result final = findMaxSum(first, second, n);
    cout << final.firstArr << " " << final.secArr;

    delete[] first;
    delete[] second;
    return 0;
}

