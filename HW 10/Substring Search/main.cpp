#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

//Основная задача - реализовать данный метод
//Можно изменить передачу параметров на ссылки (&)
//Можно добавлять любое количество любых вспомогательных методов, структур и классов
void getSubstrings(string& source, string& substring, vector<int>& res)
{
	
}

//Не изменять метод main без крайней необходимости
//ОБЯЗАТЕЛЬНО добавить в комментариях подробные пояснения и причины побудившие вас изменить код этого метода.
int main()
{
	string t;
	string p;
	vector<int> res;

	ifstream fin;
	fin.open("input.txt");
	if (fin.is_open())
	{
		getline(fin, t);
		getline(fin, p);
		fin.close();
	}

	getSubstrings(t, p, res);

	fstream fout;
	fout.open("output.txt", ios::out);
	fout << res.size() << "\n";
	for (std::vector<int>::const_iterator i = res.begin(); i != res.end(); ++i)
		fout << *i << "\n";
	fout.close();

	return 0;
}
