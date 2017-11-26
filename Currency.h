#ifndef CURRENCY_H
#define CURRENCY_H

#include <fstream>
#include <thread>
#include <sys/stat.h>
#include <chrono>
#include <iostream>
#define nullptr 0;

enum CURRENCIES {BITCOIN, ETHEREUM, LITECOIN, UNDEFINED};


class Currency
{
    public:
        Currency(const char* priceFileName);
        float getDeltaPrice()
        {
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
            }
        }
        float getDeltaPercent()
        {
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
            }
        }
        float getPrice()
        {
            std::cout << "Number of Prices: " << m_size << std::endl;
            if(m_size == 0)
                return -1;
            return m_prices[m_size-1];
        }
        void addPrice(float price)
        {
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
            m_prices[m_size-1] = price;
        }
    unsigned char* m_bitmap;
    private:
    float* m_prices;
    unsigned int m_size;
    char* m_priceFileName;
};

Currency::Currency(const char* priceFileName)
{
    unsigned int fileNameSize = 0;
    for(; priceFileName[fileNameSize] != 0; fileNameSize++);

    m_priceFileName = new char[fileNameSize+1];
    for(int i = 0; i < fileNameSize; i++)
    {
        m_priceFileName[i] = priceFileName[i];
    }
    m_priceFileName[fileNameSize] = 0;

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
    }
}

#endif