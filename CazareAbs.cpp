#include "CazareAbs.h"
#include <fstream>
#include <string>

CazareAbs::CazareAbs(const string& tip, const string& nume, const vector<Camera>& cam, const map<int, int>& preturi, const vector<string>& recen, Optiuni& op)
{
	this->tip = tip;
	this->nume = nume;
	this->camere = cam;
	this->preturi = preturi;
	this->recenzii = recen;
	this->opt = op;

	const char* filename;
	string nume_rez;
	
	nume_rez = nume + "_rez.txt";

	filename = nume_rez.c_str();

	FILE* f;
	f = fopen(filename,"r");

	if (f == NULL)
	{
		std::ofstream fout(nume_rez);
		fout << "Rezervari:";
	}
	else
		fclose(f);
	
}

void CazareAbs::addOptiuni(bool mic, bool cin, bool pran)
{
	opt.micDeJun = mic;
	opt.pranz = pran;
	opt.cina = cin;
}

void CazareAbs::printOptiuni()
{
	if (opt.micDeJun == 1 && opt.pranz == 1 && opt.cina == 1)
		std::cout << "Mic dejun + Prans + Cina - ";
	else if (opt.micDeJun == 1 && opt.pranz == 1)
		std::cout << "Mic dejun + Pranz -  ";
	else if (opt.micDeJun == 1 && opt.cina == 1)
		std::cout << "Mic dejun + Cina - ";
	else if (opt.pranz == 1 && opt.cina == 1)
		std::cout << "Pranz + Cina - ";
	else if (opt.micDeJun == 1)
		std::cout << "Mic dejun - ";
	else if (opt.cina == 1)
		std::cout << "Cina - ";
	else if (opt.pranz == 1)
		std::cout << "Pranz - ";
	else
	{
		std::cout << "Nu aveti nicio masa\n";
		return;
	}
	std::cout << opt.pret << " RON\n";

}

void CazareAbs::printRecenzii()
{
	for (auto it = recenzii.begin(); it < recenzii.end(); it++)
		std::cout << (*it) << "\n";
}

void CazareAbs::printCamere()
{
	int nr_locuri = 0;
	int nr_camere = 0;

	vector<Camera>::iterator it;
	it = camere.begin();

	nr_locuri = it->locuri;
	nr_camere++;
	it++;

	for (; it < camere.end(); it++)
	{
		if (nr_locuri != it->locuri)
		{
			std::cout <<"Sunt " << nr_camere <<" camere " << " cu " << nr_locuri << " locuri\n";
			nr_camere = 0;
			nr_locuri = it->locuri;
		}
		nr_camere++;
	}
	std::cout << "Sunt " << nr_camere << " camere " << " cu " << nr_locuri << " locuri\n";
}

int CazareAbs::verificaDisponibilitatea(const int& nr_camere, const int& locuri_camere)
{
	int nr = 0;

	for (auto it = camere.begin(); it < camere.end(); it++)
	{
		if (it->locuri == locuri_camere && it->ocupat == 0)
			nr++;
	}

	if (nr >= nr_camere)
		return 1;
	else
		return 0;
}

void ocupa(const int& locuri,int& nr_camere, CazareAbs& obj)
{
	
	for (auto it = obj.camere.begin(); it < obj.camere.end(); it++)
	{
		if (nr_camere == 0)
			break;
		if (locuri == it->locuri && it->ocupat == 0)
		{
			it->ocupat = 1;
			nr_camere--;
		}
	}
}

void CazareAbs::OcupareCamere(const int& data_1, const string& luna_1, const int& data_2, const string& luna_2)
{
	string fisier_rezervari = nume + "_rez.txt";
	std::ifstream fin(fisier_rezervari);

	int d_1, d_2,locuri, nr_camere;
	string l_1, l_2, liniuta;
	Calendar cal;

	fin >> liniuta;
	while (!fin.eof())
	{
		fin >> d_1 >> l_1 >> liniuta >> d_2 >> l_2 >> locuri >> liniuta >> nr_camere;
		
		if (luna_1 == luna_2 && l_1 == l_2 && luna_1 == l_1 && luna_2 == l_2)
		{
			if ((data_2 > d_1 && data_1 > d_1) || (data_1 > d_1 && data_2 < d_2) || (data_1<d_2 && data_2>d_2))
				ocupa(locuri, nr_camere, *this);
		}
		else if (luna_1 == l_1 || luna_2 == l_2 || luna_1 == l_2 || luna_2 == l_1)
		{
			if (luna_1 == l_1 && luna_2 != l_2)
			{
				if (!(luna_2 == l_1 && data_2 < d_1))
					ocupa(locuri, nr_camere, *this);
			}
			else if (luna_2 == l_2)
			{
				if (!(luna_1 == l_2 && data_1 > d_2))
					ocupa(locuri, nr_camere, *this);
			}
		}
		else if (!(cal.getMonthIndex(luna_2) < cal.getMonthIndex(l_1) || cal.getMonthIndex(luna_1) > cal.getMonthIndex(l_2)))
		{
			if (cal.getMonthIndex(luna_1) < cal.getMonthIndex(l_1) && cal.getMonthIndex(luna_2) > cal.getMonthIndex(l_2))
				ocupa(locuri, nr_camere, *this);
			else if (cal.getMonthIndex(l_1) > cal.getMonthIndex(luna_1) && cal.getMonthIndex(l_2) > cal.getMonthIndex(luna_2))
				ocupa(locuri, nr_camere, *this);
			else if(cal.getMonthIndex(luna_2)>cal.getMonthIndex(l_1) && cal.getMonthIndex(luna_2)<cal.getMonthIndex(l_2))
				ocupa(locuri, nr_camere, *this);
			else if(cal.getMonthIndex(luna_1)>cal.getMonthIndex(l_1) && cal.getMonthIndex(luna_1)<cal.getMonthIndex(l_2))
				ocupa(locuri, nr_camere, *this);
		}
	}
}

