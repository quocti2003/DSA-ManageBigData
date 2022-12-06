#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "my_lib.h"
using namespace std;
int main()
{
	ifstream fi;
	ofstream fo;
	string input = "", output = "sorted_books_rating.csv", temp = "";
	cout << "Input_File name: ";
	getline(cin, input);
	vector<BOOK> lib;
	Get_Book(input, temp, lib);
	Merge_Sort(lib, 0, 3000000);
	Export_Excel(output,temp, lib);
	return 0;
}