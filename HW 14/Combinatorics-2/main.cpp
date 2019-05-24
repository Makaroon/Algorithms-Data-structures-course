#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

//Необходимо реализовать данный метод
//Вся информация о задаче доступна в тексте задачи и в слайдах презентации к семинару(в ЛМС)
static string get_day(int N,int k)
{
 
}

int main(int argc, const char * argv[]) {

    int N,K;
    fstream fin;
    fstream fout;
    fin.open("input.txt",ios::in);
    fout.open("output.txt",ios::out);
    if(fin.is_open()) {
        string str;
        getline(fin,str);
        N = atoi( str.c_str());
 
        getline(fin,str);
        K = atoi( str.c_str());
         fout << get_day(N,K)<< endl;
       
        fout.close();
        fin.close();
    }
    
    return 0;
}