void CazareAbs::appendRezervare(const int& zi_1, const std::string& luna_1, const int& zi_2, const std::string& luna_2, const int& loc, const int& nr_camere)
{
	string rez;
	rez = "\n" + std::to_string(zi_1) + " " + luna_1 + " - " + std::to_string(zi_2) + " " + luna_2 + " " + std::to_string(loc) + " - " + std::to_string(nr_camere);
	std::ofstream fout(nume + "_rez.txt", std::ios::app);
	fout.write(rez.data(), rez.length());
	fout.close();
}

int getZileWeekend(const int &zi_1, const int &zi_2, const string &luna_1,Calendar &cal)
{
	int index = cal.getMonthIndex(luna_1);

	int weekend = 0;
	int zi = cal.firstDay[index];

	for (int i = 0; i < zi_1; i++)
	{
		if (zi > 7)
			zi = zi % 7;
		zi++;
	}

	for (int i = zi_1; i < zi_2; i++)
	{
		if (zi > 7)
			zi = zi % 7;
		if (zi == 6 || zi == 7)
			weekend++;
		zi++;
	}
	return weekend;
}

float CazareAbs::getPretRezervare(const int& zi_1, const std::string& luna_1, const int& zi_2, const string& luna_2, const int& loc, const int& nr_camere)
{
	Calendar cal;

	int pret_zi,dif;

	if (cal.addData(zi_1, luna_1, zi_2, luna_2) == 0)  //aici trebuie verificat ce se face daca data nu e buna
		return 0.0;

	int flag = 0;
	for (auto it = preturi.begin(); it != preturi.end(); it++)
		if (it->first == loc)
		{
			pret_zi = it->second;
			flag = 1;
		}
	if (flag == 0) return 0.0;
	pret_zi += opt.pret;
	pret_zi =pret_zi* nr_camere;

	float procent = 0.25;
	float weekend_fee = procent * (float)pret_zi;
	float pret_total;

	if (luna_1 == luna_2)
	{
		int weekend = getZileWeekend(zi_1, zi_2, luna_1, cal);
		if (weekend)
			pret_total = (float)(((weekend_fee + pret_zi) * weekend) + (pret_zi * (zi_2 - zi_1 - weekend)));
		else
			pret_total = (float)(((pret_zi) * (zi_2 - zi_1)));
	}
	else
	{
		int zile_luna_1 = cal.luna_inceput - zi_1;
		int weekend_luna_1 = getZileWeekend(zi_1, cal.luna_inceput, luna_1, cal);
		int weekend_luna_2;
		weekend_luna_2 = getZileWeekend(0, zi_2, luna_2, cal);
		//weekend_luna_2 = getZileWeekend(1, zi_2, luna_2, cal);

		
		if (weekend_luna_1 || weekend_luna_2)
		{
			pret_total = (float)(((weekend_fee + pret_zi) * (weekend_luna_1+weekend_luna_2)));
			pret_total += (float)(pret_zi * ((zile_luna_1 + zi_2) - (weekend_luna_1 + weekend_luna_2)));
		}
		else
			pret_total = (float)(((pret_zi) * (zile_luna_1 + zi_2)));
		
		dif = cal.getDiferntaLuni(luna_1, luna_2);
		if (dif > 1)
		{
			for (int j = 0; j < dif - 1; j++)
			{
				pret_total += (float)(weekend_fee + pret_zi) * 8;
				pret_total += (float)(pret_zi * 22);
			}
		}
	}

	return pret_total;
}
