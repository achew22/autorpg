#include "Conversions.h"

#include <string>
#include <cmath>
#include <sstream>

std::string Conversions::IntToString(int toConvert)
{
    std::string toReturn = "";
    for (int i = 0; pow(10.0, i) < 10*toConvert; i++)
    {
        toReturn = (char)((toConvert%(int)pow(10.0, i+1))/(pow(10,i)) + '0') + toReturn;
        toConvert -= toConvert%(int)pow(10.0, i+1);
    }
    return toReturn;
}

int Conversions::StringToInt(std::string toConvert)
{
    int toReturn = 0;
    for (int i = 0; i < toConvert.size(); i++)
    {
        toReturn += (int)((toConvert[toConvert.size()-i-1]-'0')*pow(10.0, i));
    }
    return toReturn;
}
