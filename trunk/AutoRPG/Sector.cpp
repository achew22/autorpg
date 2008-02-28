#include "Sector.h"

#include <map>
#include <vector>
#include <string>

Sector::Sector()
{
}

void Sector::MoveChar(std::string id, Sector* destination)
{
    destination->characterMap.insert(destination->characterMap.begin(), std::pair<std::string, Character*>(id, characterMap[id]));
}
