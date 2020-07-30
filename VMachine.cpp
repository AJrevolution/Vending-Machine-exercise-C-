#include "VMachine.h"


//Here to prevent LNK errors
static std::vector<currency> cashVec;
static std::vector<Item> stock;

//Used for multithreading when finding objects in stock
std::future<bool> futures;

//Print current wallet
void VMachine::DisplayWallet()
{
	std::cout << "Your wallet: ";
	printf("%.2f\n", wallet);
	
}

//Add money to wallet
void VMachine::AddCurrecy(currency amount)
{
	
	switch (amount)
	{
	case POUND:
		wallet++;
		std::cout << "Added 1 Pound\n";
		break;

	case TWOPOUNDS:
		wallet = wallet + 2;
		std::cout << "Added 2 Pounds\n";
		break;

	case ONEP:
		wallet = wallet + 0.01f;
		std::cout << "Added 1 Pence\n";
		break;
	
	case TWOP:
		wallet = wallet + 0.02f;
		std::cout << "Added 2 Pence\n";
		break;

	case FIVEP:
		wallet = wallet + 0.05f;
		std::cout << "Added 5 Pence\n";
		break;

	case TWENTYP:
		wallet = wallet + 0.20f;
		std::cout << "Added 20 Pence\n";
		break;

	case FIFTYP:
		wallet = wallet + 0.50f;
		std::cout << "Added 50 Pence\n";
		break;

	}
	

	//Add enum to vector to print later
	cashVec.emplace_back(amount);

	//Display what user has put in
	DisplayWallet();
}

//Overloading to print enum 
std::ostream& operator << (std::ostream& str, currency cash)
{
	const std::string cashWords[] = { "POUND", "TWO POUNDS", "ONE PENCE", "TWO PENCE", "FIVE PENCE", "TWENTY PENCE", "FIFTY PENCE" };
	return str << cashWords[cash];
}

//Return money from current wallet
void VMachine::ReturnMoney()
{
	if (hasBoughtSomething == true)
	{
		calculateCoinReturn();
	}

	std::cout << "Coins returned: ";

	//Loop through cash vector and display to screen
	for (int i = 0; i < cashVec.size(); i++)
	{
		if (i != cashVec.size() - 1)
		{
			std::cout << cashVec[i] << ", ";
		}

		else
		{
			std::cout << cashVec[i] << std::endl;
		}
	}

	std::cout << "Total returned: ";
	printf("%.2f\n", wallet);

	cashVec.clear();
	ResetWallet();
}

void VMachine::calculateCoinReturn()
{
	cashVec.clear();
	int floored = floor(wallet);
	float decimal = (wallet - floored) * 100;
	if (floored == 2)
	{
		cashVec.emplace_back(currency::TWOPOUNDS);
	}
	else if (floored > 2)
	{
		while (floored > 2)
		{
			floored = floored - 2;
			cashVec.emplace_back(currency::TWOPOUNDS);
		}

	}

	if (floored == 1)
	{
		cashVec.emplace_back(currency::POUND);
	}

	if (decimal == 50)
	{
		cashVec.emplace_back(currency::FIFTYP);
	}

	if (decimal > 50)
	{
		while (decimal > 50)
		{
			decimal = decimal - 50;
			cashVec.emplace_back(currency::FIFTYP);
		}

	}

	if (decimal == 20)
	{
		cashVec.emplace_back(currency::TWENTYP);
	}

	if (decimal > 20)
	{
		while (decimal > 50)
		{
			decimal = decimal - 20;
			cashVec.emplace_back(currency::TWENTYP);
		}
	
	}

	if (decimal == 5)
	{
		cashVec.emplace_back(currency::FIVEP);
	}

	if (decimal > 5)
	{
		while (decimal > 5)
		{
			decimal = decimal - 5;
			cashVec.emplace_back(currency::FIVEP);
		}

	}

	if (decimal == 2)
	{
		cashVec.emplace_back(currency::TWOP);
	}

	if (decimal > 2)
	{
		while (decimal > 2)
		{
			decimal = decimal - 2;
			cashVec.emplace_back(currency::TWOP);
		}
	
	}

	if (decimal == 1)
	{
		cashVec.emplace_back(currency::ONEP);
	}

	if (decimal > 1)
	{
		while (decimal > 1)
		{
			decimal = decimal - 1;
			cashVec.emplace_back(currency::ONEP);
		}

	}

}

