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

#include "World.h"
#include "Area.h"

#include <string>
#include <fstream>
#include <sstream>
#include <map>

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

void World::AddCharacter(Character* character)
{
    characterMap.insert(std::pair<std::string, Character*>(character->GetId(), character));
}

void World::RemoveCharacter(std::string id)
{
    characterMap.erase(id);
}

Character* World::GetCharacter(std::string id)
{
    std::map<std::string, Character*>::iterator i = characterMap.find(id);
    if (i != characterMap.end())
    {
        return (*i).second;
    }
    return NULL;
}
