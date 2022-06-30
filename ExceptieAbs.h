#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "IExceptie.h"

class ExceptieAbs :public IExceptie
{
protected:
	std::string mesaj;
public:
	ExceptieAbs(const std::string &msj):mesaj(msj){}
	virtual std::string getMesaj() override { return mesaj; }
};
