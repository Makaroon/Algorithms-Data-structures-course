#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
using namespace std;

class Huffman
{
public:

    void build()
    {
        // зупскает алгоритм (после того как были добавлены все элементы)
       
    }
    void addChance (int chance)
    {
      // добовляет елемент в список (дерево, все зависит от реализации)

    }
    string get (int i)
    {
        // выдает битовый код i символа
    }

};


int main() {

    int n;
    Huffman * huff = new Huffman();
    fstream fin;
        fin.open("input.txt",ios::in);
        if(fin.is_open()) {
            fin >> n;
            for (int i = 0; i < n; i++) {
                int x;
                fin >> x;
               huff->addChance (x);
            }
    
            fin.close();
       
        huff->build();
        fstream fout;
        fout.open("output.txt",ios::out);
            for (int i = 0; i < n; i++){
                fout << huff->get(i) << (i==n-1?"":" ");
                }
        fout.close();
        delete huff;
            
        }
  
        return 0;

}