//Purchase an item
void VMachine::Buy(const std::string& strInt)
{
	if (hasBoughtSomething == false)
	{
		hasBoughtSomething = true;
	}
	if (ValidateGivenString(operations::BUY, strInt) == true)
	{
		//Convert string number to integer 
		std::string strNumber;
		strNumber = strInt.substr(strInt.find(" ") + 1);

		int number = std::stoi(strNumber);

		//Make sure stock vector is large enough to prevent errors
		if (stock.size() > 0 && number < stock.size())
		{

			//check if wallet big enough for item && quantity > 0 
			if (wallet > stock[number].Price)
			{
				if (stock[number].Quantity > 0)
				{
					//subtract price from wallet
					wallet -= stock[number].Price;

					//subtract quantity
					stock[number].Quantity = stock[number].Quantity - 1;
				}

				else
				{
					//No items left in stock
					std::cout << "Sold out\n";
				}
			}

			//display message lacking funds 
			else { std::cout << "You lack funds, you currently have \n" << wallet << " and you need " << stock[number].Price << std::endl; }


		}

		else { std::cout << "Invalid item number\n"; }

		DisplayStock();
		
	}
	else
	{
		std::cout << "Please enter a space after BUY with an item number\n";
	}
}

void VMachine::ResetWallet()
{
	wallet = 0.00f;
}

void VMachine::DefaultStock()
{
	stock.emplace_back(Item("Pepsi", 3.32f, 5));
	stock.emplace_back(Item("Coke", 0.32f, 5));
	stock.emplace_back(Item("Crisps", 3.0f, 5));
	stock.emplace_back(Item("Uncle Ben Rice", 2.2f, 5));
	stock.emplace_back(Item("Television Entertainment System", 300.32f, 5));
	stock.emplace_back(Item("DOOM", 6.00f, 32));
	stock.emplace_back(Item("BrOwNiE", 1.00f, 50));
	stock.emplace_back(Item("food", 0.20f, 50));
}

void VMachine::DisplayStock()
{
	std::cout << "\nStock: \n";
	for (int i = 0; i < stock.size(); i++)
	{
		std::cout << "Item number|" << i << "| Name: " << stock[i].name << ", Price: " << stock[i].Price << ", Quantity: " << stock[i].Quantity << std::endl;
	}
}

void VMachine::Service()
{
	
}

void VMachine::SetBool(operations ops)
{
	switch (ops)
	{
	case SERVICE:
		service = true;
		break;

	case PASSWORD:
		accessGranted = true;
		break;

	case EXIT:
		service = false;
		accessGranted = false;
		adding = false;
		removing = false;
		break;

	case ADD:
		adding = true;
		removing = false;
		break;

	case REMOVE:
		removing = true;
		adding = false;
		break;
	
	}
}

void VMachine::Add(const std::string& strAdd)
{
	//Used to decipher given string into separate string objects
	std::string name, strprice, strquantity;

	//Used to store index of an already existing stock item
	int indexFinder = 9999; 

	//Used to check how far algorithm is through given string
	int counter = 0;
	
	//Used to see if an object needs its quantity replacing
	bool replacer = false;

	//Ensure string meets function standards and no error will happen
	if (ValidateGivenString(operations::ADD ,strAdd) == true)
	{

		//Cannot compare string to const string like strAdd[i] == "," thus need this string
		std::string comma = ",";

		//loop through string and add to name, strprice, strquantity to decipher into floats and integers for comparison
		for (int i = 0; i < strAdd.length() - 1; i++)
		{
			if (strAdd[i] == comma[0])
			{
				counter++;
				continue;

			}

			else
			{
				//Complete name string
				if (counter == 0)
				{
					name.push_back(strAdd[i]);

				
				}

				//Complete price string
				else if (counter == 1)
				{
					existingItemCheck(&replacer, &indexFinder, name);
		

					strprice.push_back(strAdd[i + 1]);


				}

				//Complete quantity string
				else if (counter == 2)
				{
					strquantity.push_back(strAdd[i + 1]);
				}
			}
		}


		//Convert string to floats and integers
		float fprice;
		int intquant;
		fprice = std::stof(strprice);
		float round_down = floorf(fprice * 100) / 100;
		intquant = std::stoi(strquantity);

		//Replace existing object
		if (replacer == true)
		{
			std::cout << stock[indexFinder].name << " already exists, increasing quantity\n";
			stock[indexFinder].Quantity += intquant;
			stock[indexFinder].Price = round_down;

		}

		//Add new object
		else
		{
			stock.emplace_back(Item(name, round_down, intquant));
			std::cout << name << " " << round_down << " " << intquant << std::endl;
		}

		DisplayStock();
	}

	else
	{
		std::cout << "Invalid string entered, format is (space included): String, Number, Number\n";
	}
	
}

