#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const std::string fileName = "file_ofstream_trunc";

void _out()
{
	ofstream fout(fileName, std::ios::out);

	if (!fout.is_open())
	{
		cout << "open file failed." << endl;
		return;
	}
	fout << "aaa" << endl;
}

void _app()
{
	ofstream fout(fileName, std::ios::out | std::ios::app);

	if (!fout.is_open())
	{
		cout << "open file failed." << endl;
		return;
	}
	fout << "aaa" << endl;
}

void _trunc()
{
	ofstream fout(fileName, std::ios::trunc);
	
	if (!fout.is_open())
	{
		cout << "open file failed." << endl;
		return;
	}
	fout << "aaa" << endl;
}

int main()
{
	_trunc();	
}










