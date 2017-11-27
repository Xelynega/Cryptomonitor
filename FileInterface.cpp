#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

class Entry{
public:
  Entry(){
    value = -1;
  }
  Entry(float _value){
    this->value = _value;
  } //Constructor
  //~Entry(); //Destructor

  float getValue(){
    return value;
  }
  void setValue(float newValue){
      value = newValue;
  }
private:
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
    /*for (int fileLineNumber = 0; fileLineNumber < 24; fileLineNumber++){ //loops 24 times
      //file.seekg(fileLineNumber); //seeks line number
      Entry newEntry; //place holder
      file.read((char *)&newEntry, sizeof(Entry)); //reads binary line, constructs the new entry
      entries[fileLineNumber] = newEntry; //adds new entry to array of entries
    }*/
    std::cout << "Values in file: ";
    for(int i = 0; i < 24; i++)
    {
        float temp;
        file.read((char*)&temp, sizeof(float));
        entries[i].setValue(temp);
        std::cout << temp << ", ";
    }
    std::cout << std::endl;

    file.close(); //closes stream
    return true;
}



bool writeData(const char filename[], Entry* entries){

  fstream file(filename, ios::binary | ios::out | ios::trunc); //output stream
  //char newLine[1] = {'\n'};  //used to make new lines in binary file
  if (!file.is_open()){
    //log failed to open file
    return false;
  }

  /*for (int fileLineNumber = 0; fileLineNumber < 24; fileLineNumber++){ //loops 24 times
    Entry curEntry = entries[fileLineNumber]; //entry from array of entries to be written
    file.write((char *)&curEntry, sizeof(Entry)); //writes entry in binary
    //file.write((char *)newLine, sizeof(char)); //makes new line
  }*/
  for(int i = 0; i < 24; i++)
  {
      float temp = entries[i].getValue();
      file.write((char*)&temp, sizeof(float));
  }

  file.close(); //closes stream
  return true;
}



int main (){
  Entry* entries;
  fillEntries(entries);
  writeData("test.dat", entries);
  readData("test.dat", entries);

 //delete above after you use it once
//readData will return array of entries
//keep track of the array of entries and use it when you call writeData

  return 0;
}