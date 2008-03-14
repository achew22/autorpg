#ifndef WORLD_H
#define WORLD_H

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

#include <map>
#include <string>
#include "Character.h"
#include "Area.h"

class World
{
private:
    std::map<int, Character*> characterMap;
    std::vector<Area*> areaVect;
    std::string file;
public:
    World(std::string filename);
    ~World();
    void AddCharacter(Character* character);
    void RemoveCharacter(int id);
    Character* GetCharacter(int id);
    std::map<int, Character*>* GetCharacterMap();
};

#endif
