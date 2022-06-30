#include "Alerta.h"

int Alerta::rezolvaExceptie()
{
	std::cout << "Pentru a incerca sa va conectati sau inregistrati din nou, apasati tasta 1\n";
	std::cout << "Pentru a iesi, apasati tasta 2\n";
	std::cout << "Tasta: ";
	std::string tasta;
	std::cin >> tasta;
	if (tasta == "1")
		return 1;
	return 0;
}

void Alerta::semnaleazaExceptie(const std::string& nume)
{
	Log& ref = Log::getInstance();
	ref.write(("Alerta: Conectare esuata, username utilizator: " + nume + "\n"));
}
