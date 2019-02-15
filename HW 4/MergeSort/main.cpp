#include "ReadWriter.h"
#include "MergeSort.h"
//iostream, fstream включены в ReadWriter.h

//Не рекомендуется добавлять собственные вспомогательные классы и методы.
//Необходимо использовать уже имеющиеся классы и методы, добавив реализацию, соответствующую описанию.
using namespace std;

//Описание методов на английском языке имеется в классе MergeSort, в файле MergeSort.h
void MergeSort::sort(int* arr, int length)
{
    divide_and_merge(arr, 0, length-1);
}

void MergeSort::merge(int* arr, int first, int second, int end)
{
    int *b = new int[end-first+1];
    int i = 0, j = first, k = second + 1;
    while (j <= second && k <= end)
    {
        if (arr[j] <= arr[k])
            b[i++] = arr[j++];
        else b[i++] = arr[k++];
    }

    while(j<=second)
        b[i++]=arr[j++];

    while(k<=end)
        b[i++]=arr[k++];

    for (int l = first; l <= end; ++l)
    {
        arr[l] = b[l-first];
    }
    delete []b;
}

void MergeSort::divide_and_merge(int* arr, int left, int right)
{
    int m = left + (right - left) / 2;
    if (left < right)
    {
        divide_and_merge(arr, left, m);
        divide_and_merge(arr, m + 1, right);
        merge(arr, left, m, right);
    }
}

int main()
{
    ReadWriter rw;

    int* brr = nullptr;
    int length;

    //Read data from file
    length = rw.readInt();

    brr = new int[length];
    rw.readArray(brr, length);

    //Start sorting
    MergeSort s;

    s.sort(brr, length);

    //Write answer to file
    rw.writeArray(brr, length);

    delete[] brr;

    return 0;
}