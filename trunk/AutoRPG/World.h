#ifndef WORLD_H
#define WORLD_H

#include <map>
#include <string>
#include "Character.h"
#include "Area.h"

class World
{
private:
    std::map<std::string, Character*> characterMap;
    std::vector<Area*> areaVect;
    std::string file;
public:
    World(std::string filename);
};

#endif
