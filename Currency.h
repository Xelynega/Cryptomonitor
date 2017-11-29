#ifndef CURRENCY_H
#define CURRENCY_H

#include <fstream>
#include <thread>
#include <sys/stat.h>
#include <chrono>
#include <iostream>
#include "FileInterface.cpp"
#include "utility.h"

#define nullptr 0

enum CURRENCIES {BITCOIN, ETHEREUM, LITECOIN, UNDEFINED};


class Currency
{
    public:
        Currency(const char* priceFileName);
        float getDeltaPrice()
        {
            /*TESTING CODE
            if(m_size == 0)
                return -1;
            if(m_size == 1)
                return 0;
            if(m_size > 24)
            {
                return m_prices[m_size-1] - m_prices[m_size-26];
            }
            else
            {
                float average = 0;
                int i = 0;
                for(int i = 0; i < m_size - 1; i++)
                    average += m_prices[i];
                average /= (m_size-1);
                return m_prices[m_size-1] - average;
            }*/
            
            logFile("Getting Price Delta in Currency.h::getDeltaPrice()", 0);
            float dp = entries[23].getValue() - entries[0].getValue();
            std::cout << entries[1].getValue() << std::endl;
            return dp;
        }
        float getDeltaPercent()
        {
           /*TESTING CODE
           
           if(m_size == 0)
                return -1;
            if(m_size == 1)
                return 0;
            if(m_size > 24)
            {
                return (m_prices[m_size-1] - m_prices[m_size-26]) / m_prices[m_size-26];
            }
            else
            {
                float average = 0;
                int i = 0;
                for(int i = 0; i < m_size - 1; i++)
                    average += m_prices[i];
                average /= (m_size-1);
                return (m_prices[m_size-1] - average) / average;
            }*/
            
            logFile("Getting Price Delta % in Currency.h::getDeltaPercent()", 0);
            return ((entries[23].getValue() - entries[0].getValue()) / entries[23].getValue()) * 100;
        }
        float getPrice()
        {
            /*TEST CODE
            std::cout << "Number of Prices: " << m_size << std::endl;
            if(m_size == 0)
                return -1;
            return m_prices[m_size-1];*/
            
            logFile("Fetching current price from within Currency class in Currency.h::getPrice()", 0);
            return entries[23].getValue();
        }
        void addPrice(float price)
        {
            /*TEST CODE
            
            if(price < 0)
                return;
            //std::cout << "Current Size: " << m_size << std::endl;
            std::ofstream currencyFile(m_priceFileName, std::ios::out | std::ios::app | std::ios::binary);
            currencyFile.write((char*)&price, sizeof(float));
            currencyFile.close();
            //std::cout << "Wrote new price to file: " << price << std::endl;
            float* temp = new float[m_size];
            for(int i = 0; i < m_size; i++)
            {
                temp[i] = m_prices[i];
            }
            delete m_prices;
            m_size++;
            m_prices = new float[m_size];
            for(int i = 0; i < m_size-1; i++)
            {
                m_prices[i] = temp[i];
            }
            m_prices[m_size-1] = price;*/
            
            logFile("Adding price to currency in Currency.h::addPrice().", 0);
            
            if(price < 0)
            {
                logFile("Invalid price passed to Currency.h::addPrice().", 1);
                return;
            }
            Entry* tempEntries = new Entry[24];
            for(int i = 0; i < 23; i++)
            {
                tempEntries[i] = entries[i+1];
            }
            Entry newEntry(price);
            tempEntries[23] = newEntry;
            delete entries;
            entries = tempEntries;
            writeData(m_priceFileName, entries);
        }
    unsigned char* m_bitmap;
    private:
    //float* m_prices;
    //unsigned int m_size;
    Entry* entries;
    char* m_priceFileName;
};

Currency::Currency(const char* priceFileName)
{
    logFile("Creating new currency in Currency.h::Currency() (non-default constructor)", 1);
    unsigned int fileNameSize = 0;
    for(; priceFileName[fileNameSize] != 0; fileNameSize++);

    m_priceFileName = new char[fileNameSize+1];
    for(int i = 0; i < fileNameSize; i++)
    {
        m_priceFileName[i] = priceFileName[i];
    }
    m_priceFileName[fileNameSize] = 0;

    readData(m_priceFileName, entries);

    /*TEST CODE
    
    struct stat results;
    std::ifstream currencyFile(priceFileName, std::ios::in | std::ios::binary);
    if(currencyFile.is_open())
    {
        stat(priceFileName, &results);
        m_size = results.st_size/sizeof(float);
        std::cout << "Floats in file: " << m_size << std::endl;
        m_prices = new float[m_size];
        for(unsigned int i = 0; i < m_size; i++)
        {
            float tmp;
            currencyFile.read((char*)&tmp, sizeof(float));
            m_prices[i] = tmp;
            std::cout << m_prices[i] << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        m_size = 0;
        m_prices = nullptr;
        std::ofstream makeFile(priceFileName, std::ios::binary);
        makeFile.close();
    }*/
}

#endif
