#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

class Entry{
public:
  Entry(){
    strcpy(date, "January 1, 2017");
    value = -1;
  }
  Entry(char* _date, float _value){
    strcpy(this->date, _date);
    this->value = _value;
  } //Constructor
  //~Entry(); //Destructor

  float getValue(){
    return value;
  }
  char* getDate(){
    return date;
  }
private:
  char date[80];
  float value;
};

//FUNCTION SIGNATURES//
void fillEntries(Entry*& entries);
bool readData(const char filename[], Entry*& entries);
bool writeData(const char filename[], Entry* entries);
///////////////////////

void fillEntries(Entry*& entries){
  entries = new Entry[24]; //creates new array with 24 slots
  for (int i = 0; i < 24; i++){ //loops 24 times
    entries[i] = Entry(); //makes default entry, will be overwritten eventually
  }
}

bool readData(const char filename[], Entry*& entries){

    fillEntries(entries); //fill array of entries with default values

    fstream file(filename, ios::binary | ios::in); //input stream

    if (!file.is_open()){
      //log failed to open file
      return false;
  	}

    for (int fileLineNumber = 0; fileLineNumber < 24; fileLineNumber++){ //loops 24 times
      file.seekg(fileLineNumber); //seeks line number
      Entry newEntry; //place holder
      file.read((char *)&newEntry, sizeof(Entry)); //reads binary line, constructs the new entry
      entries[fileLineNumber] = newEntry; //adds new entry to array of entries
    }

    file.close(); //closes stream
    return true;
}



bool writeData(const char filename[], Entry* entries){

  fstream file(filename, ios::binary | ios::out | ios::trunc); //output stream
  char newLine[1] = {'\n'};  //used to make new lines in binary file
  if (!file.is_open()){
    //log failed to open file
    return false;
  }

  for (int fileLineNumber = 0; fileLineNumber < 24; fileLineNumber++){ //loops 24 times
    Entry curEntry = entries[fileLineNumber]; //entry from array of entries to be written
    file.write((char *)&curEntry, sizeof(Entry)); //writes entry in binary
    file.write((char *)newLine, sizeof(char)); //makes new line
  }

  file.close(); //closes stream
  return true;
}



int main (){
  Entry* entries;
  fillEntries(entries);
  writeData("test.cpp", entries);
 //delete above after you use it once
//readData will return array of entries
//keep track of the array of entries and use it when you call writeData

  return 0;
}