#include "CazareList.h"
#include <fstream>
#include <string>

//CazareList& CazareList::getInstance()
//{
//    if (instance == nullptr)
//    {
//        instance = new CazareList();
//        return *instance;
//    }
//    return *instance;
//}

//void CazareList::destroy()
//{
//    if (instance != nullptr)
//        delete instance;
//}

//ICazare& CazareList::operator[](const int& index)
//{
//    if (index < vect.size())
//        return *vect[index];
//}
void CazareList::print()
{
	for (auto it = vect.begin(); it < vect.end(); it++)
		(*it)->afis();
}

void CazareList::ocupa(const int& data_1, const string& luna_1, const int& data_2, const string& luna_2)
{
	for (auto it = vect.begin(); it < vect.end(); it++)
		(*it)->OcupareCamere(data_1, luna_1, data_2, luna_2);
}

int CazareList::printDisponibile(std::vector<string> &cazari,const int& data_1, const string& luna_1, const int& data_2, const string& luna_2, const int& locuri, const int& nr_camere, const float& bonus)
{
	int flag = 0;
	for (auto it = vect.begin(); it < vect.end(); it++)
	{
		if ((*it)->verificaDisponibilitatea(nr_camere,locuri)==1)
		{
			float pret = (*it)->getPretRezervare(data_1, luna_1, data_2, luna_2, locuri, nr_camere);
			std::cout << (*it)->getNume() << "\n";
			pret = pret - (pret * (bonus / 100));
			std::cout << "Pret: " << pret << " RON" << "\n\n";
			flag = 1;
			cazari.push_back((*it)->getNume());
		}
	}
	if (flag == 0)
	{
		std::cout << "Nu este niciun loc de cazare disponibil\n";
		return 0;
	}
	return 1;
}

int CazareList::getCazare(const string& nume)
{
	for (int i = 0; i < vect.size(); i++)
		if (vect[i]->getNume() == nume)
			return i;
	return -1;
}

void CazareList::printRecenzii(const string& numeCazare)
{
	std::vector<string> recenzii;
	string nume, ren,spatiu;
	std::ifstream fin("Recenzii.txt");

	while (!fin.eof())
	{
		getline(fin, nume);
		getline(fin, ren);
		getline(fin,spatiu);
		if (nume == numeCazare)
			recenzii.push_back(ren);
	}
	if (recenzii.size() == 0)
		std::cout << "\nNu este nicio recenzie.\n\n";
	else
	{
		for (auto it = recenzii.begin(); it < recenzii.end(); it++)
			std::cout <<"* "<< (*it) << "\n";
	}
}

CazareList::~CazareList()
{
	for (auto it : vect)
	{
		delete it;
	}
}
