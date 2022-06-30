#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "CClient.h"
#include <vector>
#include <fstream>

class CClientList
{
public:
	static CClientList& getInstance()
	{
		if (CClientList::instance == nullptr)
		{
			CClientList::instance = new CClientList();

			std::ifstream fin;
			fin.open("clienti.txt");
			string nume, pass;

			while (!fin.eof())
			{
				fin >> nume;
				fin >> pass;

				CClientList::instance->vect.push_back(CClient(nume, pass));
			}
			fin.close();
			return *CClientList::instance;
		}
		return *instance;
	}
	static void destory()
	{
		CClientList::instance->updateFisier();
		if (CClientList::instance != nullptr)
			delete instance;
	}
	void print()
	{
		for (auto it = vect.begin(); it < vect.end(); it++)
			std::cout << *it << "\n";
	}
	void updateFisier()
	{
		if (CClientList::instance == nullptr)
			return;

		std::ofstream fout;
		fout.open("clienti.txt");

		for (auto it = vect.begin(); it < vect.end() - 1; it++)
		{
			fout << it->getUsername() << "\n";
			fout << it->getPass() << "\n\n";
		}
		fout << (vect.end() - 1)->getUsername() << "\n";
		fout << (vect.end() - 1)->getPass();
		fout.close();
	}
	void add(const CClient& client) { vect.push_back(client); }
	CClient& operator [](const int &index);
	int existaClient(const string& nume, const string& pass);
	int existaNumeClient(const string& nume);

private:
	std::vector<CClient> vect;
	static CClientList* instance;

	CClientList() {}
	CClientList(const CClientList &obj) {}
};

