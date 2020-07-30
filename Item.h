#pragma once
#include <string>

class Item
{
public:

	std::string name;
	float Price;
	int Quantity;
	

	Item(std::string strName, float fPrice, int iQuantity)
		: name(strName), Price(fPrice), Quantity(iQuantity)
	{

	}

	~Item()
	{

	}
};

