#include "Edge.h"
#include <iostream>
#include <fstream>
#include <vector>

class ReadWriter
{
private:

    std::fstream fin;
    std::fstream fout;

public:

    ~ReadWriter()
    {
        fin.close();
        fout.close();
    }

    ReadWriter(std::string name)
    {
        fin.open(name, std::ios::in);
        fout.open("output.txt", std::ios::out);
    }

    int read(std::vector<std::vector<int>>& x, std::string name)
    {

//        std::string line;
//        std::stringstream sstr;
//        int N;
//        float number;
//
//        getline(fin, line); // читаем из файла строку
//        sstr << line; // выводим ее в строковой поток sstr
//        for (N = 0; sstr >> number; N++);
        if (fin.is_open())
        {
            //Число пробелов в первой строчке вначале равно 0
            int n = 0;
            std::string symbol;
            while (getline(fin, symbol))//на всякий случай цикл ограничиваем концом файла
                n++;
            //Опять переходим в потоке в начало файла
            fin.close();
            fin.open(name,std::ios::in);

            //Теперь мы знаем сколько чисел в файле и сколько пробелов в первой строке.
            //Теперь можем считать матрицу.

            x = std::vector<std::vector<int>> (n, std::vector<int>(n));

            //Считаем матрицу из файла
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    fin >> x[i][j];
            fin.close();//под конец закроем файла
        } else
        {
            //Если открытие файла прошло не успешно
            std::cout << "Файл не найден.";
        }
        return 0;
    }
};