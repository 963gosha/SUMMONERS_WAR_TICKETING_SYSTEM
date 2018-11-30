#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include "windows.h"
using namespace std;

struct report
{
	string code;
	string userName;
	string describeYourIssue;
	string reason;
	string description;
	string status;
	string deparment;
	string date;
}typedef Report;

bool  check_file(ifstream &f)
{
	if (f.fail())
		return false;
	return true;
}

int getReportsSize(ifstream &f)
{
	int size;
	string line;
	for (size = 0;  !f.eof(); size++)
	{
		getline(f, line);
	}
	f.seekg(0, ios::beg);
	return size / 9;
}
/*
param1:reference to the working file
return:string after the key in the txt file
raise:the function isnt reset the file run
*/
string getValueFromReport(ifstream &f)
{
	string line,value;
	getline(f, line);
	int index=line.find(":")+1;
	for (; index<line.length() ; index++)
	{
		value += line[index];
	}
	return value;
}
void getReportsData(ifstream &f, Report *data)
{
	string line;
	for (int i = 0; !f.eof(); i++)
	{
		data[i].code = getValueFromReport(f);
		data[i].userName = getValueFromReport(f);
		data[i].describeYourIssue = getValueFromReport(f);
		data[i].reason = getValueFromReport(f);
		data[i].description = getValueFromReport(f);
		data[i].status = getValueFromReport(f);
		data[i].deparment = getValueFromReport(f);
		data[i].date = getValueFromReport(f);
		getline(f, line);
	}
	f.seekg(0, ios::beg);
}

void printTicket(Report tick)
/*
param1:ticket struct
return:none
raise:none
*/
{
	string line;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	cout << "Code:"<<tick.code << endl;
	cout << "Username:"<<tick.userName << endl;
	cout << "Described issue:"<<tick.describeYourIssue << endl;
	cout << "Reason:"<<tick.reason << endl;
	cout << "Description:"<<tick.description << endl;
	cout << "Status:"<<tick.status << endl;
	cout << "Deparment:"<<tick.deparment << endl;
	cout << "Date:"<<tick.date << endl << endl;
	SetConsoleTextAttribute(hConsole, 7);
}

