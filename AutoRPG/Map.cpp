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

#include "Map.h"
#include "Point.h"
#include "Conversions.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

Map::Map(std::string mapFile, std::string pictureFile)
{
    std::ifstream fileIn(mapFile.c_str());
    std::string line = "";   //the current line
    getline(fileIn, line);
    std::istringstream stringIn;
    stringIn.str(line);
    std::string temp = "";
    stringIn >> temp;
    spriteDim.x = Conversions::StringToInt(temp);
    stringIn >> temp;
    spriteDim.y = Conversions::StringToInt(temp);

    while (!fileIn.eof())
    {
        getline(fileIn, line);
        line += " END__";
        std::string buffer = "";
        std::istringstream stringIn;
        stringIn.str(line);
        std::vector<int> tempLine;
        stringIn >> buffer;
        while (buffer != "END__")
        {
            tempLine.push_back(Conversions::StringToInt(buffer));
            stringIn >> buffer;
        }
        spriteIds.push_back(tempLine);
    }

    fileIn.close();

    spriteSheet = Sprite_Sheet::FindSheet(pictureFile);
    if (spriteSheet == NULL)
    {
        spriteSheet = new Sprite_Sheet(spriteDim.x, spriteDim.y, pictureFile);
    }
}

void Map::ApplyMap(int x, int y, int w, int h, SDL_Surface* destination)
{
    if (spriteSheet == NULL)
    {
        return;
    }
    Point start, numberTiles;
    start.x = (int)(x/spriteDim.x);
    start.y = (int)(y/spriteDim.y);
    numberTiles.x = (int)(w/spriteDim.x) + 1;
    numberTiles.y = (int)(h/spriteDim.y) + 1;
    if ((start.x + numberTiles.x >= spriteIds.size()) || (start.y + numberTiles.y >= spriteIds[0].size()))
    {
        return;
    }
    for (int i = start.x * spriteDim.x; i <= (start.x + numberTiles.x) * spriteDim.x; i += spriteDim.x)
    {
        for (int j = start.y * spriteDim.y; j <= (start.y + numberTiles.y) * spriteDim.y; j += spriteDim.y)
        {
            if ((i >= 0) && (j >= 0))
            {
                spriteSheet->ApplySprite(i, j, spriteIds[i/spriteDim.x][j/spriteDim.y], destination);
            }
        }
    }
}

Point Map::GetDim()
{
    return Point(spriteIds.size(), spriteIds[0].size());
}
