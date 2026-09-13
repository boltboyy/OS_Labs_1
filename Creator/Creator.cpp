#include <iostream>
#include <cstdlib>
#include "employee.h"
#include <iomanip>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Please enter the correct number of arguments." << '\n';
		return 1;
	}
	const char* FileName = argv[1];
	int n = atoi(argv[2]);
	if (n <= 0)
	{
		cout << "Number of records isn't positive." << '\n';
		return 1;
	}
	ofstream file(FileName, ios::binary);
	if (!file)
	{
		cout << "file isn't open" << '\n';
		return 1;
	}
	employee e;
	cout << "Enter number, name, hours: " << '\n';
	for (int i = 0; i < n; i++)
	{
		cin >> e.num;
		cin >> setw(10) >> e.name;
		cin >> e.hours;
		file.write(reinterpret_cast<const char*>(&e), sizeof(e));
	}
	file.close();
	cout << "File created." << '\n';

	return 0;
}