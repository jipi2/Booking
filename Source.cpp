#include "CClientList.h"
#include "CAdministrator.h"
#include "CazareList.h"
#include "CazariFactory.h"
#include "IExceptie.h"
#include <string>
#include <conio.h>

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::ifstream;

CAdministrator* CAdministrator::instance = nullptr;
CazareList* CazareList::instance = nullptr;
CClientList* CClientList::instance = nullptr;

int logare();
void prelucrareClient(const int& index);

bool verificareOras(const string& oras)
{
	std::ifstream fin("Orase.txt");
	string _oras;
	while (!fin.eof())
	{
		getline(fin, _oras);
		if (_oras == oras)
		{
			fin.close();
			return true;
		}
	}
	fin.close();
	return false;
}

string hide()
{
	char parola[256];
	int i = 0;
	char c = 'c';

	while (c != 0xD)
	{
		if (i > 255)
			break;
		c = _getch();
		if (c != 0xD && c!=0x8)
		{		
			parola[i++] = c;
			cout << "*";
		}
		if (c == 0x8)
		{
			if (i > 0)
			{
				i--;
				printf("\b \b");
			}
		}
		else if(c == 0xD)
		{
			cout << "\n";
		}
	}

	parola[i] = '\0';
	string pass_str = parola;
	return pass_str;
}

int logareAdministrator(const string& nume, const string& pass)
{
	CAdministrator& adm = CAdministrator::getInstance();

	if (adm.getUsername() == nume && adm.getPass() == pass)
	{
		Log& ref = Log::getInstance();
		ref.write(("Logare_Admin: Administratorul s-a logat cu succes\n"));

		return 1;
	}
	return 0;
}

void adminPrelucrare()
{
	system("CLS");

	CAdministrator& adm = CAdministrator::getInstance();
	string rasp;

	cout << "Buna ziua domnule administrator\n";
	adm.prelucreazaRezervari();
	cout << "Doriti sa adaugati o unitate de cazare?\n";
	cout << "Puteti raspunde cu DA sau NU: "; cin >> rasp;
	
	if (rasp == "DA" || rasp == "Da" || rasp == "da")
	{
		try 
		{
			adm.addCazari();
		}
		catch (IExceptie& e)
		{
			cout << e.getMesaj();
			e.semnaleazaExceptie("");
			e.rezolvaExceptie();
		}
	}
	else
		cout << "Va multumim pentru mentenanta!\n";
}

vector<string> citesteOrase()
{
	vector<string> orase;
	string _oras;
	ifstream fin;
	fin.open("Orase.txt");

	while (!fin.eof())
	{
		getline(fin, _oras);
		if(_oras!="")
			orase.push_back(_oras);
	}
	fin.close();
	return orase;
}

void afisOrase(vector<string>& orase)
{
	for (auto it = orase.begin(); it < orase.end(); it++)
		cout << *it << "\n";
}

int verificaCazareIntrodusa(string& cazare, vector<string>& cazari_disp)
{
	for (auto it = cazari_disp.begin(); it < cazari_disp.end(); it++)
		if ((*it) == cazare)
			return 1;
	return 0;
}

