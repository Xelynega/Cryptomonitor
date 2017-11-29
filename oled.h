#include <oled-exp.h>
#include <ugpio/ugpio.h>
#include <stdio.h>
#include <iostream>
#include "Currency.h"
#include "utility.h"
#include <thread>

#define BUTTON_GPIO 19

const unsigned char delta[] = {0x70, 0x4C, 0x42, 0x42, 0x4C, 0x70};

void oledInitialize()
{
    logFile("Initializing OLED in oled.h::oledInitialize()", 0);
    oledDriverInit();
    oledClear();
    gpio_free(BUTTON_GPIO);
    gpio_request_one(BUTTON_GPIO, GPIOF_DIR_IN, 0);
    gpio_direction_input(BUTTON_GPIO);
}

void drawBorder()
{
    logFile("Drawing OLED border in oled.h::drawBorder()", 0);
    oledSetCursorByPixel(0, 0);
    oledWriteByte(0xFF);
    for(int i = 0; i < 126; i++)
    {
        oledWriteByte(0x01);
    }
    oledWriteByte(0xFF);
    for(int i = 1; i < 7; i++)
    {
        oledSetCursorByPixel(i, 0);
        oledWriteByte(0xFF);
        oledSetCursorByPixel(i, 127);
        oledWriteByte(0xFF);
    }
    oledSetCursorByPixel(7, 0);
    oledWriteByte(0xFF);
    for(int i = 0; i < 126; i++)
    {
        oledWriteByte(0b10000000);
    }
    oledWriteByte(0xFF);
}

void drawBitmap(char column, char row, const unsigned char bitmap[])
{
    logFile("Drawing bitmap for OLED in oled.h::drawBitmap()", 0);
    for(int i = 0; i < 8; i++)
    {
        oledSetCursorByPixel(row + i, column);
        for(int j = 0; j < 64; j++)
        {
            oledWriteByte(bitmap[(i*64)+j]);
        }
    }
}

void printArray(const unsigned char array[6])
{
    logFile("Printing array for OLED in oled.h::printArray()", 0);
    for(int i = 0; i < 6; i++)
    {
        oledWriteByte(array[i]);
    }
}

void drawUI(const unsigned char bitmap[])
{
    logFile("Drawing UI for OLED in oled.h::drawUI()", 0);
    drawBitmap(0, 0, bitmap);
    const char* btcString = "$:      ";
    oledSetCursorByPixel(2, 58);
    for(int i = 0; btcString[i] != 0; i++)
        oledWriteChar(btcString[i]);

    oledSetCursorByPixel(4, 58);
    printArray(delta);
    oledWriteChar('%');
    oledWriteChar(':');
    oledWriteChar(' ');
    oledWriteChar(' ');
    oledWriteChar(' ');
    oledWriteChar(' ');
    oledWriteChar(' ');
    oledWriteChar('%');

    oledSetCursorByPixel(5, 58);
    printArray(delta);
    oledWriteChar('$');
    oledWriteChar(':');
    oledWriteChar(' ');
    oledWriteChar(' ');
    oledWriteChar(' ');
    oledWriteChar(' ');
    oledWriteChar(' ');
    oledWriteChar('$');
}

void updatePrices(float price, float deltaPercent, float deltaPrice)
{
    logFile("Updating prices for OLED in oled.h::updatePrices()", 0);
    oledSetCursorByPixel(2, 70);
    char priceString[16];
    sprintf(priceString, "%f6.6", price);
    int decimal = 0;
    while(priceString[decimal] != '.' && decimal < 8)
        decimal++;

    for(int i = 0; i < decimal+3; i++)
        oledWriteChar(priceString[i]);
    if(deltaPercent < 0)
    {
        oledSetCursorByPixel(4,115);
        oledWriteByte(0x04);
        oledWriteByte(0x0C);
        oledWriteByte(0x1C);
        oledWriteByte(0x3C);
        oledWriteByte(0x3C);
        oledWriteByte(0x1C);
        oledWriteByte(0x0C);
        oledWriteByte(0x04);
        deltaPercent *= -1;
    }
    else
    {
        oledSetCursorByPixel(4, 115);
        oledWriteByte(0x20);
        oledWriteByte(0x30);
        oledWriteByte(0x38);
        oledWriteByte(0x3C);
        oledWriteByte(0x3C);
        oledWriteByte(0x38);
        oledWriteByte(0x30);
        oledWriteByte(0x20);
    }
    char dPercentString[8];
    sprintf(dPercentString, "%f4.2", deltaPercent);
    int addPercent = 0;
    if(dPercentString[2] == '.')
        addPercent++;
    oledSetCursorByPixel(4, 82-6*addPercent);
    for(int i = 0; i < 4 + addPercent; i++)
        oledWriteChar(dPercentString[i]);
    if(deltaPrice < 0)
    {
        oledSetCursorByPixel(5, 115);
        oledWriteByte(0x04);
        oledWriteByte(0x0C);
        oledWriteByte(0x1C);
        oledWriteByte(0x3C);
        oledWriteByte(0x3C);
        oledWriteByte(0x1C);
        oledWriteByte(0x0C);
        oledWriteByte(0x04);
        deltaPrice *= -1;
    }
    else
    {
        oledSetCursorByPixel(5, 115);
        oledWriteByte(0x20);
        oledWriteByte(0x30);
        oledWriteByte(0x38);
        oledWriteByte(0x3C);
        oledWriteByte(0x3C);
        oledWriteByte(0x38);
        oledWriteByte(0x30);
        oledWriteByte(0x20);
    }
    char dPriceString[8];
    sprintf(dPriceString, "%f4.2", deltaPrice);
    int addPrice = 0;
    if(dPriceString[2] == '.')
        addPrice++;
    oledSetCursorByPixel(5, 82-6*addPrice);
    for(int i = 0; i < 4 + addPrice; i++)
        oledWriteChar(dPriceString[i]);
}

drawErrorSign(){}

clearErrorSign(){}

char screenNum = 0;
char lastScreenNum = -1;
char numScreens = 3;
char lastState = false;
#include <mutex>

void updateGUI(Currency* cryptos[], bool& update, std::mutex* priceMutex, bool fetchError)
{
    logFile("Updating GUI for OLED in oled.h::updateGUI()", 0);
    int changed = false;
    int buttonState = gpio_get_value(BUTTON_GPIO);

    if(fetchError)
        drawErrorSign();
    else
        clearErrorSign();
    
    if(buttonState != lastState)
    {
        if(lastState == 0)
            screenNum++;
        lastState = buttonState;
    }

    if(screenNum < 0)
        screenNum = numScreens-1;
    if(screenNum > numScreens -1)
        screenNum = 0;
    if(lastScreenNum != screenNum)
    {
        lastScreenNum = screenNum;
        oledClear();
        drawUI(cryptos[screenNum]->m_bitmap);
        priceMutex->lock();
        updatePrices(cryptos[screenNum]->getPrice(), cryptos[screenNum]->getDeltaPercent(), cryptos[screenNum]->getDeltaPrice());
        priceMutex->unlock();
    }

    if(update)
    {
        if(priceMutex->try_lock())
        {
            updatePrices(cryptos[screenNum]->getPrice(), cryptos[screenNum]->getDeltaPercent(), cryptos[screenNum]->getDeltaPrice());
            update = false;
            priceMutex->unlock();
        }
    }
}
