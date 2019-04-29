#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

string getLCS(string x, string y)
{
    return "";
}

int main()
{
	string x;
	string y;
	string res;

	ifstream fin;
	fin.open("input.txt");
	if (fin.is_open())
	{
		getline(fin, x);
		getline(fin, y);
		fin.close();
	}

	res = getLCS(x, y);

	fstream fout;
	fout.open("output.txt", ios::out);
	fout << res;
	fout.close();

	return 0;
}

