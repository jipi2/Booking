#include "CClient.h"
#include "Rezervare.h"
#include <fstream>
#include <string>

int CClient::getBonusFidelitate()
{
	int bonus;

	switch (nr_rezervari)
	{
	case 0:
		bonus = 0;
		break;
	case 1:
		bonus = 2;
		break;
	case 3:
		bonus = 6;
		break;
	case 4:
		bonus = 10;
		break;
	case 5:
		bonus = 14;
		break;
	default:
		bonus = 18;
		break;
	}

	return bonus;
}

void CClient::rezerva(const int& data_1, const string& luna_1, const int& data_2, const string& luna_2, const int &locuri, const int &nr_camere, const string &nume_cazare)
{
	string nume_rez = (username + "_rez.txt");
	std::ofstream fout(nume_rez,std::ios::app);

	string rez = std::to_string(data_1);
	rez = rez + " " + luna_1 + " - ";
	rez = rez + std::to_string(data_2) + " ";
	rez = rez + luna_2 + " " + std::to_string(locuri) + " - " + std::to_string(nr_camere);
	string _rez_rezervari = rez;
	rez = rez + " - " + nume_cazare;
	rez = rez+" in asteptare" + "\n";

	fout.write(rez.data(), rez.length());
	fout.close();
	nr_rezervari++;

	std::ofstream f_out("Rezervari.txt",std::ios::app);
	_rez_rezervari = username +" : " + _rez_rezervari+" - "+nume_cazare+"\n";
	f_out.write(_rez_rezervari.data(), _rez_rezervari.length());
	f_out.close();

	Log& ref = Log::getInstance();
	ref.write(("Rezervare: Utilizatorul " + username + " a realizat o rezervare\n"));
}

int CClient::verificaRezervare(const int& data_1, const string& luna_1, const int& data_2, const string& luna_2, const int& locuri, const int& nr_camere, const string& nume_cazare)
{
	string rez = std::to_string(data_1);
	rez = rez + " " + luna_1 + " - ";
	rez = rez + std::to_string(data_2) + " ";
	rez = rez + luna_2 + " " + std::to_string(locuri) + " - " + std::to_string(nr_camere)+" - "+nume_cazare;

	string fileName = username + "_rez.txt";

	FILE *f;

	char file[256];
	strcpy(file, fileName.data());
	f = fopen(file, "r");

	if (f == NULL)
	{
		return 1;                               
	}                             
	else
	{
		fclose(f);
		std::ifstream fin;
		string rezervare;
		string delim = nume_cazare;

		fin.open(file);
		while (!fin.eof())
		{
			getline(fin, rezervare);
			rezervare = rezervare.substr(0, rezervare.find(delim) + delim.length());

			if (rezervare == rez)
			{
				fin.close();
				throw Rezervare("Aceasta rezervare exista deja!\n");
			}
		}
	}
	return 1;
}

void CClient::updateNrRezervari()
{
	std::ifstream fin((username + "_rez.txt"));
	string linie;

	while (getline(fin, linie))
	{
		if (linie.find("aprobat") != string::npos)
			nr_rezervari++;
	}
	fin.close();
}

void CClient::scrieRecenzie()
{
	string oras,nume,linie;
	string recenzie;
	bool flag = 0;

	std::cout << "Introduceti orasul: ";  std::cin >> oras;
	FILE* f = fopen((oras + ".txt").data(),"r");
	if (f == NULL)
	{
		std::cout << "Nu avem nicio unitate de cazare in acest oras\n";
		return;
	}
	std::cout << "Introduceti numele unitatii de cazare: "; getline(std::cin, nume);
	getline(std::cin, nume);
	std::ifstream fin((username + "_rez.txt"));
	while (getline(fin, linie))
	{
		if (linie.find(nume) != string::npos)
		{
			if (linie.find("aprobat") != string::npos)
				flag = 1;
		}
	}
	fin.close();
	if (flag == 0)
	{
		std::cout << "Nu puteti scrie o recenzie deoarece nu aveti nicio rezervare aprobata la aceasta unitate de cazare\n";
		return;
	}
	std::cout << "Scrieti receznia dumneavoastra urmata de tasta 'Enter'\n";
	getline(std::cin, recenzie);

	std::ofstream fout("Recenzii.txt",std::ios::app);
	fout << nume << "\n";
	fout << recenzie<<"\n\n";
}

void CClient::afisIstoricCazari()
{
	FILE* f = fopen((username + "_rez.txt").data(), "r");
	if (f == NULL)
	{
		std::cout << "\nNu aveti nicio rezervare efectuata\n\n";
		return;
	}
	fclose(f);
	
	std::ifstream fin((username + "_rez.txt"));
	string rez;

	std::cout << "\n";
	while (!fin.eof())
	{
		getline(fin, rez);
		std::cout << rez << "\n";
	}
	std::cout << "\n";
	fin.close();
}
