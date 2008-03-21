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
#include <SDL/SDL.h>

Client::Client(Fake_Server* theServer, int clientId, SDL_Surface* theScreen)
{
    id = clientId;
    server = theServer;
    eventManager = new Event_Manager(&characterMap);
    player = NULL;

    screen = theScreen;
    dynamicLayer = SDL_CreateRGBSurface(SDL_SWSURFACE, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, NULL, NULL, NULL, NULL);
    map = NULL;

    moveUp = SDLK_UP;
    moveDown = SDLK_DOWN;
    moveLeft = SDLK_LEFT;
    moveRight = SDLK_RIGHT;
}

Client::~Client()
{
    delete eventManager;
    SDL_FreeSurface(dynamicLayer);
    if (map != NULL)
    {
        delete map;
    }
}

bool Client::Update()
{
    std::string event = player->PollEvent();

    //First, send all of the events that the character did to the server
    while (event != "NULL")
    {
        if (DEBUG_SHOWALL || DEBUG_SHOWEVENTS)
        {
            printf("Client %i sent an event with string '%s' to the server!\n", id, event.c_str());
        }
        SendEventToServer(event);
        event = player->PollEvent();
    }

    //Now process all of the events that the server sent to the client
    while (PollEvent())
    {
        if (DEBUG_SHOWALL || DEBUG_SHOWEVENTS)
        {
            printf("Client %i is polling an event that occurred\n", id);
        }
    }

    //Now update the positions of all of the characters that it knows of
    for (std::map<int, Character*>::iterator i = characterMap.begin(); i != characterMap.end(); i++)
    {
        i->second->UpdatePosition();
    }

    return true;
}

void Client::SetKeys(SDLKey keyUp, SDLKey keyDown, SDLKey keyLeft, SDLKey keyRight)
{
    moveUp = keyUp;
    moveDown = keyDown;
    moveLeft = keyLeft;
    moveRight = keyRight;
}

int Client::GetId()
{
	return id;
}

//Attempt to connect to the server and take control of the character with id characterId
bool Client::Connect(int characterId)
{
    std::string setupString = server->RegisterClient(this, characterId);
    if (setupString == "FAILED")
    {
        return false;
    }
    std::stringstream setupStream;
    setupStream.str(setupString);
    std::string line = "", mapfile = "", picfile = "";
    getline(setupStream, line); //Should read 'Map:'
    getline(setupStream, mapfile); //Should read 'mapfile.txt'
    getline(setupStream, picfile); //Should read 'picturefile.png'
    map = new Map(mapfile, picfile);
    getline(setupStream, line); //Shoud read 'Characters:'
    getline(setupStream, line); //Should be the serialized version of the first character
    while (line != "END_")
    {
        Character* tempChar = new Character(line);
        characterMap.insert(std::pair<int, Character*>(tempChar->GetId(), tempChar));
        getline(setupStream, line);
    }
    player = characterMap.find(characterId)->second;
    return true;
}

void Client::RegisterEvent(std::string event)
{
	eventManager->AddEvent(event);
}

void Client::SendEventToServer(std::string event)
{
    server->RegisterEvent(event, id);
}

bool Client::PollEvent()
{
    return eventManager->PollEvent();
}

void Client::HandleInput(SDL_Event SDLEvent)
{
    if (SDLEvent.type == SDL_KEYDOWN)
    {
        SDLKey keyPressed = SDLEvent.key.keysym.sym;
        if (keyPressed == moveRight)    //Right button pressed
        {
            player->MoveRight();
        }
        else if (keyPressed == moveLeft)    //Left button pressed
        {
            player->MoveLeft();
        }
        else if (keyPressed == moveDown)    //Down button pressed
        {
            player->MoveDown();
        }
        else if (keyPressed == moveUp)    //Up button pressed
        {
            player->MoveUp();
        }
    }
    else if (SDLEvent.type == SDL_KEYUP)
    {
        SDLKey keyUp = SDLEvent.key.keysym.sym;
        if (keyUp == moveRight)    //Right button released
        {
            if (player->GetVelocity().x > 0)   //If you were moving right
            {
                player->StopMoveHoriz();    //Stop moving right
            }
        }
        else if (keyUp == moveLeft)     //Left button released
        {
            if (player->GetVelocity().x < 0)   //If you were moving left
            {
                player->StopMoveHoriz();    //Stop moving left
            }
        }
        else if (keyUp == moveUp)     //Up button released
        {
            if (player->GetVelocity().y < 0)   //If you were moving up
            {
                player->StopMoveVert();    //Stop moving up
            }
        }
        else if (keyUp == moveDown) //Down button released
        {
            if (player->GetVelocity().y > 0) //If you were moving down
            {
                player->StopMoveVert();  //Stop moving down
            }
        }
    }
}


