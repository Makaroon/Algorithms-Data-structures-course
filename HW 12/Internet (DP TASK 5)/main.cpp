#include <iostream>
#include <fstream>
#include <vector>


using namespace std;


int countMinSum(int seconds, vector<int>& values)
{
	
}


int main()
{
	vector<int> values;
	int value = 0, seconds = 0;
	
	ifstream fin;
	fin.open("input.txt");
	if (fin.is_open())
	{
		fin >> seconds;
		for (int i = 0; i < N; i++)
		{
			fin>>value;
			values.push_back(value);
		}
		fin.close();
	}
	
	int res = countMinSum(seconds, values);
	
	fstream fout;
	fout.open("output.txt", ios::out);
	fout << res;
	fout.close();
	
	return 0;
}
