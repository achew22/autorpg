#ifndef AREA_H
#define AREA_H

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
    Point dim;
    std::map<std::string, Character*> characterMap;
    Map* map;
    std::vector< std::vector<Sector*> > sectorVect;
public:
    Area(std::string filename);
};

#endif
