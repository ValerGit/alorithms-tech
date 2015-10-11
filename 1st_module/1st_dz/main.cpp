#include <iostream>

using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    if(n <= 0 || n > 1000)
    {
        if(n == 0) cout << "0";
        return 0;
    }


    int prev = 1, sum = 1;
    cout << sum;

    for(int curr = 2; curr <= n; ++curr)
    {
        //в sum складывается количество
        //предыдуших элементов повторенных curr раз
        sum += prev;

        //добавляется необходимая дельта в размере текущего элемента
        sum += curr;

        //предыдущему элементу присваивается значение текущего
        prev = curr;
        cout << " " << sum;
    }
    return 0;
}

