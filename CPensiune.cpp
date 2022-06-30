#include "CPensiune.h"

using std::cout;

CPensiune::CPensiune(const string& tip, const string& nume, const vector<Camera>& cam, const map<int, int>& preturi, const vector<string>& recenii, const int& marg, Optiuni& op)
	:CazareAbs(tip, nume, cam, preturi, recenzii, op), nrMargarete(marg)
{

}

void CPensiune::afis()
{
	cout << "\n";
	cout << nume << "\n";
	cout << "Pensiunea are " << nrMargarete << " margarete\n";
	printCamere();
	cout << "Pretul camerelor este: \n";
	for (auto it = preturi.begin(); it != preturi.end(); ++it)
		cout << "Pentru camere cu " << it->first << " pretul este: " << it->second << " RON\n";
	cout << "Optiunile pentru mese sunt:\n";
	printOptiuni();
	cout << "\n";
}
