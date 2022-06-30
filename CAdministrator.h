#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Utilizator.h"
#include <fstream>
#include <map>

class CAdministrator :public Utilizator
{
public:
	static CAdministrator& getInstance() {
        if (instance == nullptr)
        {
            std::ifstream fin;
            fin.open("admin.txt");

            string nume, pass;
            fin >> nume;
            fin >> pass;

            instance = new CAdministrator(nume, pass);
            fin.close();
            return (*instance);
        }
        return (*instance);
	}

    void prelucreazaRezervari();
    void addCazari();
private:
	CAdministrator(const string& name, const string& par) :Utilizator(name, par) {}
	CAdministrator(const CAdministrator& obj) :Utilizator(obj) {}  //e private ca sa nu se mai poata copia
    void aprobaRezervari(string& linie);
    void respingeRezervari(string& linie);
    void adaugaCazareFisier(string &filename, string &tip, string &nume,int &lux, int &nr_camere,int &nr_tipuri,std::map<int,int> &camere_locuri,std::map<int,int> &list_pret,int &flag,string &mese,int &pret_mese,bool nou);

	static CAdministrator* instance;
};