void rezerva(CazareList& cazari, CClient& client)
{
	CClientList& clienti = CClientList::getInstance();
	int flag = 1, data_1, data_2,locuri, nr_camere;
	string luna_1, luna_2,aux,nume_cazare;
	Calendar cal;
	vector<string> cazari_disp; //cazarile disponibile

	cout << "Va rog, completati: \n";
	cout << "Data de la care vreti sa va cazati (prima litera a lunii va fi majuscula), exemplu: '23 Decembrie'\n";
	cout << "Data: "; cin>>data_1>>luna_1;
	cout << "Data pana la care vreti sa va cazati (prima litera a lunii va fi majuscula), exemplu: '25 Decembrie'\n";
	cout << "Data: "; cin >> data_2 >> luna_2;

	while (cal.addData(data_1, luna_1, data_2, luna_2) == 0)
	{
		cout << "Data incorecta, incercati din nou\n";

		cout << "Data de la care vreti sa va cazati (prima litera a lunii va fi majuscula), exemplu: '23 Decembrie'\n";
		cout << "Data: "; cin >> data_1 >> luna_1;
		cout << "Data de la care vreti sa va cazati (prima litera a lunii va fi majuscula), exemplu: '25 Decembrie'\n";
		cout << "Data: "; cin >> data_2 >> luna_2;
	}

	cout << "Cate camere: "; cin >> nr_camere;
	cout << "Cate locuri/camera: "; cin >> locuri; getline(cin,aux);

	cazari.ocupa(data_1, luna_1, data_2, luna_2);

	cout << "Cazarile disponibile sunt (pretul include si reducerea datorata bonusului de fidelitate, daca acesta exista):\n\n";

	if(cazari.printDisponibile(cazari_disp,data_1, luna_1, data_2, luna_2,locuri,nr_camere, (float)client.getBonusFidelitate()) == 0)
	{
		cout << "Va mai asteptam in alta perioada\n";
		return;
	}
	else
	{
		try 
		{
			cout << "Introduceti numele hotelului/pensiunii unde doriti sa faceti rezervarea(sau apasati tasat 3 daca nu doriti sa faceti nicio rezervare): "; getline(cin, nume_cazare);
			if (nume_cazare == "3")
				return;
			while (verificaCazareIntrodusa(nume_cazare, cazari_disp) == 0)
			{
				cout << "Numele introdus nu este corect, introduceti din nou: "; getline(cin, nume_cazare);
				if (nume_cazare == "3")
					return;
			}
			if (client.verificaRezervare(data_1, luna_1, data_2, luna_2, locuri, nr_camere, nume_cazare) == 1)
			{
				client.rezerva(data_1, luna_1, data_2, luna_2, locuri, nr_camere, nume_cazare);
				cazari[cazari.getCazare(nume_cazare)].appendRezervare(data_1, luna_1, data_2, luna_2, locuri, nr_camere);

				cout << "\nCererea de rezervare se afla in asteptare, va multumim!\n";
			}
		}
		catch (IExceptie& e)
		{
			cout <<"\n"<< e.getMesaj();
			e.rezolvaExceptie();
			e.semnaleazaExceptie(client.getUsername());
			cout << "\n\nApasati orice tasta";
			_getch();
			prelucrareClient(clienti.existaClient(client.getUsername(), client.getPass()));
		}
	}
}

