#include "CClientList.h"
#include "Alerta.h"

//void CClientList::destory()
//{
//	CClientList::instance->updateFisier();
//	if (CClientList::instance != nullptr)
//		delete instance;
//}

//void CClientList::print()
//{
//	for (auto it = vect.begin(); it < vect.end(); it++)
//		std::cout << *it << "\n";
//}

//void CClientList::updateFisier()
//{
//	if (CClientList::instance == nullptr)
//		return;
//
//	std::ofstream fout;
//	fout.open("clienti.txt");
//
//	for (auto it = vect.begin(); it < vect.end()-1; it++)
//	{
//		fout <<it->getUsername()<<"\n";
//		fout <<it->getPass()<< "\n\n";
//	}
//	fout << (vect.end() - 1)->getUsername() << "\n";
//	fout << (vect.end() - 1)->getPass();
//	fout.close();
//}

CClient& CClientList::operator[](const int& index)
{
    if (index < vect.size())
        return vect[index];
}

int CClientList::existaClient(const string& nume, const string& pass)
{

    for(int i = 0;i<vect.size();i++)
        if (vect[i].getPass() == pass && vect[i].getUsername() == nume)
        {
            vect[i].updateNrRezervari();
            return i;
        }

    throw Alerta("Conectarea nu a reusit!\n");
    return -1;
}

int CClientList::existaNumeClient(const string& nume)
{
    for (int i = 0; i < vect.size(); i++)
        if (vect[i].getUsername() == nume)
        {
            return i;
        }

    return -1;
}
