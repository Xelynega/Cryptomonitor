
#include "utility.h"

using namespace std;



float parsePrice(const char line[]);
float power(float num, const float p);

//Fetches the price of bitcoin from min-api-cryptocompare
float priceBTC()
{
	std::string command;
	char intake[20];
	ifstream infile;
	command = "curl -k \"https://min-api.cryptocompare.com/data/price?fsym=BTC&tsyms=USD\" | tee mostRecentBTC.txt";//Pull the price and store it in a file
  system(command.c_str());
	infile.open("mostRecentBTC.txt");
	if(!infile.is_open())
		return -1;
	infile.getline(intake, 20);//Read the single line of data present
	if(intake[2] != 'U')//Check to see if its valid
		return -1;
	system("rm -R mostRecentBTC.txt");//Delete the file
	float price = parsePrice(intake);//Parse the price to return the value of the coin
	return price;
}

//Fetches the price of ethererum from min-api-cryptocompare
float priceETH()
{
	std::string command;
	char intake[20];
	ifstream infile;
	command = "curl -k \"https://min-api.cryptocompare.com/data/price?fsym=ETH&tsyms=USD\" | tee mostRecentETH.txt";//Pull the price and store it in a file
	system(command.c_str());
	infile.open("mostRecentETH.txt");
	if(!infile.is_open())
		return -1;
	infile.getline(intake, 20);//Read the single line of data present
	if(intake[2] != 'U')//Check to see if its valid
		return -1;
	system("rm -R mostRecentETH.txt");//Delete the file
	float price = parsePrice(intake);//Parse the price to return the value of the coin
	return price;
}

//Fetches the price of Litecoin from min-api-cryptocompare
float priceLTC()
{
	std::string command;
	char intake[20];
	ifstream infile;
	command = "curl -k \"https://min-api.cryptocompare.com/data/price?fsym=LTC&tsyms=USD\" | tee mostRecentLTC.txt";//Pull the price and store it in a file
	system(command.c_str());
	infile.open("mostRecentLTC.txt");
	if(!infile.is_open())
		return -1;
	infile.getline(intake, 20);//Read the single line of data present
	if(intake[2] != 'U')//Check to see if its valid
		return -1;
	system("rm -R mostRecentLTC.txt");//Delete the file
	float price = parsePrice(intake);//Parse the price to return the value of the coin
	return price;
}

int logFile(const char toLog[], int sev)
{
  //TIME FUNCTION - VERSION OF LOCALTIME USAGE PULLED FROM cplusplus.com
  time_t rawtime;
  struct tm * timeinfo;
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  string tmp = asctime(timeinfo);
  //END OF LOCALTIME USAGE PULLED FROM cplusplus.com

  int size = tmp.size(); //I need the size of what asciitime returns to properly extract all the data from it.

  //This whole block of code is a messy way to extract a numbered month value from tm.
  char month[3] = {tmp[4], tmp[5], tmp[6]};
  string stmonth;
  for(int i = 0; i < 3; i++)
  {
    stmonth += month[i];
  }
  string monthNum;
  if(stmonth ==  "Jan")
  {
      monthNum = "01";
  }
  else if(stmonth == "Feb")
  {
    monthNum = "02";
  }
  else if(stmonth == "Mar")
  {
    monthNum = "03";
  }
  else if(stmonth == "Apr")
  {
    monthNum = "04";
  }
  else if(stmonth == "May")
  {
    monthNum = "05";
  }
  else if(stmonth == "Jun")
  {
    monthNum = "06";
  }
  else if(stmonth == "Jul")
  {
    monthNum = "07";
  }
  else if(stmonth == "Aug")
  {
    monthNum = "08";
  }
  else if(stmonth == "Sep")
  {
    monthNum = "09";
  }
  else if(stmonth == "Oct")
  {
    monthNum = "10";
  }
  else if(stmonth == "Nov")
  {
    monthNum = "11";
  }
  else if(stmonth == "Dec")
  {
    monthNum = "12";
  }
  //End numerical month extraction

  char year[2] = {tmp[size-3], tmp[size-2]};//Extract year
  char day[2] = {tmp[8], tmp[9]};//Extract day
  char currentTime[8];//Extract time (HH:MM:SS)

  //The reason fixed sizes works for all of these is because asciitime always returns in the same format and length.
  for(int i = 0; i < 8; i++)
  {
    currentTime[i] = tmp[11+i];
  }

  string timestamp;
  for(int i = 0; i < 2; i++)//Concatenate day
  {
    timestamp += day[i];
  }
  timestamp += '/' + monthNum + '/'; //Concatenate months
  for(int i = 0; i < 2; i++) //Concatenate years
  {
    timestamp += year[i];
  }
  timestamp += " - ";//Concatenate spacers between date and time
  for(int i = 0; i < 8; i++) //Concatenate time
  {
    timestamp += currentTime[i];
  }
  //timestamp complete, ready to be put into file.

  ofstream outLog;
  switch(sev)//Check severity level and output to matching log file.
  {
    case -1:
    {
      outLog.open("cryptologSevere.log", fstream::app);//Open severe log in append format
      if(!outLog.is_open())
        return -1;
      int i = 0;
      outLog << timestamp << ": ";//Put timestamp at front of line
      while(toLog[i])
      {
        outLog << toLog[i];//Output the toLog that was passed to the function
        i++;
      }
      outLog << "\n\n";//Make space for a new log entry
      outLog.close();
      break;
    }
    case 1:
    {
      outLog.open("cryptologWarning.log", fstream::app);//Open warning log in append format
      if(!outLog.is_open())
        return -1;
      int i = 0;
      outLog << timestamp << ": ";//Put timestamp at front of line
      while(toLog[i])
      {
        outLog << toLog[i];//Output the toLog that was passed to the function
        i++;
      }
      outLog << "\n\n";//Make space for a new log entry
      outLog.close();
      break;
    }
    case 0:
    {
      outLog.open("cryptologNormal.log", fstream::app);//Open normal log in append format
      if(!outLog.is_open())
        return -1;
      int i = 0;
      outLog << timestamp << ": ";//Put timestamp at front of line
      while(toLog[i])
      {
        outLog << toLog[i];//Output the toLog that was passed to the function
        i++;
      }
      outLog << "\n\n";//Make space for a new log entry
      outLog.close();
      break;
    }
    default:
    {
      return -1;//if the logging function broke, there's not much you can do.
    }
  }
  return 0;
}

//Basically a stripped-down string to float function, data is validated before being passed.
float parsePrice(const char line[])
{
	//this is basically a string-to-float function, nothing special, move along.
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

//Power Function to assist in parsePrice's string-to-float
float power(float num, const float p)
{
	//Power function to assist in parsePrice()
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
