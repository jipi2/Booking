#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "CazareAbs.h"
#include <string>



class CHotel :public CazareAbs
{
private:
	int nrStele = 0;
public:
	CHotel(const string& tip, const string& nume, const vector<Camera>& cam, const map<int, int>& preturi, const vector<string>& recenii, const int& stele, Optiuni& op);

	virtual int getLux() override { return nrStele; }
	virtual void afis()override;

	~CHotel() {}
};

