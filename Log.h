#define _CRT_SECURE_NO_WARNINS
#pragma once
#include <iostream>

class Log
{
private:
	static Log* instance;

	Log() {}
	Log(const Log& obj) {}

	void destroy();
public:
	static Log& getInstance();
	
	void write(const std::string& text);

	~Log() { destroy(); }
};
