#include "Log.h"
#include <fstream>

Log* Log::instance = nullptr;
Log& Log::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Log();
		return *instance;
	}
	return *instance;
}

void Log::destroy()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void Log::write(const std::string& text)
{
	std::ofstream fout("Registru.log", std::ios::app);
	fout << text;
	fout.close();
}
