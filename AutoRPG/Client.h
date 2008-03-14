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
#include "Area.h"
#include "Fake_Server.h"

#include <SDL/SDL.h>
#include <map>
#include <string>
#include <vector>

class Client
{
private:
    int id;
    Event_Manager* eventManager;
    std::map<int, Character*> characterMap;
    Fake_Server* server;
    Character* player;

    //Key mappings
    SDLKey moveUp;
    SDLKey moveDown;
    SDLKey moveLeft;
    SDLKey moveRight;
public:
    Client(Fake_Server* theServer, int clientId);
    ~Client();
    bool Update();
    void SetKeys(SDLKey keyUp, SDLKey keyDown, SDLKey keyLeft, SDLKey keyRight);
	int GetId();
    bool Connect(int characterId);  //Connects to the server using character with id characterId
	void RegisterEvent(std::string event);  //Let the Client know that an event has occurred
	void SendEventToServer(std::string event);  //Send a serialized event to server - often occurs in tandem with the function above
    bool PollEvent();   //Process the next event in eventManager. Returns false if there are no more events to poll
    void HandleInput(SDL_Event SDLEvent);   //Handle the input from SDL, such as keypresses and mouse clicks
};

#endif
