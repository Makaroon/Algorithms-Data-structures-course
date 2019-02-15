#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

union UN
{
    unsigned int a;
    unsigned char ch[4];
};

// Функция цифровой сортировки
void radixSort(int* numbers, int array_size)
{
    int* c = new int[256];
    int* b = new int[array_size];
    UN un;
    for (int j = 0; j < 4; ++j)
    {
        for (int i = 0; i < 256; ++i)
            c[i]=0;
        for (int i = 0; i < array_size; ++i)
        {
            un.a = static_cast<unsigned int>(numbers[i]);
            c[un.ch[j]]++;
        }
        for (int i = 1; i < 256; ++i)
            c[i] += c[i - 1];
        for (int i = array_size-1; i >= 0; --i)
        {
            un.a = static_cast<unsigned int>(numbers[i]);
            b[c[un.ch[j]]-1]=numbers[i];
            c[un.ch[j]]=c[un.ch[j]]-1;
        }
        for (int i = 0; i < array_size; ++i)
            numbers[i] = b[i];
    }
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
    radixSort(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}
