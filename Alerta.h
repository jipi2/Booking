#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "ExceptieAbs.h"

class Alerta : public ExceptieAbs
{
public:
	Alerta(const std::string &msj):ExceptieAbs(msj){}
	virtual int rezolvaExceptie()override;
	virtual void semnaleazaExceptie(const std::string& nume) override;
};

