#include "Eroare.h"

int Eroare::rezolvaExceptie()
{
	exit(-100);
	return 0;
}

void Eroare::semnaleazaExceptie(const std::string& nume)
{
	Log& ref = Log::getInstance();
	ref.write(mesaj);
}
