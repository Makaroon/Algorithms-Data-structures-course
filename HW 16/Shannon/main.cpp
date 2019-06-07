
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
using namespace std;

class ShannonFano
{
public:
    ShannonFano()// можно изменить что бы принимал на вход количесво элементов
    {
        
    }

    void build()
    {
        // запускает алгоритм (после того как были добавлены все элементы)
    }
    void addChance (int chance)
    {
      // добавляет элемент в список (дерево, все зависит от реализации)
    }
    string get (int i)
    {
        // выдает битовый код i символа
    }

};


int main() {

		    int n;
    ShannonFano * shf = new ShannonFano();
 
    fstream fin;
        fin.open("input.txt",ios::in);
        if(fin.is_open()) {
            fin >> n;
            for (int i = 0; i < n; i++) {
                int x;
                fin >> x;
				shf->addChance (x);
            }
    
            fin.close();
       
        shf->build();
        fstream fout;
        fout.open("output.txt",ios::out);
            for (int i = 0; i < n; i++){
                fout <<shf->get(i) << (i==n-1?"":" ");
                }
        fout.close();
        delete shf;
            
        }
        return 0;		
}