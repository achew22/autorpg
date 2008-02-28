#ifndef SECTOR_H
#define SECTOR_H

class Character;    //Forward declaration to avoid declaration rings because the Sector class needs to know the Character class,
    //but the Character class needs to know the Sector class, so neither can be made...

#include <vector>
#include <map>
#include <string>

class Sector
{
private:
    std::map<std::string, Character*> characterMap;
public:
    Sector();
    void MoveChar(std::string id, Sector* destination);
};

#endif
