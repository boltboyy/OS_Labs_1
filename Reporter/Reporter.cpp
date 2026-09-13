#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include "employee.h"

using namespace std;

bool compare(const employee& a, const employee& b)
{
	return a.num < b.num;
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Number of arguments isn't right." << '\n';
		cout <<"Usage: Reporter.exe <binary file> <report file> <rate per hour>" << '\n';
		return 1;
	}
	const char* FileName = argv[1];
	double rate = atof(argv[3]);
	if (rate <= 0)
	{
		cout << "Money per hour must be positive." << '\n';
		return 1;
	}
	ifstream file(FileName, ios::binary);
	if (!file)
	{
		cout << "File isn't open" << '\n';
		return 1;
	}
	employee e;
	vector <employee> v;
	while (file.read(reinterpret_cast<char*>(&e), sizeof(e)))
	{
		v.push_back(e);
	}
	sort(v.begin(), v.end(), compare);
	ofstream report(argv[2]);
	if (!report)
	{
		cout << "report isn't open" << '\n';
		return 1;
	}
	report << left;
	report << "Report for file " << FileName << '\n';
	report << setw(8) << "Num" << setw(12) << "Name" << setw(10) << "Hours" << "Salary" << '\n';
	report << fixed << setprecision(2);
	for (size_t i = 0; i < v.size(); i++)
	{
		cout << v[i].num << " " << v[i].name << " " << v[i].hours << '\n';
		report << setw(8) << v[i].num << setw(12) << v[i].name << setw(10) << v[i].hours << v[i].hours * rate << '\n';
	}
	cout << "Report created." << '\n';
	report.close();
	return 0;
}