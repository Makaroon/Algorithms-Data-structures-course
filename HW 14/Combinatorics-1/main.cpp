//
//  main.cpp
//  A
//
//  Created by Данил Нечай on 02.04.2018.
//  Updated by Плесовских Александр on 07.09.2018.
//  Finished by Ясиновский Александр on 24.05.2019.
//  Copyright © 2018 Данил Нечай. All rights reserved.
//

#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

//Необходимо реализовать 3 метода (1,2,3).
//Вся информация о задаче доступна в тексте задачи и в слайдах презентации к семинару(в ЛМС)
static BigInteger FactTree(int n) //subtask 1
{
    BigInteger a(1);
    for (int i = 1; i < n; ++i)
        a *= (i + 1);
    return a;
}

static BigInteger C(int n, int k)//subtask 2
{
    int maxN = max(n - k, k);
    BigInteger a(1);
    for (int i = maxN; i < n; ++i)
        a *= (i + 1);
    a /= FactTree(n - maxN);
    return a;
}

static BigInteger Pair(int n)//subtask 3
{
    BigInteger a(1);
    for (int i = 1; i < (n - 2); i += 2)
        a *= (i + 2);
    return a;
}

int main(int argc, const char* argv[])
{

    int n, N, K;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open())
    {
        string str;
        getline(fin, str);
        N = atoi(str.c_str());
        n = N;
        getline(fin, str);
        K = atoi(str.c_str());
        fout << FactTree(N) << endl;
        fout << C(N, K) << endl;
        fout << Pair(N) << endl;
        fout.close();
        fin.close();
    }
    return 0;
}
