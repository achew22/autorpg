#include "Map.h"
#include "Point.h"
#include "Conversions.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

Map::Map(std::string spriteIdsFile)
{
    std::ifstream fileIn(spriteIdsFile.c_str());
    std::string line = "";   //the current line

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
            tempLine.push_back(StringToInt(buffer));
            stringIn >> buffer;
        }
        spriteIds.push_back(tempLine);
    }

    fileIn.close();

    spriteDim.x = 1;
    spriteDim.y = 1;
}

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
            tempLine.push_back(StringToInt(buffer));
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

int Map::StringToInt(std::string in)
{
    int total = 0;
    for (int i = 0; i < in.size(); i++)
    {
        total += pow(10.0, in.size() - (i + 1)) * (in[i] - '0');
    }
    return total;
}

void Map::AssignSpriteSheet(Sprite_Sheet* sheet)
{
    spriteSheet = sheet;
    spriteDim = sheet->GetSpriteDimension();
}

void Map::AssignSpriteSheet(int wOfSprite, int hOfSprite, std::string file,
    int red /*= 0*/, int green /*= 255*/, int blue /*= 255*/)
{
    spriteSheet = Sprite_Sheet::FindSheet(file);
    if (spriteSheet == NULL)
    {
        spriteSheet = new Sprite_Sheet(wOfSprite, hOfSprite, file, red, green, blue);
    }
    spriteDim = spriteSheet->GetSpriteDimension();
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
