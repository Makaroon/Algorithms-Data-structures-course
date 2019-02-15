#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

//Можно создавать любое количество любых вспомогательных классов, структур и методов для решения задачи.
void algorithm(int* a, int l, int r)
{
    int i = l, j = r;
    int pivot = a[(l + r) / 2];

    while (i <= j)
    {
        while (a[j] > pivot)
            j--;
        while (a[i] < pivot)
            i++;

        if (i <= j)
        {
            int s = a[i];
            a[i] = a[j];
            a[j] = s;
            j--;
            i++;
        }
    }

    if (l < j)
        algorithm(a, l, j);
    if (i < r)
        algorithm(a, i, r);
}

//Необходимо реализовать алгоритм быстрой сортировки.
//В качестве опорного элемента выбирать случайный
void quickSort(int* numbers, int array_size)
{
    algorithm(numbers, 0, array_size - 1);
}

//Не удалять и не изменять метод main без крайней необходимости.
//Необходимо добавить комментарии, если все же пришлось изменить метод main.
int main()
{
    //Объект для работы с файлами
    ReadWriter rw;

    int* brr = nullptr;
    int n;

    //Ввод из файла
    n = rw.readInt();

    brr = new int[n];
    rw.readArray(brr, n);

    //Запуск сортировки, ответ в том же массиве (brr)
    quickSort(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}