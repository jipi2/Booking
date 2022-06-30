#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "ExceptieAbs.h"

class Eroare :public ExceptieAbs
{
public:
	Eroare(const std::string& msj) :ExceptieAbs(msj) {}
	virtual int rezolvaExceptie()override;
	virtual void semnaleazaExceptie(const std::string& nume)override;
};

