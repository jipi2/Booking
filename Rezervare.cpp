#include "Rezervare.h"

int Rezervare::rezolvaExceptie()
{
	std::cout << "Va vom redirectiona la pagina unde s-a realizat identificarea utilizatorului\n";
	return 1;
}

void Rezervare::semnaleazaExceptie(const std::string& nume)
{
	Log& ref = Log::getInstance();
	ref.write(("Eroare_Rezervare: Utilizatorul " + nume + " a incercat sa faca aceeasi rezervare de 2 ori\n"));
}
