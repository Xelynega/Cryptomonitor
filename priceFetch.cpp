#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

float power(float num, const float p)
{
	float constantNum = num;
	if(p==0)
		return 1;
	else if (p < 0)
	{
		for(int i = 0; i > p; i--)
			num = num/constantNum;
	}
	else
	{
		for(int i = 1; i < p; i++)
			num = num*constantNum;
	}
	return num;
}

float parsePrice(const char line[])
{
	int i = 0;
	float price = 0;
	bool escape = true;
	while(line[i] && escape)
	{
		char test = line[i];
		switch(test)
		{
			case '9':
			case '8':
			case '7':
			case '6':
			case '5':
			case '4':
			case '3':
			case '2':
			case '1':
			case '0':
			{
				price = price*10 + (test-48);
				break;
			}
			case '.':
			{
				 escape = false;
				 break;
			}
			default:
			{
				break;
			}


		}
		i++;
	}

	int counterDec = 1;
	escape = true;
	float decPrice = 0;

	while(line[i] && escape)
	{
		char test = line[i];
		switch(test)
		{
			case '9':
			case '8':
			case '7':
			case '6':
			case '5':
			case '4':
			case '3':
			case '2':
			case '1':
			case '0':
			{
				decPrice = decPrice+(power(0.1,counterDec) * (test-48));
				counterDec++;
				break;
			}
			case '.':
			{
				 escape = false;
				 break;
			}
			default:
			{
				break;
			}


		}
		i++;
	}

	float returnPrice = price+decPrice;
	return returnPrice;
}

float priceBTC()
{
	std::string command;
	char intake[20];
	ifstream infile;
	command = "curl -k \"https://min-api.cryptocompare.com/data/price?fsym=BTC&tsyms=USD\" | tee mostRecentBTC.txt";
  system(command.c_str());
	infile.open("mostRecentBTC.txt");
	if(!infile.is_open())
		return -1;
	infile.getline(intake, 20);
	if(intake[2] != 'U')
		return -1;
	system("rm -R mostRecentBTC.txt");
	float price = parsePrice(intake);
	return price;
}

float priceETH()
{
	std::string command;
	char intake[20];
	ifstream infile;
	command = "curl -k \"https://min-api.cryptocompare.com/data/price?fsym=ETH&tsyms=USD\" | tee mostRecentETH.txt";
	system(command.c_str());
	infile.open("mostRecentETH.txt");
	if(!infile.is_open())
		return -1;
	infile.getline(intake, 20);
	system("rm -R mostRecentETH.txt");
	if(intake[2] != 'U')
		return -1;
	float price = parsePrice(intake);
	return price;
}

float priceLTC()
{
	std::string command;
	char intake[20];
	ifstream infile;
	command = "curl -k \"https://min-api.cryptocompare.com/data/price?fsym=LTC&tsyms=USD\" | tee mostRecentLTC.txt";
	system(command.c_str());
	infile.open("mostRecentLTC.txt");
	if(!infile.is_open())
		return -1;
	infile.getline(intake, 20);
	system("rm -R mostRecentLTC.txt");
	if(intake[2] != 'U')
		return -1;
	float price = parsePrice(intake);
	return price;
}



int main(const int argc, const char* const argv[])
{
	float BTC = priceBTC();
	float LTC = priceLTC();
	float ETH = priceETH();
	cout << "\n\n\n";
	cout << LTC << endl;
	cout << BTC << endl;
	cout << ETH << endl;
	return 0;
}
