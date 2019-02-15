#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

//Можно создавать любое количество любых вспомогательных классов, структур и методов для решения задачи.

void swap(int* ages, int a, int b)
{
    ages[a] += ages[b];
    ages[b] = ages[a] - ages[b];
    ages[a] = ages[a] - ages[b];
}

void heapify(int* ages, int n, int i)
{
    int max;
    if ((n > 2 * i + 1) && (ages[2 * i + 1] > ages[i]))
        max=2*i+1;
    else max = i;
    if ((n > 2 * i + 2) && (ages[2 * i + 2] > ages[max]))
        max=2*i+2;
    if (max!=i)
    {
        swap(ages, i, max);
        heapify(ages, n, max);
    }
}

void heapBuild(int* ages, int n)
{
    for (int i = (n / 2)-1; i >= 0; --i)
        heapify(ages, n, i);
}
//Функция сортировки на куче
//Необходимо реализовать данную функцию.
//Результат должен быть в массиве numbers.
void heapSort(int *numbers, int array_size)
{
    heapBuild(numbers, array_size);
    for (int i = array_size-1; i >= 1; --i)
    {
        swap(numbers,0,i);
        heapify(numbers,--array_size, 0);
    }
}

//Не удалять и не изменять метод main без крайней необходимости.
//Необходимо добавить комментарии, если все же пришлось изменить метод main.
int main() 
{
    //Объект для работы с файлами
    ReadWriter rw;

    int *brr = nullptr;
    int n;

    //Ввод из файла
    n = rw.readInt();

    brr = new int[n];
    rw.readArray(brr, n);

    //Запуск сортировки, ответ в том же массиве (brr)
    heapSort(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}