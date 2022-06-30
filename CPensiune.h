#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "CazareAbs.h"

class CPensiune : public CazareAbs
{
private:
	int nrMargarete = 0;
public:
	CPensiune(const string& tip, const string& nume, const vector<Camera>& cam, const map<int, int>& preturi, const vector<string>& recenii, const int& marg, Optiuni& op);
	virtual void afis() override;

	virtual int getLux() override { return nrMargarete; }

	~CPensiune() {}
};

