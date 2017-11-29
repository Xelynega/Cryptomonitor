/*
#include <iostream>
#include <fstream>

using namespace std;

int logFile(const char toLog[], int sev)
{
  //TIME FUNCTION - VERSION OF LOCALTIME
  time_t rawtime;
  struct tm * timeinfo;
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  string tmp = asctime(timeinfo);
  //END OF LOCALTIME USAGE

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
    case 0:
    {
      outLog.open("cryptolog-severe.txt", fstream::app);//Open severe log in append format
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
    case -1:
    {
      outLog.open("cryptolog-warn.txt", fstream::app);//Open warning log in append format
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
      outLog.open("cryptolog-normal.txt", fstream::app);//Open normal log in append format
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
*/
