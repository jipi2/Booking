#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include "Calendar.h"

typedef struct camera
{
	int locuri;
	bool ocupat; // 1 -> ocupat  ; 0 ->liber

}Camera;

typedef struct optiunui
{
	bool micDeJun;
	bool pranz;
	bool cina;
	int pret;

}Optiuni;

class ICazare
{
public:
	virtual std::string getTip() = 0; //hotel sau pensiune
	virtual std::string getNume() = 0;
	virtual void printOptiuni() = 0;
	virtual void printRecenzii() = 0;
	virtual int getLux() = 0; //hotel -> nr stele ; pensiune -> nr margarete
	virtual void printCamere() = 0;
	virtual void addOptiuni(bool mic, bool cin, bool pran) = 0;
	virtual int getPretOptiune() = 0;
	virtual void afis() = 0;
	virtual float getPretRezervare(const int& zi_1, const std::string& luna_1, const int& zi_2, const string& luna_2, const int& loc, const int& nr_camere)=0;
	virtual int verificaDisponibilitatea(const int& nr_camere, const int& locuri_camere) = 0;
	virtual void OcupareCamere(const int &data_1, const std::string &luna_1, const int &data_2, const std::string &luna_2) = 0;
	virtual void appendRezervare(const int& zi_1, const std::string& luna_1, const int& zi_2, const std::string& luna_2, const int& loc, const int& nr_camere) = 0;
};

/*
Exemplu de format fisier:

Hotel
Hotel Brasov Frumos
4 //nr stele sau marg
10 //numarul camerelor
2 //cate tipuri de camera
5 - 2 //5 cu 2 locuri
5 - 3 //5 cu 3 locuri
2 - 150 // cu 2  locuri costa 150
3 - 250 // cu 3 locuri costa 400
 Pranz Cina //mesele disponibilie

*/