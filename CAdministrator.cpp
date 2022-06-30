#define _CRT_SECURE_NO_WARNINGS
#include "CAdministrator.h"
#include "Log.h"
#include "Eroare.h"
#include <string>
#include <sstream>
#include <vector>

void CAdministrator::aprobaRezervari(string& linie)
{
	string user,rez;
	std::vector<string> rezervari;
	std::stringstream ss(linie);
	ss >> user;
	linie = linie.erase(0, user.length() + 3);
	
	std::ifstream fin((user + "_rez.txt"));
	while (getline(fin, rez))
		rezervari.push_back(rez);

	for (auto it = rezervari.begin(); it < rezervari.end(); it++)
	{
		if (it->find(linie) != string::npos)
		{
			(*it) = (*it).substr(0, linie.length());
			(*it) = (*it) + " aprobat";
		}
	}
	fin.close();

	std::ofstream fout((user + "_rez.txt"));
	for (auto it = rezervari.begin(); it < rezervari.end(); it++)
	{
		fout << "\n" << (*it);
	}
	fout.close();

	Log& ref = Log::getInstance();
	ref.write(("Rezervare_aprobata: Administratorul a aprobat rezervarea facuta de catre utilizatorul " + user + "\n"));
}

void CAdministrator::respingeRezervari(string& linie)
{
	string user, rez;
	std::vector<string> rezervari;
	std::stringstream ss(linie);
	ss >> user;
	linie = linie.erase(0, user.length() + 3);

	std::ifstream fin((user + "_rez.txt"));
	while (getline(fin, rez))
		rezervari.push_back(rez);

	for (auto it = rezervari.begin(); it < rezervari.end(); it++)
	{
		if (it->find(linie) != string::npos)
		{
			(*it) = (*it).substr(0, linie.length());
			(*it) = (*it) + " respins";
		}
	}
	fin.close();

	std::ofstream fout((user + "_rez.txt"));
	for (auto it = rezervari.begin(); it < rezervari.end(); it++)
	{
		fout << (*it) << "\n";
	}
	fout.close();

	string nume_cazare = linie;

	nume_cazare = nume_cazare.substr(nume_cazare.find("-") + 1, nume_cazare.length());
	nume_cazare = nume_cazare.substr(nume_cazare.find("-") + 1, nume_cazare.length());
	nume_cazare = nume_cazare.substr(nume_cazare.find("-") + 2, nume_cazare.length());

	linie = linie.substr(0, linie.find(nume_cazare) - 3);
	std::vector<string> rez_cazare;
	std::ifstream f_in(nume_cazare + "_rez.txt");
	getline(f_in, rez);
	while (getline(f_in, rez)) rez_cazare.push_back(rez);
	f_in.close();

	std::ofstream f_out(nume_cazare + "_rez.txt");
	f_out << "Rezervari:";

	for (auto it = rez_cazare.begin(); it < rez_cazare.end(); it++)
	{
		if ((*it) != linie)
			f_out <<"\n" << (*it);
	}
	f_out.close();

	Log& ref = ref.getInstance();
	ref.write(("Rezervare_Anulata: Administratorul a anulat rezervarea facuta de utilizatorul " + user + " la unitatea de cazare cu numele " + nume_cazare + "\n"));
}

void CAdministrator::prelucreazaRezervari()
{
	std::cout << "Pe ecran vor aparea rezervarile care asteapta raspunsul dumneavoastra\n\n";
	std::cout << "Pentru a aproba o rezervare scrieti: 'a' de la aprobat\n";
	std::cout << "Pentru a respinge o rezervare scrieti 'r' de la respins\n\n";
	int flag = 0;

	std::ifstream fin;
	fin.open("Rezervari.txt");
	string linie, rasp;

	while (getline(fin, linie))
	{
		std::cout << linie << "\n";
		std::cin >> rasp;
		if (rasp == "a")
		{
			aprobaRezervari(linie);
		}
		else
		{
			respingeRezervari(linie);
		}

		flag = 1;
	}
	if (flag == 0)
		std::cout << "Nu este nicio rezervare in asteptare\n\n\n";
	fin.close();

	std::ofstream fout("Rezervari.txt");
	fout << "";
	fout.close();
}

