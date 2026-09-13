#include <iostream>
#include <windows.h>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <string>
#include "employee.h"

using namespace std;

int main()
{
	char fileName[256];
	int n;
	cout << "Enter fileName and n" << '\n';
	cin >> setw(256) >> fileName;
	cin >> n;
	char cmdLine[256];
	sprintf_s(cmdLine, "Creator.exe %s %d", fileName, n);
	cout << cmdLine << '\n';
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	if (!CreateProcessA(NULL, cmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		cout << "Creator isn't started." << '\n';
		return 1;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	cout << "Creator finished." << '\n';
	ifstream file(fileName, ios::binary);
	if (!file)
	{
		cout << "file isn't open" << '\n';
		return 1;
	}
	employee e;
	while (file.read(reinterpret_cast<char*>(&e), sizeof(e)))
	{
		cout << e.num << " " << e.name << " " << e.hours << '\n';
	}
	file.close();
	char reportName[256];
	double rate;
	cout << "Enter report file name and rate per hour" << '\n';
	cin >> setw(256) >> reportName;
	cin >> rate;
	char cmdLine2[256];
	sprintf_s(cmdLine2, "Reporter.exe %s %s %g", fileName, reportName, rate);
	cout << cmdLine2 << '\n';
	STARTUPINFOA si2;
	PROCESS_INFORMATION pi2;
	ZeroMemory(&si2, sizeof(si2));
	si2.cb = sizeof(si2);
	if (!CreateProcessA(NULL, cmdLine2, NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2))
	{
		cout << "Reporter isn't started." << '\n';
		return 1;
	}
	WaitForSingleObject(pi2.hProcess, INFINITE);
	CloseHandle(pi2.hThread);
	CloseHandle(pi2.hProcess);
	ifstream rep(reportName);
	if (!rep)
	{
		cout << "Report file isn't open" << '\n';
		return 1;
	}
	string line;
	while (getline(rep, line))
	{
		cout << line << '\n';
	}
	rep.close();
	return 0;
}