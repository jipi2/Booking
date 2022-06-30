#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>

using std::string;

class Utilizator
{
protected:
	string username;
	string pass;
public:
	Utilizator(const string &name, const string &par):username(name), pass(par){}

	string getUsername() { return username; }
	string getPass() { return pass; }

	virtual ~Utilizator() {}
};
