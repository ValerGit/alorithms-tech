/*
 * Дана очень длинная последовательность целых чисел длины n.
 * Требуется вывести в отсортированном виде её первые k элементов. Последовательность
 * может не помещаться в память. Время работы O(n * log(k)). Доп. память O(k).
 * Использовать слияние.
 */

#include <iostream>

using namespace std;

void morzh(int* A, int left, int mid, int right)
{
    int iter1 = 0, iter2 = 0;
    int* temp = new int[right - left];
    while(((left + iter1) < mid) && ((mid + iter2) < right))
    {
        if(A[left + iter1] < A[mid + iter2])
        {
            temp[iter1 + iter2] = A[left + iter1];
            ++iter1;
        }
        else
        {
            temp[iter1 + iter2] = A[mid + iter2];
            ++iter2;
        }
    }
    while((left + iter1) < mid)
    {
        temp[iter1 + iter2] = A[left + iter1];
        ++iter1;
    }
    while((mid + iter2) < right)
    {
        temp[iter1 + iter2] = A[mid + iter2];
        ++iter2;
    }
    for(int i = 0; i < (right - left); ++i)
    {
        A[left + i] = temp[i];
    }
    delete[] temp;
}

void mergeSort(int* A, int start, int end)
{
    if(start + 1 >= end) return;
    int mid = (start + end) / 2;
    mergeSort(A, start, mid);
    mergeSort(A, mid , end);
    morzh( A, start, mid, end );
}

void mix(int* A, int* B,int sizeB, int k)
{
    int* C = new int[k];
    int iterA = 0, iterB = 0;
    while ((iterB < sizeB) && (iterA + iterB < k))
    {
        if(A[iterA] < B[iterB])
        {
            C[iterA + iterB] = A[iterA];
            ++iterA;
        }
        else
        {
            C[iterA + iterB] = B[iterB];
            ++iterB;
        }
    }
    while((iterA + iterB < k))
    {
        C[iterA + iterB] = A[iterA];
        ++iterA;
    }
    while((iterB < sizeB) && (iterA + iterB < k))
    {
        C[iterA + iterB] = B[iterB];
        ++iterB;
    }
    for(int i = 0; i < k; ++i)
    {
        A[i] = C[i];
    }
    delete[] C;
}


void makeMerge(int* result, int k, int n) {
    mergeSort(result, 0, k);
    int *auxiliry = new int[k];

    for(int i = k; i < n; ) {

        int end = 0;
        if ((i + k) >= n) end = n;
        else end = i + k;

        int size = end - i;
        for (int j = 0; j < size; ++j) {
            cin >> auxiliry[j];
        }
        mergeSort(auxiliry, 0, size);
        mix(result, auxiliry, size, k);

        i = end;
    }
    delete[] auxiliry;
}


int main()
{
    int  n = 0, k = 0;
    cin >> n >> k;
    int* result = new int[k];
    for(int j = 0; j < k; ++j)
    {
        cin >> result[j];
    }
    makeMerge( result, k, n );

    for(int i = 0; i < k; ++i)
    {
        cout << result[i] <<" ";
    }

    delete[] result;
    return 0;
}