void printPrevCases(Report *data, int size)
/*
param1:reference to the working file
return:none
raise:none
*/
{
	system("cls");
	cout << "*****************************************************************" << endl;
	cout << "*\t\t Previous cases \t\t\t" << endl;
	cout << "*****************************************************************" << endl;
	string str, line;
	Report tmpTicket;
	for (int i = 0; i < size; i++)
	{
		if (data[i].status == "In Attention")
			printTicket(data[i]);
	}
}
void searchAndPrintByCode(Report *data, int size)
/*
param1:reference to the working file
return:none
raise:none
*/
{
	string code, line;
	Report tmpTicket;
	int count = 0;
	cout << "*****************************************************************" << endl;
	cout << "Enter the desirabled ticket by code: " << endl;
	cout << "*****************************************************************" << endl;
	cin >> code;
	for (int i = 0; i < size; i++)
	{
		if (data[i].code == code)
		{
			printTicket(data[i]);
			break;
		}
		if (i + 1 == size)	/*	if next hitteration the loop will break	*/
		{
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 12);
			cout << "There no ticket with entered Code" << endl;
			SetConsoleTextAttribute(hConsole, 7);
		}
	}
}
void searchAndPrintByUserName(Report *data, int size)
/*
param1:reference to the working file
return:none
raise:none
*/
{
	string userName, line;
	Report tmpTicket;
	bool ifFoundOne = false;
	int count = 0;
	cout << "*****************************************************************" << endl;
	cout << "Enter the desirabled ticket by Username: " << endl;
	cout << "*****************************************************************" << endl;
	cin >> userName;
	for (int i = 0; i < size; i++)
	{
		if (data[i].userName == userName && data[i].status == "In Attention")
		{
			printTicket(data[i]);
			ifFoundOne = true;
		}
		if ((i + 1 == size) && ifFoundOne == false)	/*	if next hitteration the loop will break	*/
		{
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 12);
			cout << "There no ticket with entered Username" << endl;
			SetConsoleTextAttribute(hConsole, 7);
		}
	}
}
void prevCasesOptions(Report *data, int size)
/*
param1:reference to the working file
return:none
raise:none
*/
{
	bool flag = true;
	int choice;
	while (flag)
	{
		cout << "*****************************************************************" << endl;
		cout << "1) Search by 'code' " << endl << "2) Search by Username" << endl << "3) back" << endl;
		cout << "*****************************************************************" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:// Search by 'code'
		{
			searchAndPrintByCode(data, size);
			break;
		}
		case 2: // Search by Username"
		{
			searchAndPrintByUserName(data, size);
			break;
		}
		case 3: // back
		{
			flag = false;
			return;
		}
		default:
		{
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 12);
			cout << " you entered an unavilable choice try again" << endl;
			SetConsoleTextAttribute(hConsole, 7);
		}
		}
	}
}
void printNewCases(Report *data, int size)
/*
param1:reference to the working file
return:none
raise:none
*/
{
	system("cls");
	cout << "*****************************************************************" << endl;
	cout << "*\t\t New cases \t\t\t" << endl;
	cout << "*****************************************************************" << endl;
	string str, line;
	int count = 0;
	Report tmpTicket;
	for (int i = 0; i < size; i++)
	{
		if (data[i].status != "In Attention")
			printTicket(data[i]);
	}
}
void changeStatus(Report *report,int index)
/*
param1:reference to the working file
param2:struct of tmp ticket
return:none
raise:none
*/
{
	string line, trash;
	report[index].status = "In Attention";
}
void changeStatusMenu(Report *data, int size)
/*
param1:reference to the working file
return:none
raise:none
*/
{
	string code;
	Report tmpTicket;
	int index;
	cout << "*****************************************************************" << endl;
	cout << "Enter the 'Code' of the report-status you want to change:" << endl;
	cout << "*****************************************************************" << endl;
	cin >> code;
	for (int index = 0; index < size; index++)
	{
		if (data[index].code == code && data[index].status == "Received")
		{
			changeStatus(data, index);
			break;
		}
		if (index + 1 == size)	/*	if next hitteration the loop will break	*/
		{
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 12);
			cout << "error : there no ticket with entered Code" << endl;
			SetConsoleTextAttribute(hConsole, 7);
		}
	}
}
void updateReportFile(Report *data, ifstream &f, int size)
{
	ofstream temp;
	temp.open("temp.txt");
	for (int i = 0; i < size ; i++)
	{
		temp << "Code:" << data[i].code << endl;
		temp << "Username:" << data[i].userName << endl;
		temp << "Described issue:" << data[i].describeYourIssue << endl;
		temp << "Reason:" << data[i].reason << endl;
		temp << "Description:" << data[i].description << endl;
		temp << "Status:" << data[i].status << endl;
		temp << "Deparment:" << data[i].deparment << endl;
		temp << "Date:" << data[i].date << endl ;
		temp<< "'''" ;
		if (i + 1 < size)
			temp << endl;
	}
	f.close();
	temp.close();
	remove("Tickets.txt");
	rename("temp.txt", "Tickets.txt");
}
int main()
{
	int choice, reportDataSize;
	bool flag = true;
	ifstream ticketsFile("Tickets.txt");
	/*	try open file Tickets.txt	*/
	try
	{
		if (!check_file(ticketsFile))
			throw "error:couldnt open file.. ";
	}
	catch (char* str)
	{
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 12);
		cout << str << endl;
		SetConsoleTextAttribute(hConsole, 7);
		return 0;
	}
	reportDataSize = getReportsSize(ticketsFile);
	Report *data = new Report[reportDataSize];
	getReportsData(ticketsFile, data);
	while (flag)
	{
		cout << "*****************************************************************" << endl;
		cout << "*\t\t Admin manu \t\t\t*" << endl;
		cout << "*****************************************************************" << endl;
		cout << "1) Previous cases " << endl << "2) New cases" << endl << "3) back" << endl;
		cout << "*****************************************************************" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:// the admin choce go to previous cases
		{
			printPrevCases(data, reportDataSize);
			prevCasesOptions(data, reportDataSize);
			break;
		}
		case 2: // the admin choce to see new cases
		{
			printNewCases(data, reportDataSize);
			changeStatusMenu(data, reportDataSize);
			updateReportFile(data, ticketsFile , reportDataSize);
			break;
		}
		case 3: // the admin choce to go to the previous screen
		{
			flag = false;
			return 0;
		}
		default:
		{
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 12);
			cout << "eroor:you entered an unavilable choice try again" << endl;
			SetConsoleTextAttribute(hConsole, 7);
		}
		}
	}


	return 0;
}

