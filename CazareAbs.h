#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "ICazare.h"
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class CazareAbs :public ICazare
{
protected:
	string tip; //hotel sau pensiune
	string nume;
	Optiuni opt;
	vector<Camera> camere;
	map<int, int> preturi; //pretul camerei difera in functie de numarul de locuri
	vector<string> recenzii;

	friend void ocupa(const int& locuri,  int& nr_camere,CazareAbs &obj);
public:
	CazareAbs(const string& tip, const string& nume, const vector<Camera>& cam, const map<int, int>& preturi, const vector<string>& recen, Optiuni &op);
	
	virtual void addOptiuni(bool mic, bool cin, bool pran) override;
	virtual std::string getTip() override { return tip; }
	virtual string getNume() override { return nume;}
	virtual void printOptiuni() override;
	virtual void printRecenzii() override;
	virtual void printCamere() override;
	virtual int getPretOptiune() override { return opt.pret; }
	virtual float getPretRezervare(const int& zi_1, const std::string& luna_1, const int& zi_2, const string& luna_2, const int& loc, const int& nr_camere) override;
	virtual int verificaDisponibilitatea(const int& nr_camere, const int& locuri_camere);
	virtual void OcupareCamere(const int& data_1, const string& luna_1, const int& data_2, const string& luna_2) override;
	virtual void appendRezervare(const int& zi_1, const std::string& luna_1, const int& zi_2, const std::string& luna_2, const int& loc, const int& nr_camere)override;

	virtual ~CazareAbs() {}
};