void VMachine::Remove(const std::string& strRem)
{
	std::string name, strquantity;
	int indexFinder = 9999;
	int counter = 0;
	bool replacer = false;

	//Ensure string meets function standards 
	if (ValidateGivenString(operations::REMOVE, strRem) == true)
	{

		//Cannot compare string to const string like strAdd[i] == "," thus need this string
		std::string comma = ",";
		for (int i = 0; i < strRem.length() - 1; i++)
		{
			if (strRem[i] == comma[0])
			{
				counter++;
				continue;

			}

			else
			{
				//decipher name from given string to name
				if (counter == 0)
				{
					name.push_back(strRem[i]);			
				}

				//decipher quantity from given string
				else if (counter == 1)
				{
					//Check if item exists, if not cancel entire loop and function
					existingItemCheck(&replacer, &indexFinder, name);
						
					if(replacer == false)
					{
						std::cout << " Item does not exist\n";
						break;
					}
					
					strquantity.push_back(strRem[i + 1]);
				}

			}
		}
		
		if (replacer == true)
		{
			int intquant;
			intquant = std::stoi(strquantity);

		
			if (intquant < stock[indexFinder].Quantity)
			{
				stock[indexFinder].Quantity -= intquant;
			}

			else
			{
				stock.erase(stock.begin() + indexFinder);
			}

		}
	}

	else
	{
		std::cout << "String entered incorrectly. Please enter the name, with quantity after (name, quantity)\n";
	}

	DisplayStock();
}
void VMachine::IntroductionMessage()
{
	std::cout << "\nWelcome to the vending machine\n\n";

		std::cout << "Commands:\n BUY [Item Number], SERVICE -> ADD -> (NAME, [PRICE], [QUANTITY]) - REMOVE -> (NAME, QUANTITY), EXIT (SERVICE), POUND, TWO POUNDS, 1, 2, 5, 20, 50, COIN RETURN\n\n";
                                         
}


//Multi thread search over vector
void VMachine::existingItemCheck(bool* replace, int* indexToBe, const std::string& stringCheckingFor)
{
	
	std::string comparative1, comparative2;
	comparative1 = stringCheckingFor;
	
	//convert string1 to lowercase
	std::transform(comparative1.begin(), comparative1.end(), comparative1.begin(), ::tolower);

	//Loop over stock to see if the given string already exists
	for (int i = 0; i < stock.size(); i++)
	{
		//Look at entire vector in different threads
		futures = std::async(std::launch::async, checkLogic, comparative1, indexToBe, i);
		
		//Prevent a true replace boolean from being overriden from a later found false value
		if (*replace == false)
		{
			*replace = futures.get();
		}
	}
}

//Compare to see if a given item exists in stock already
bool VMachine::checkLogic(const std::string str1, int *indexToBe, int index)
{
	std::string str2 = stock[index].name;

	//convert string 2 to lowercase
	std::transform(str2.begin(), str2.end(), str2.begin(), ::tolower);

	if (str1 == str2)
	{
		*indexToBe = index;
		
		return true;
	}

	return false;
}

