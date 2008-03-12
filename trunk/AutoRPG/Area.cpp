/*
Copyright 2007, 2008 Andrew Allen and Brian Shourd

This file is part of AutoRPG.

AutoRPG is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

AutoRPG is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with AutoRPG (Called LICENSE.txt).  If not, see
<http://www.gnu.org/licenses/>.
*/

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