nclude <iostream>
#include <fstream>

using namespace std;

int logFile(const char toLog[], int sev)
{
  ofstream outLog;
  switch(sev)
  {
    case 0:
    {
      outLog.open("cryptolog-severe.txt", fstream::app);
      if(!outLog.is_open())
        return -1;
      int i = 0;
      while(toLog[i])
      {
        outLog << toLog[i];
        i++;
      }
      outLog << "\n\n";
      outLog.close();
      break;
    }
    case -1:
    {
      outLog.open("cryptolog-warn.txt", fstream::app);
      if(!outLog.is_open())
        return -1;
      int i = 0;
      while(toLog[i])
      {
        outLog << toLog[i];
        i++;
      }
      outLog << "\n\n";
      outLog.close();
      break;
    }
    case 1:
    {
      outLog.open("cryptolog-normal.txt", fstream::app);
      if(!outLog.is_open())
        return -1;
      int i = 0;
      while(toLog[i])
      {
        outLog << toLog[i];
        i++;
      }
      outLog << "\n\n";
      outLog.close();
      break;
    }
    default:
    {
      return -1;
    }
  }
  return 0;
}

