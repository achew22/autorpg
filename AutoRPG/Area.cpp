#include "Area.h"

#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

Area::Area(std::string filename)
{
    std::ifstream inStream(filename.c_str());
    std::string line = "";
    getline(inStream, line);    //Should read "Name:", we can check if we want, but I don't think at this stage that it is necessary
    getline(inStream, name);
    getline(inStream, line);    //Should read "Map:"
    getline(inStream, line);

    std::istringstream inString;
    inString.str(line);
    std::string mapFile1 = "", mapFile2 = "";
    inString >> mapFile1 >> mapFile2;
    map = new Map(mapFile1, mapFile2);

}
