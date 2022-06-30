#include "CazariFactory.h"
#include "CHotel.h"
#include "CPensiune.h"
#include <fstream>
#include <sstream>
#include <map>


using std::string;

Optiuni getOp(string& mese)
{
	Optiuni op;

	op.cina = 0; op.pranz = 0; op.micDeJun = 0;

	if (mese == "")
	{
		op.cina = 0;
		op.micDeJun = 0;
		op.pranz = 0;

		return op;
	}

	string word;
	string delim = " ";
	int pos,ok=0;
	pos = mese.find(delim);

	while (pos != string::npos && mese!="")
	{
		ok = 1;
		word = mese.substr(0, pos);
		if (word == "Cina") 
			op.cina = 1;
		if (word == "Pranz") 
			op.pranz = 1;
		if (word == "MicDejun") 
			op.micDeJun = 1;

		mese.erase(0, pos + delim.length());
		pos = mese.find(delim);
	}

	if (mese == "Cina") 
		op.cina = 1;
	if (mese == "Pranz") 
		op.pranz = 1;
	if (mese == "MicDejun") 
		op.micDeJun = 1;
	
	return op;
}

std::vector<ICazare*> CazariFactory::getCazari(const char* filename)
{
	std::vector<string> ren;
	std::vector<ICazare*> vect;
	
	Camera c;
	Optiuni op;

	string nume;
	char num[60];
	string tip;
	int lux; //stele sau margarete
	int tip_camera;
	string liniuta;
	int nr_camera, locuri;
	int pret;
	string mese;
	int pret_optiune;

	std::ifstream fin;
	fin.open(filename);

	while (!fin.eof())
	{
		pret_optiune = 0;
		int k = 0;
		std::map<int, int> list_pret;
		fin >> tip;
		getline(fin, nume);
		getline(fin, nume);
		fin >> lux;
		fin >> nr_camera;
		std::vector<Camera> cam(nr_camera);
		fin >> tip_camera;

		for (int i = 0; i < tip_camera; i++)
		{
			fin >> nr_camera;
			fin >> liniuta;
			fin >> locuri;

			c.locuri = locuri;
			c.ocupat = 0;

			for (int j = 0; j < nr_camera; j++)
				cam[k++] = c;
			
		}
		for (int i = 0; i < tip_camera; i++)
		{
			fin >> locuri;
			fin >> liniuta;
			fin >> pret;
			list_pret.insert(std::pair<int,int>(locuri, pret));
		}

		getline(fin, mese);
		getline(fin, mese);

		if (mese != "")
			fin >> pret_optiune;

		op = getOp(mese);
		mese = "";
		op.pret = pret_optiune;

		if (tip == "Hotel")
		{
			ICazare* ptr = new CHotel(tip, nume, cam, list_pret, ren, lux,op);
			vect.push_back(ptr);
		}
		else 
		{
			ICazare* ptr = new CPensiune(tip, nume, cam, list_pret, ren, lux,op);
			vect.push_back(ptr);
		}
	}
	fin.close();
	return vect;
}