bool VMachine::ValidateGivenString(operations op ,const std::string& stringCheckingFor)
{
	if (op == operations::BUY)
	{
		if (stringCheckingFor.length() > 4)
		{
			//if(stringCheckingFor[5] != )
			for (int i = 4; i < stringCheckingFor.length(); i++)
			{
				//Ensure 2 characters infront contains a digit
				if (!std::isdigit(stringCheckingFor[i]))
				{
					std::cout << "Enter a valid item number\n";
					return false;
				}
			}

			return true;
		}

		else
		{
			return false;
		}
	}

	else
	{
		int counter = 0;
		std::string comma = ",";
		std::string space = " ";

		//Check if string is empty
		if (stringCheckingFor.empty() == true)
		{
			return false;
		}

		//Ensure it ends with a number
		if (!std::isdigit(stringCheckingFor[stringCheckingFor.length() - 1]))
		{
			return false;
		}

		//Ensure it doesn't start with a space
		if (stringCheckingFor[0] == space[0])
		{
			return false;
		}

		//Ensure it doesn't start with a comma
		if (stringCheckingFor[0] == comma[0])
		{
			return false;
		}

		//For ADD operation
		if (op == operations::ADD)
		{

			for (int i = 0; i < stringCheckingFor.length(); i++)
			{
				if (stringCheckingFor[i] == comma[0])
				{
					counter++;
					//Ensure no space before the comma
					if (stringCheckingFor[i - 1] == space[0])
					{
						return false;
					}

					//Ensure there is a space after the comma
					if (stringCheckingFor[i + 1] != space[0])
					{
						return false;
					}


					if (counter == 1)
					{
						//Ensure 2 characters infront contains a digit
						if (!std::isdigit(stringCheckingFor[i + 2]))
						{
							return false;
						}
					}

					if (counter == 2)
					{
						//Ensure 2 characters infront contains a digit
						if (!std::isdigit(stringCheckingFor[i + 2]))
						{
							return false;
						}
					}
				}
			}

			//All checks passed
			if (counter == 2)
			{
				return true;
			}

		}

		else if (op == operations::REMOVE)
		{

			for (int i = 0; i < stringCheckingFor.length(); i++)
			{
				if (stringCheckingFor[i] == comma[0])
				{
					counter++;

					//Ensure character before first comma is not a space
					if (stringCheckingFor[i - 1] == space[0])
					{
						return false;
					}

					//Ensure character after comma is a space
					if (stringCheckingFor[i + 1] != space[0])
					{
						return false;
					}

					if (counter == 1)
					{
						//Ensure 2 characters infront contains a digit
						if (!std::isdigit(stringCheckingFor[i + 2]))
						{
							return false;
						}
					}

					if (counter > 1)
					{
						//If more comma's appear, then cancel
						return false;

					}
				}
			}

			if (counter == 1)
			{
				return true;
			}
		}
	}
	return false;
	


}



//if (amount == POUND)
	//{
	//	wallet++;
	//	
	//	std::cout << "Added 1 Pound\n";
	//}
	//
	//else if (amount == TWOPOUNDS)
	//{
	//	wallet = wallet + 2;
	//
	//	std::cout << "Added 2 Pounds\n";
	//}
	//
	//else if (amount == ONEP)
	//{
	//	wallet = wallet + 0.01;
	//
	//	std::cout << "Added 1 Pence\n";
	//}
	//
	//else if (amount == TWOP)
	//{
	//	wallet = wallet + 0.02;
	//
	//	std::cout << "Added 2 Pence\n";
	//}
	//
	//else if (amount == FIVEP)
	//{
	//	wallet = wallet + 0.05;
	//
	//	std::cout << "Added 5 Pence\n";
	//}
	//
	//else if (amount == TWENTYP)
	//{
	//	wallet = wallet + 0.20;
	//
	//	std::cout << "Added 20 pence\n";
	//}
	//
	//else if (amount == FIFTYP)
	//{
	//	wallet = wallet + 0.50;
	//
	//	std::cout << "Added 50 pence\n";
	//}



	//for (int i = 0; i < stock.size(); i++)
	//{
	//	comparative2 = stock[i].name;
	//
	//	//convert string 2 to lowercase
	//	std::transform(comparative2.begin(), comparative2.end(), comparative2.begin(), ::tolower);
	//
	//	if (comparative1 == comparative2)
	//	{
	//		indexToBe = i;
	//		return true;
	//	}
	//}

