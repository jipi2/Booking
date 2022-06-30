#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Utilizator.h"

class CClient : public Utilizator
{
private:
	int nr_rezervari = 0;
public:
	CClient(const string& name, const string& par) :Utilizator(name, par) {}

	int getBonusFidelitate();
	int getNrRezervari() { return nr_rezervari; }
	void changePassword(const string& new_pass) { pass = new_pass; }
	void rezerva(const int& data_1, const string& luna_1, const int& data_2, const string& luna_2, const int &locuri, const int &nr_camere, const string &nume_cazare);
	int verificaRezervare(const int& data_1, const string& luna_1, const int& data_2, const string& luna_2, const int& locuri, const int& nr_camere, const string& nume_cazare); //verificam sa nu mai fie aceeasi rezervare deja facuta
	void updateNrRezervari();
	void scrieRecenzie();
	void afisIstoricCazari();
	friend std::ostream& operator<< (std::ostream& out, const CClient& obj)
	{
		out <<"Username: " << obj.username << "\n";
		out << "Password: " << obj.pass << "\n";
		return out;
	}

	virtual ~CClient() {}
};

