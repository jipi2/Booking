#define _CRT_SECURE_NO_WARINGS
#pragma once
#include "ExceptieAbs.h"

class Rezervare :public ExceptieAbs
{
public:
	Rezervare(const std::string& msj) :ExceptieAbs(msj) {}
	virtual int rezolvaExceptie();
	virtual void semnaleazaExceptie(const std::string& nume);
};

