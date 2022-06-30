#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include "Log.h"

class IExceptie
{
public:
	virtual std::string getMesaj() = 0;
	virtual int rezolvaExceptie() = 0;
	virtual void semnaleazaExceptie(const std::string &nume) = 0;
};
