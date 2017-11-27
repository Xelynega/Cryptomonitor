#include <fstream>
#include <string>
#include <cstdlib>

#ifndef utility
#define utility

float priceBTC();
float priceETH();
float priceLTC();

int logFile(const char toLog[], int sev);

#endif
