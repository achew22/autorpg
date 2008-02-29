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

#include "Client.h"

#include <string>
#include <sstream>

Client::Client(Fake_Server* theServer, int clientId)
{
    id = clientId;
    server = theServer;
    eventManager = new Event_Manager(&characterMap);
}

void Client::Connect(int characterId)
{
    std::string setupString = server->RegisterClient(id, characterId);
    std::stringstream setupStream;
    setupStream.str(setupString);
    std::string line = "";
    getline(setupStream, line);
    while (line != "END_")
    {
        Character* tempChar = new Character(line);
        characterMap.insert(std::pair<int, Character*>(tempChar->GetId(), tempChar));
        getline(setupStream, line);
    }
}

void Client::InEvent(Event* event)
{
    eventManager->AddEvent(event);
    server->InEvent(Event::Serialize(event));
}
