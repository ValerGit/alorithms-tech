#include <iostream>

using namespace std;

int nut_number(int x) {
    return (x*(x-1)/2);
}

void placing_X_into_Y_column(int **&arr, int x, int y, int start, int end) {

    for (int i = start; i < end; ++i) {
        arr[i][y] = x;
    }

}

int sum_of_intersect(int** arr, int x, int y) {
    int sum = 0;
    for(int i = x, j = y; i >= 0; --i, ++j) {
        sum += arr[i][j];
    }
    return sum;
}

int main() {
    int n = 0;
    cin >> n;
    if(n <= 0) cout << "0";
    return 0;
    ++n;
    //массив с возможными вариантами построения пирамидок из i-го количества кубиков
    int **arr = new int *[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = new int[n];
    }

    //заполняем всю матрицу нулями
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; ++j) {
            arr[i][j] = 0;
        }
    }

    //один способ положить на верх ноль
    placing_X_into_Y_column(arr, 1, 0, 0, n);

    for (int i = 1; i < n; ++i) {

        //вычисляем все возможные способы  построить из i кубиков пирамиду
        //(x + y = i) где x и y индексы в матрице
        int sum = sum_of_intersect(arr, i, 0);
        placing_X_into_Y_column(arr, sum, i, i + 1, n);

        //на i кубиках не может лежать i кубиков - поэтому пересечение
        //вычисляем отдельно
        arr[i][i] = sum_of_intersect(arr, i-1, 1);

    }

    //имеем нижнюю треугольную матрицу -
    //заполним ячейкина необходимой нам диагонали (x + y = n - 1)
    int half = n / 2 - 1;

    for (int x = half, y = n - half - 1; x >= 0; --x, ++y) {
        arr[x][y] = sum_of_intersect(arr, x-1, y - x + 1);
    }

    //пройдемся по нужной нам диагонали и просуммруем все ячейки
    int sum = sum_of_intersect(arr, n-1, 0);

    cout << sum;
//    for (int bottom = 0; bottom < n; ++bottom) {
//        for (int top = 0; top < n ; ++top) {
//            cout << arr[bottom][top] << " ";
//        }
//        cout << endl;
//    }
    return 0;
}