void prelucrareClient(const int& index)
{
	system("CLS");

	string _oras;

	CClientList& clienti = CClientList::getInstance();
	clienti[index].updateNrRezervari();
	cout << "Utilizatorul " << clienti[index].getUsername() << " s-a logat cu succes!\n\n";

	Log& ref = Log::getInstance();
	ref.write(("Logare: Utilizatorul " + clienti[index].getUsername() + " s-a logat cu succes\n"));

	vector<string> orase = citesteOrase();

	cout << "Avem cazari disponibile in orasele:\n\n";
	afisOrase(orase);

	cout << "\nOrasul dorit: "; getline(cin, _oras);
	getline(cin, _oras);

	while (verificareOras(_oras) == false)
	{
		cout << "Ati introdus un oras care nu este pe lista, va rog introduceti unul din lista!\n";
		cout << "\nOrasul dorit: "; getline(cin, _oras);
	}

	_oras += ".txt";
	CazareList& cazari = CazareList::getInstance();
	cazari.addVector(CazariFactory::getCazari(_oras.data()));

	cout << "\nDoriti sa vedeti toate cazarile din acest oras?\n"; cout << "Puteti raspunde cu DA sau NU: ";
	string rasp;
	cin >> rasp;

	if(rasp == "DA"||rasp == "Da"||rasp == "da")
		cazari.print();

	cout << "\nDoriti sa vedeti recenzii despre o anumita unitate de cazare?\n";
	cout << "Puteti raspunde cu DA sau NU: ";
	cin >> rasp;
	if (rasp == "DA" || rasp == "Da" || rasp == "da")
	{
		string unitCazare;
		cout << "Introduceti numele unitatii de cazare: "; getline(cin, unitCazare);
		getline(cin, unitCazare);
		cazari.printRecenzii(unitCazare);
	}

	cout << "\nDoriti sa faceti o rezervare?\n" << "Puteti raspunde cu DA sau NU: "; cin >> rasp;
	if (rasp == "DA" || rasp == "Da" || rasp == "da")
		rezerva(cazari, clienti[index]);
	
	cout << "\nDoriti sa scrieti o recenzie?\n";
	cout << "Puteti raspunde cu DA sau NU: "; cin >> rasp;
	if (rasp == "DA" || rasp == "Da" || rasp == "da")
		clienti[index].scrieRecenzie();

	cout << "\nDoriti sa vedeti istoricul rezervarilor dumneavoastra?\n";
	cout << "Puteti raspunde cu DA sau NU: "; cin >> rasp;
	if (rasp == "DA" || rasp == "Da" || rasp == "da")
		clienti[index].afisIstoricCazari();

	cout << "\nVa multumim si va mai asteptam!\n";
	cout << "\n\nApasati orice tasta pentru a inchide consola.\n\n";

	cazari.destroy();

	_getch();
}

void inregistrareClient()
{
	system("CLS");

	CClientList& clienti = CClientList::getInstance();
	string userName, pass;

	cout << "Introduceti un username si o parola pentru a va putea conecta ulterior: \n";
	cout << "!!FOARTE IMPORTANT!! NUMELE SI PAROLA NU TREBUIE SA CONTINA SPATII PENTRU CA SE VOR LUA IN CONSIDERARE DOAR CARACTERELE TASTATE PANA LA SPATIU\n\n";

	cout << "Username: "; cin >> userName;
	cout << "Password: "; pass = hide();

	while (clienti.existaNumeClient(userName) != -1 || logareAdministrator(userName,pass) == 1)
	{
		cout << "Acest Username exista deja, va rog introduceti altul\n";
		cout << "Username: "; cin >> userName;
	}

	cout << "Utilizatorul cu username-ul: " << userName << " s-a inregistrat cu succes\n";
	cout << "Va vom redirectiona la pagina principala\n\n\n";

	CClient c(userName, pass);

	clienti.add(c);
	clienti.updateFisier();

	Log& ref = Log::getInstance();
	ref.write(("Inregistrare: Utilizatorul " + userName + " s-a inregistrat cu succes\n"));

	logare();
}

int logare()
{
	system("CLS");
	CClientList& clienti = CClientList::getInstance();
	string userName, pass;
	int index_client;

	int connect;

	cout << "Buna ziua si bine ati venit pe site-ul nostru\n";
	cout << "Pentru a va conecta, apasati '1', pentru a va inregistra, apasati '2': ";

	cin >> connect;

	if (connect == 1) 
	{
		cout << "Username: "; cin >> userName;
		cout << "Password: "; pass = hide();

		if (logareAdministrator(userName, pass) == 1)
			adminPrelucrare();
		else
		{
			try 
			{
				index_client = clienti.existaClient(userName, pass);
			}
			catch (IExceptie& e)
			{
				cout << "\n" << e.getMesaj();
				e.semnaleazaExceptie(userName);
				if (e.rezolvaExceptie() == 1)
					return 1;
				return 0;
			}
			prelucrareClient(index_client);
		}
	}
	else if (connect == 2)
	{
		inregistrareClient();
	}
	else
	{
		cout << "\n\nNu ati apasat nici 1, nici 2";
		cout << "\n\nVa mai asteptam!\n\n";
	}

	return 0;
}

int main()
{
	int cont;
	cont = logare();
	while (cont == 1)
		cont = logare();

	return 0;
}
