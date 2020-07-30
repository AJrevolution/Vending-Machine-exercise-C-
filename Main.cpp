
#include <compare>
#include <string_view>

#include "VMachine.h"


//Functions
void processCommand(VMachine& machine, const std::string& strCommand);
void purchasingProcessor(const std::string& strInt);

int main()
{
	//Create vending machine
	VMachine vendM; 

	std::string command;
	vendM.IntroductionMessage();
	vendM.DefaultStock();
	vendM.DisplayStock();

	//Input loop
	while (vendM.turnedOn)
	{
		std::getline(std::cin, command);

		processCommand(vendM, command);
	}

	return 1;
}

void processCommand(VMachine& machine, const std::string& strCommand)
{
	if (machine.service == false)
	{
		//Money commands
		//Pounds
		if (strCommand._Equal("POUND"))
		{
			machine.AddCurrecy(currency::POUND);
		}

		else if (strCommand == "TWO POUNDS")
		{
			machine.AddCurrecy(currency::TWOPOUNDS);
		}

		//Pennies
		else if (strCommand == "1")
		{
			machine.AddCurrecy(currency::ONEP);
		}

		else if (strCommand == "2")
		{
			machine.AddCurrecy(currency::TWOP);
		}

		else if (strCommand == "5")
		{
			machine.AddCurrecy(currency::FIVEP);
		}

		else if (strCommand == "20")
		{
			machine.AddCurrecy(currency::TWENTYP);
		}

		else if (strCommand == "50")
		{
			machine.AddCurrecy(currency::FIFTYP);
		}

		//Other commands

		//Buy
		//Check if first 3 characters are BUY
		else if (strCommand.compare(0, 3, "BUY") == 0)
		{
			machine.Buy(strCommand);
		}

		//Return
		else if (strCommand == "COIN RETURN")
		{
			machine.ReturnMoney();
		}

		//Service
		else if (strCommand == "SERVICE")
		{
			std::cout << "Service mode entered, please enter the password\n";
			machine.SetBool(operations::SERVICE);
			
		}

		else
		{
			std::cout << "Invalid command\n";
		}
	}

	else if (machine.service == true)
	{
		if (strCommand == "EXIT")
		{
			std::cout << "You have exited service mode\n";
			machine.SetBool(operations::EXIT);
			//machine.service == false;
		}

		else if (machine.accessGranted == false)
		{
			if (strCommand == machine.password)
			{
				std::cout << "Password entered, you can now Add or Remove items from the machine\n";
				machine.SetBool(operations::PASSWORD);
				//machine.accessGranted == true;
			}

			else
			{
				//try again
				std::cout << "Try again to enter the password, or type EXIT\n";
			}
		}

		else
		{
			if (machine.adding == true)
			{
				//Mars Bar, 0.60, 3
				machine.Add(strCommand);
			}

			else if (machine.removing == true)
			{
				machine.Remove(strCommand);
			}

			else if (strCommand == "ADD")
			{
				std::cout << "Enter the item name, its price, and the quantity. Don't use a pound sign\n";
				machine.SetBool(operations::ADD);

			}

			else if (strCommand == "REMOVE")
			{
				std::cout << "Enter the item name, followed by the quantity:”\n";
				machine.SetBool(operations::REMOVE);
			}

			else
			{
				std::cout << "Invalid command, enter either ADD or REMOVE\n";
			}
		}
	}

	
}

void purchasingProcessor(const std::string& strInt)
{
	if (strInt.length() > 4)
	{
		std::string strNumber;
		strNumber = strInt.substr(strInt.find(" ") + 1);
		
		int number = std::stoi(strNumber);

		std::cout << "You want: " << number << std::endl;



	}

	else
	{
		std::cout << "Please enter a space after BUY with an item number\n";
	}
}

//Vending machine class
	//Buy, return, service

//item
	//name, price

//money
	//POUND, TWO POUNDS, 1, 2,  5, 10, 20, 

// INSERT, BUY, RETURN, SERVICE, -- 1, POUND ETC ETC for money
// switch case for each 4, with insert having an additional enums for money