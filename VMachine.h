#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <future>
#include "Item.h"

enum operations { INSERT, BUY, RETURN, SERVICE, PASSWORD, ADD, REMOVE, EXIT };
enum currency { POUND, TWOPOUNDS, ONEP, TWOP, FIVEP, TWENTYP, FIFTYP };

class VMachine
{
public:

	bool turnedOn = true;

	bool service = false;
	bool accessGranted = false;
	bool adding = false;
	bool removing = false;

	std::string password = "1234abc";
	
	//static std::vector<currency> cashVec;

	VMachine()
	{
		std::cout << "new vending machine made\n";
	}

	~VMachine()
	{
		//std::cout << "vending machine destroyed\n";
	}

	void AddCurrecy(currency amount);

	void ReturnMoney();

	void Buy(const std::string& strInt);

	void DefaultStock();

	void DisplayStock();

	void Service();

	void SetBool(operations ops);

	void Add(const std::string& strAdd);

	void Remove(const std::string& strRem);

	void IntroductionMessage();

	void calculateCoinReturn();

	static bool checkLogic(const std::string str1, int *indexToBe, int index);

private:

	float wallet = 0;
	bool hasBoughtSomething = false;
	

	void DisplayWallet();

	void ResetWallet();

	void existingItemCheck(bool* replace, int* indexToBe, const std::string& stringCheckingFor);

	bool ValidateGivenString(operations op, const std::string& stringCheckingFor);

};

