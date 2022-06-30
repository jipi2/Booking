#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "ICazare.h"
#include <vector>

class CazariFactory
{
public:
	static std::vector<ICazare*> getCazari(const char* filename);
};

