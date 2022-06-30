#include "CHotel.h"
#include <fstream>

using std::cout;

CHotel::CHotel(const string& tip, const string& nume, const vector<Camera>& cam, const map<int, int>& preturi, const vector<string>& recenii, const int& stele, Optiuni& op)
	:CazareAbs(tip, nume, cam, preturi, recenzii, op), nrStele(stele)
{
	
}

void CHotel::afis()
{
	cout << "\n";
	cout << nume<<"\n";
	cout << "hotelul are " << nrStele << " stele\n";
	printCamere();
	cout << "Pretul camerelor este: \n";
	for (auto it = preturi.begin(); it != preturi.end(); ++it)
		cout << "Pentru camere cu " << it->first << " locuri pretul este: " << it->second << " RON\n";
	cout << "Optiunile pentru mese sunt:\n";
	printOptiuni();
	cout << "\n";
}
