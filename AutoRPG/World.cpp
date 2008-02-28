#include "World.h"
#include "Area.h"

#include <string>
#include <fstream>
#include <sstream>

World::World(std::string filename)
{
    file = filename;

    std::ifstream fileIn(filename.c_str());
    std::string line = "";   //the current line

    while (!fileIn.eof())
    {
        getline(fileIn, line);
        areaVect.push_back(new Area(line));
    }

    fileIn.close();
}
