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

#include "Fake_Server.h"
#include "Event.h"
#include "Client.h"
#include "Event_Manager.h"
#include "constants.h"
#include "Conversions.h"

#include <string>
#include <fstream>
#include <sstream>

Fake_Server::Fake_Server(std::string filename)
{
    std::ifstream inFile;
    inFile.open(filename.c_str());
    std::string line = "";
    getline(inFile, line);
    world = new World(line);
    getline(inFile, line);
    int locx = 0, locy = 0;
    std::string temp = "";
    int i = 0;
    while (line != "END_")
    {
        std::stringstream inString;
        inString.str(line);
        inString >> temp;
        locx = Conversions::StringToInt(temp);
        inString >> temp;
        locy = Conversions::StringToInt(temp);
        world->AddCharacter(new Character(locx, locy, CHARACTER_WIDTH, CHARACTER_HEIGHT, NULL, i));
        i++;
        getline(inFile, line);
    }
    eventManager = new Event_Manager(world->GetCharacterMap());
    inFile.close();
}

Quest* Fake_Server::GetQuest(int id)
{
    return questMap[id];
}

void Fake_Server::InEvent(std::string event)
{
    eventManager->AddEvent(event);
    //Here, it still needs to determine which clients (if any) to send this event to
}

std::string Fake_Server::RegisterClient(int clientId, int characterId)
{
    world->GetCharacter(characterId)->AssignClient(clientId);
    std::string toSend = "";
    for (std::map<int, Character*>::iterator i = world->GetCharacterMap()->begin(); i != world->GetCharacterMap()->end(); i++)
    {
        toSend += i->second->Serialize() + "\n";
    }
    toSend += "END_";
    return toSend;
}
