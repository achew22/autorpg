#ifndef AREA_H
#define AREA_H

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

class Character;    //Forward declaration to avoid declaration rings because the Area class needs to know the Character class,
    //but the Character class needs to know the Area class, so neither can be made...

#include "Sector.h"
#include "Map.h"
#include "Point.h"

#include <vector>
#include <map>
#include <string>

class Area
{
private:
    std::string name;
    int id;
    Point dim;
    std::map<int, Character*> characterMap;
    Map* map;
    std::vector< std::vector<Sector*> > sectorVect;
public:
    Area(std::string filename);
    std::string GetMapInfo();
    int GetId();
};

#endif