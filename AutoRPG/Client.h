#ifndef CLIENT_H
#define CLIENT_H

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

#include "Event_Manager.h"
#include "Character.h"
#include "Sector.h"
#include "Event.h"
#include "Fake_Server.h"

#include <map>
#include <vector>

class Client
{
private:
    int id;
    Event_Manager* eventManager;
    std::map<int, Character*> characterMap;
    //std::vector<Sector*> sectorArray;
    Fake_Server* server;
public:
    Client(Fake_Server* theServer, int clientId);
    void Connect(int characterId);
    void InEvent(Event* event);
};

#endif
