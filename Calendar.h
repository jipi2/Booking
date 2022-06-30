#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>

using std::string;
//acest calendar este valabil pt 2022

enum Months
{
	Ianuarie = 31 ,Februarie = 28,Martie = 31, Aprilie =30, Mai = 31, Iunie = 30, Iulie = 31, August = 31,
	Septembrie = 30,Octombrie = 31, Noiembrie = 30, Decembrie = 31
};

class Calendar
{
private:

	 int firstDay[12] = {6,2,2,5,7,3,5,1,4,6,2,4}; //1 = luni 
	 Months luna_inceput;
	 Months luna_final;
	 int zi_inceput;
	 int zi_final;
	 string str_months[12] = { "Ianuarie","Februarie","Martie","Aprilie","Mai","Iunie","Iulie","August","Septembrie","Octombrie","Noiembrie","Decembrie" };
	
public:
	Calendar() {}
	int addData(const int& zi_1, const string& luna_1, const int& zi_2, const string& luna_2);
	int getMonthIndex(const string& luna);
	int getDiferntaLuni(const string& luna_1, const string& luna_2);

	friend class CazareAbs;
	friend int getZileWeekend( const int& zi_1, const int& zi_2, const string& luna_1, Calendar& cal);

	~Calendar() {}
};

