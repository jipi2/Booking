#include "Calendar.h"

int Calendar::getMonthIndex(const string& luna)
{
	for (int i = 0; i < 12; i++)
		if (str_months[i] == luna)
			return i;
	return -1;
}

int Calendar::getDiferntaLuni(const string& luna_1, const string& luna_2)
{
	int nr = 0;
	int i = getMonthIndex(luna_1);
	for (int j = i; j < 12; j++)
	{
		if (str_months[j] == luna_2)
			break;
		else
			nr++;
	}
	return nr;
}

Months identificaLuna(const string& luna)
{
	if (luna == "Ianuarie")
		return Ianuarie;
	if (luna == "Februarie")
		return Februarie;
	if (luna == "Martie")
		return Martie;
	if (luna == "Aprilie")
		return Aprilie;
	if (luna == "Mai")
		return Mai;
	if (luna == "Iunie")
		return Iunie;
	if (luna == "Iulie")
		return Iulie;
	if (luna == "August")
		return August;
	if (luna == "Septembrie")
		return Septembrie;
	if (luna == "Octombrie")
		return Octombrie;
	if (luna == "Noiembrie")
		return Noiembrie;
	if (luna == "Decembrie")
		return Decembrie;
}

string getLunaString(Months luna)
{
	if (luna == Ianuarie)
		return "Ianuarie";
	if (luna == Februarie)
		return "Februarie";
	if (luna == Martie)
		return "Martie";
	if (luna == Aprilie)
		return "Aprilie";
	if (luna == Mai)
		return "Mai";
	if (luna == Iunie)
		return "Iunie";
	if (luna == Iulie)
		return "Iulie";
	if (luna == August)
		return "August";
	if (luna == Septembrie)
		return "Septembrie";
	if (luna == Octombrie)
		return "Octombrie";
	if (luna == Noiembrie)
		return "Noiembrie";
	if (luna == Decembrie)
		return "Decembrie";

}

bool verificaData(const int& zi_1, const string& luna_1, const int& zi_2, const string& luna_2, Calendar &obj)
{
	if (obj.getMonthIndex(luna_1) == -1)
		return 0;
	if (obj.getMonthIndex(luna_2) == -1)
		return 0;

	if (obj.getMonthIndex(luna_2) < obj.getMonthIndex(luna_1))
		return 0;

	if (zi_1 > identificaLuna(luna_1))
		return 0;
	if (zi_2 > identificaLuna(luna_2))
		return 0;

	if (luna_1 == luna_2 && zi_1 >= zi_2)
		return 0;

	return 1;
}

int Calendar::addData(const int& zi_1, const string& luna_1, const int& zi_2, const string& luna_2)
{
	if (verificaData(zi_1, luna_1, zi_2, luna_2, *(this)) == 0)
		return 0;

	zi_inceput = zi_1;
	luna_inceput = identificaLuna(luna_1);

	zi_final = zi_2;
	luna_final = identificaLuna(luna_2);

	return 1;
}
