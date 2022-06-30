#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "ICazare.h"
#include <vector>


class CazareList
{
public:
	static CazareList& getInstance()
	{
		if (instance == nullptr)
		{
			instance = new CazareList();
			return *instance;
		}
		return *instance;
	}
	static void destroy()
	{
		if (instance != nullptr)
			delete instance;
	}
	void addVector(std::vector<ICazare*> v) { this->vect = v; }
	void print();

	ICazare& operator[] (const int& index)
	{
		if (index < vect.size())
			return *vect[index];
	}

	void ocupa(const int& data_1, const string& luna_1, const int& data_2, const string& luna_2);
	int printDisponibile(std::vector<string> &cazari,const int& data_1, const string& luna_1, const int& data_2, const string& luna_2, const int& locuri, const int& nr_camere, const float& bonus);
	int getCazare(const string& nume);
	void printRecenzii(const string &numeCazare);

private:
	std::vector<ICazare*> vect;
	static CazareList* instance;

	CazareList(){}
	CazareList(const CazareList& obj){}
	~CazareList();
};

