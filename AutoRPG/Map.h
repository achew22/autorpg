#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include "Sprite_Sheet.h"
#include "Point.h"

class Map
{
private:
    std::vector< std::vector<int> > spriteIds;
    Sprite_Sheet* spriteSheet;
    int StringToInt(std::string in);
    Point spriteDim;
public:
    Map(std::string spriteIdsFile);
    Map(std::string mapFile, std::string pictureFile);
    void AssignSpriteSheet(Sprite_Sheet* sheet);
    void AssignSpriteSheet(int wOfSprite, int hOfSprite, std::string file, int red = 0, int green = 255, int blue = 255);
    void ApplyMap(int x, int y, int h, int w, SDL_Surface* destination);
    Point GetDim();
};

#endif
