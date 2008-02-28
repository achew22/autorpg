#ifndef FAKE_SERVER_H
#define FAKE_SERVER_H

#include "World.h"

#include <string>

//Returns everything as a string, since everything ought to be serialized. This means that it
//will have to go through the parser before it can be used.
class Fake_Server
{
private:
    World* theWorld;
public:
    Fake_Server();
    std::string getQuest(int id);
};

#endif