void CAdministrator::adaugaCazareFisier(string& filename, string& tip, string& nume, int& lux, int& nr_camere, int& nr_tipuri, std::map<int, int>& camere_locuri, std::map<int, int>& list_pret, int& flag, string& mese, int& pret_mese, bool nou)
{
	if (tip != "Pensiune" && tip != "Hotel")
		throw Eroare("Eroare: Nu s-a putut adauga unitatea de cazare\n");

	std::ofstream fout(filename, std::ios::app);
	if(nou == false)
		fout << "\n\n";

	fout << tip << "\n";
	fout << nume << "\n";
	fout << lux << "\n";
	fout << nr_camere << "\n";
	fout << nr_tipuri;

	for (auto it = camere_locuri.begin(); it != camere_locuri.end(); it++)
	{
		fout <<"\n"<< it->second << " - " << it->first;
	}

	for (auto it = list_pret.begin(); it != list_pret.end(); it++)
	{
		fout <<"\n" << it->first << " - " << it->second;
	}
	if (flag == 1)
	{
		fout <<"\n" << mese << "\n";
		fout << pret_mese;
	}
	fout.close();

	std::cout << "\nUnitatea de Cazare a fost adaugata cu succes!\n";

	Log& ref = Log::getInstance();
	ref.write(("Cazari_Adaugare: Administratorul a adaugat o noua unitate de cazare: " + nume + "\n"));
}


void CAdministrator::addCazari()
{
	string oras,tip,rasp,mese,nume;
	int lux, nr_camere, nr_tipuri, nr_camere_tipuri,nr_locuri,pret,pret_mese,flag = 0;
	char filename[256];
	std::map<int, int> list_pret;
	std::map<int, int> camere_locuri;
	bool nou = false;

	std::cout << "\nIntroduceti orasul: "; getline(std::cin, oras);
	if (oras == "")
		getline(std::cin, oras);
	string _oras = oras;
	oras += ".txt";
	FILE *f;
	strcpy(filename, oras.data());
	f = fopen(filename, "r");
	if (f == NULL)
	{
		std::ofstream fout(oras);
		fout << "";
		fout.close();
		std::ofstream f_out("Orase.txt",std::ios::app);
		f_out << "\n";
		f_out << _oras;
		f_out.close();
		nou = true;
	}

	std::cout << "Introduceti tipul cazarii (Hotel/Pensiune): "; std::cin >> tip;
	std::cout << "Introduceti numele: "; getline(std::cin,nume);
	if(nume=="")
		getline(std::cin, nume);
	if (tip == "Hotel")
		std::cout << "Introduceti numarul de stele: "; 
	else
		std::cout << "Introduceti numarul de margarete: "; 
	std::cin >> lux;

	std::cout << "Introduceti numarul de camere: "; std::cin >> nr_camere;
	std::cout << "Cate tipuri (in functie de numarul de locuri) de camere sunt: "; std::cin >> nr_tipuri;
	for (int i = 0; i < nr_tipuri; i++)
	{
		std::cout << "Numarul de camere: "; std::cin >> nr_camere_tipuri;
		std::cout << "Numarul de locuri: "; std::cin >> nr_locuri;
		camere_locuri.insert(std::pair<int, int>(nr_locuri, nr_camere_tipuri));
	}
	for (auto it = camere_locuri.begin(); it != camere_locuri.end(); it++)
	{
		std::cout << "Pretul pentru camerele cu " << it->first << " loc/locuri: "; std::cin >> pret;
		list_pret.insert(std::pair<int, int>(it->first, pret));
	}
	std::cout << "Exista mese: "; std::cin >> rasp;
	if (rasp == "DA" || rasp == "Da" || rasp == "da")
	{
		std::cout << "Introduceti mesele cu spatiu intre ele: "; getline(std::cin, mese);
		if(mese=="")
			getline(std::cin, mese);
		std::cout << "Introduceti pretul pt aceste optiuni: "; std::cin >> pret_mese;
		flag = 1;
	}
	adaugaCazareFisier(oras, tip, nume, lux, nr_camere, nr_tipuri, camere_locuri, list_pret, flag, mese, pret_mese,nou);
}

